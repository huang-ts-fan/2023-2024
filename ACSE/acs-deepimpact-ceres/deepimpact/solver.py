"""
This module contains the atmospheric entry solver class
for the Deep Impact project
"""
import os
import numpy as np
import pandas as pd
from scipy.interpolate import PchipInterpolator

__all__ = ['Planet']


class Planet():
    """
    The class called Planet is initialised with constants appropriate
    for the given target planet, including the atmospheric density profile
    and other constants
    """

    def __init__(self, atmos_func='exponential',
                 atmos_filename=os.sep.join((os.path.dirname(__file__), '..',
                                             'resources',
                                             'AltitudeDensityTable.csv')),
                 Cd=1., Ch=0.1, Q=1e7, Cl=1e-3, alpha=0.3,
                 Rp=6371e3, g=9.81, H=8000., rho0=1.2):
        """
        Set up the initial parameters and constants for the target planet

        Parameters:
        -----------

        atmos_func: string, optional
            Function which computes atmospheric density, rho, at altitude, z.
            Default is the exponential function rho = rho0 exp(-z/H).
            Options are 'exponential', 'tabular' and 'constant'

        atmos_filename: string, optional
            Name of the filename to use with the tabular atmos_func option

        Cd: float, optional
            The drag coefficient

        Ch: float, optional
            The heat transfer coefficient

        Q: float, optional
            The heat of ablation (J/kg)

        Cl: float, optional
            Lift coefficient

        alpha: float, optional
            Dispersion coefficient

        Rp: float, optional
            Planet radius (m)

        rho0: float, optional
            Air density at zero altitude (kg/m^3)

        g: float, optional
            Surface gravity (m/s^2)

        H: float, optional
            Atmospheric scale height (m)

        """

        # Input constants
        self.Cd = Cd
        self.Ch = Ch
        self.Q = Q
        self.Cl = Cl
        self.alpha = alpha
        self.Rp = Rp
        self.g = g
        self.H = H
        self.rho0 = rho0
        self.atmos_filename = atmos_filename

        # set function to define atmoshperic density
        if atmos_func == 'exponential':
            self.rhoa = lambda z:  rho0 * np.exp(-z / self.H)
        elif atmos_func == 'tabular':
            density_table = pd.read_csv(
                self.atmos_filename,
                skiprows=1,
                names=['Altitude', 'Density'],
                sep='\\s+')
            density_interp = PchipInterpolator(
                density_table['Altitude'],
                density_table['Density']
            )
            self.rhoa = lambda z: density_interp(z)
        elif atmos_func == 'constant':
            self.rhoa = lambda z: rho0
        else:
            raise NotImplementedError(
                "atmos_func must be 'exponential', 'tabular' or 'constant'"
                )

    def solve_atmospheric_entry(
            self, radius, velocity, density, strength, angle,
            init_altitude=100e3, dt=0.05, radians=False):
        """
        Solve the system of differential equations for a given impact scenario
        Function written with the assistance of chat-GPT

        Parameters:
        -----------

        radius: float
            The radius of the asteroid in meters

        velocity: float
            The entery speed of the asteroid in meters/second

        density: float
            The density of the asteroid in kg/m^3

        strength: float
            The strength of the asteroid (i.e. the maximum pressure it can
            take before fragmenting) in N/m^2

        angle: float
            The initial trajectory angle of the asteroid to the horizontal
            By default, input is in degrees. If 'radians' is set to True, the
            input should be in radians

        init_altitude: float, optional
            Initial altitude in m

        dt: float, optional
            The output timestep, in s

        radians: logical, optional
            Whether angles should be given in degrees or radians. Default=False
            Angles returned in the dataframe will have the same units as the
            input

        Returns:
        --------

        Result: DataFrame
            A pandas dataframe containing the solution to the system.
            Includes the following columns:
            'velocity', 'mass', 'angle', 'altitude',
            'distance', 'radius', 'time'
        """

        if not radians:
            angle = np.deg2rad(angle)

        # Initial conditions
        time = 0.0

        mass = self.calculate_mass(radius, density)
        theta = angle
        altitude = init_altitude
        distance = 0.0

        # Setup for stopping conditions
        has_pancaked = False
        extra_iterations = 50
        i = 0  # For extra iterations after stopping condition met

        max_simulation_iterations = 1e6
        iteration_counter = 0

        prev_velocity = velocity
        velocity_change_relative_threshold = 2e-4
        prev_altitude = altitude

        # Calculation of numerical timestep
        # Get a dt that is close to target_dt but still divisible by output_dt
        target_dt = 0.005
        n = max(round(dt / target_dt), 1)
        output_dt = dt
        dt = output_dt / n  # calculate with a small timestep

        # Check for if cratering impact occurs between output timesteps
        add_last_iteration = False

        # Lists to store results
        velocities, masses, altitudes, distances, thetas, times, radii = \
            [velocity], [mass], [altitude], \
            [distance], [theta], [time], [radius]

        while i < extra_iterations:
            # Basic stopping conditions
            if mass < 0 or velocity < 0 or altitude < 0:
                # Add iteration of numerical dt if cratering happened
                # between output timesteps
                add_last_iteration = not iteration_counter % n == 0
                break

            if iteration_counter > max_simulation_iterations:
                break

            iteration_counter += 1

            # RK4 for solving update
            k1 = self.calculate_slopes(
                radius,
                velocity,
                mass,
                theta,
                altitude,
                density
            )
            k2 = self.calculate_slopes(
                radius,
                velocity + 0.5 * k1[0] * dt,
                mass + 0.5 * k1[1] * dt,
                theta + 0.5 * k1[2] * dt,
                altitude + 0.5 * k1[3] * dt,
                density
            )
            k3 = self.calculate_slopes(
                radius,
                velocity + 0.5 * k2[0] * dt,
                mass + 0.5 * k2[1] * dt,
                theta + 0.5 * k2[2] * dt,
                altitude + 0.5 * k2[3] * dt,
                density
            )
            k4 = self.calculate_slopes(
                radius,
                velocity + k3[0] * dt,
                mass + k3[1] * dt,
                theta + k3[2] * dt,
                altitude + k3[3] * dt,
                density
            )

            time += dt

            velocity += (k1[0] + 2*k2[0] + 2*k3[0] + k4[0]) * dt / 6.0
            mass += (k1[1] + 2*k2[1] + 2*k3[1] + k4[1]) * dt / 6.0
            theta += (k1[2] + 2*k2[2] + 2*k3[2] + k4[2]) * dt / 6.0
            altitude += (k1[3] + 2*k2[3] + 2*k3[3] + k4[3]) * dt / 6.0
            distance += (k1[4] + 2*k2[4] + 2*k3[4] + k4[4]) * dt / 6.0

            # Atmospheric density at current altitude
            rho_a = self.rhoa(altitude)
            ram_pressure = rho_a * velocity ** 2

            # Calculate change in radius if breaking up
            if ram_pressure >= strength:
                radius += (k1[5] + 2*k2[5] + 2*k3[5] + k4[5]) * dt / 6.0

                has_pancaked = True
            # Break if radius has pancaked and terminal velocity reached
            elif has_pancaked:
                delta_v = abs(velocity - prev_velocity)
                percentage_diff = delta_v / velocity
                if percentage_diff < velocity_change_relative_threshold:
                    i += 1

            # Break if meteor has bounced
            if altitude > prev_altitude:
                i += 1

            prev_velocity = velocity
            prev_altitude = altitude

            if iteration_counter % n == 0:
                times.append(time)
                radii.append(radius)
                velocities.append(velocity)
                masses.append(mass)
                thetas.append(theta)
                altitudes.append(altitude)
                distances.append(distance)

        # Ensures that the crater point is added to the df regardless of dt
        if add_last_iteration:
            times.append(time)
            radii.append(radius)
            velocities.append(velocity)
            masses.append(mass)
            thetas.append(theta)
            altitudes.append(altitude)
            distances.append(distance)

        if not radians:
            thetas = np.rad2deg(thetas)

        return pd.DataFrame({'velocity': velocities,
                             'mass': masses,
                             'angle': thetas,
                             'altitude': altitudes,
                             'distance': distances,
                             'radius': radii,
                             'time': times})

    def calculate_slopes(self, radius, v, m, theta, z, density):
        """
        Calculate the slopes for each equation.
        Function written with the assistance of chat-GPT


        Parameters:
        -----------

        radius: float
            The current radius of the asteroid.
        v: float
            The current velocity of the asteroid.
        m: float
            The current mass of the asteroid.
        theta: float
            The current trajectory angle of the asteroid.
        z: float
            The current altitude of the asteroid.
        density: float
            The current density of the asteroid.

        Returns:
        --------

        Returns: tuple
            The slope: (dv_dt, dm_dt, dtheta_dt, dz_dt, dx_dt)
        """

        A = np.pi * radius ** 2
        rho_a = self.rhoa(z)

        dv_dt = \
            (-self.Cd * rho_a * A * v ** 2) / (2 * m) + self.g * np.sin(theta)
        dtheta_dt = \
            (self.g * np.cos(theta) / v) - (self.Cl * rho_a * A * v) \
            / (2 * m) - (v * np.cos(theta)) / (self.Rp + z)
        dm_dt = (-self.Ch * rho_a * A * v ** 3) / (2 * self.Q)
        dz_dt = -v * np.sin(theta)
        dx_dt = (v * np.cos(theta)) / (1 + z / self.Rp)
        dr_dt = np.sqrt((7/2) * self.alpha * rho_a / density) * v

        return (dv_dt, dm_dt, dtheta_dt, dz_dt, dx_dt, dr_dt)

    def calculate_energy(self, result):
        """
        Function to calculate the kinetic energy lost per unit altitude in
        kilotons TNT per km, for a given solution.

        Parameters:
        -----------

        result: DataFrame
            A pandas dataframe with columns for the velocity, mass, angle,
            altitude, horizontal distance and radius as a function of time

        Returns: DataFrame
            Returns the dataframe with additional column ``dedz`` which is the
            kinetic energy lost per unit altitude

        """

        # First entry is np.nan because no previous kinetic energy
        dedz = [np.nan]

        mass = result["mass"].iloc[0]
        velocity = result["velocity"].iloc[0]
        altitude_previous = result["altitude"].iloc[0]
        ke_previous = self.calculate_kinetic_energy(mass, velocity)

        for i in range(1, len(result)):
            mass = result["mass"].iloc[i]
            velocity = result["velocity"].iloc[i]
            altitude_current = result["altitude"].iloc[i]
            ke_current = self.calculate_kinetic_energy(mass, velocity)

            # Calculate deltas and convert altitude from m to km
            delta_ke = ke_previous - ke_current
            delta_altitude = (altitude_previous - altitude_current) / 1000

            # Avoid division by zero
            if not np.isclose(delta_altitude, 0, rtol=1e-5):
                dedz_value = delta_ke / delta_altitude
            else:
                dedz_value = np.nan

            altitude_previous = altitude_current
            ke_previous = ke_current

            dedz.append(dedz_value)

        result['dedz'] = dedz

        return result

    def analyse_outcome(self, result):
        """
        Inspect a pre-found solution to calculate the impact and airburst stats

        Parameters:
        -----------

        result : DataFrame
            pandas dataframe with velocity, mass, angle, altitude, horizontal
            distance, radius and dedz as a function of time

        Returns:
        --------

        outcome : Dict
            dictionary with details of the impact event, which should contain
            the key: ``outcome`` (which should contain one of the following
            strings: ``Airburst`` or ``Cratering``),
            as well as the following 4 keys: ``burst_peak_dedz``,
            ``burst_altitude``, ``burst_distance``, ``burst_energy``
        """

        outcome = {'outcome': 'Unknown',
                   'burst_peak_dedz': 0.,
                   'burst_altitude': 0.,
                   'burst_distance': 0.,
                   'burst_energy': 0.}

        if result.empty:
            return outcome

        # Find the row with the maximum 'dedz'
        max_dedz_row = result.sort_values(by="dedz", ascending=False).iloc[0]

        # Update the outcome dictionary
        outcome['burst_peak_dedz'] = max_dedz_row['dedz']
        outcome['burst_altitude'] = max_dedz_row['altitude']
        outcome['burst_distance'] = max_dedz_row['distance']

        airburst = max_dedz_row['altitude'] > 0

        if airburst:
            outcome['outcome'] = 'Airburst'

            # Calculate burst energy as kinetic energy lost
            outcome['burst_energy'] = (
                self.calculate_kinetic_energy(
                    result['mass'].iloc[0],
                    result['velocity'].iloc[0]
                ) -
                self.calculate_kinetic_energy(
                    max_dedz_row['mass'],
                    (max_dedz_row['velocity']))
            )
        else:
            outcome['outcome'] = 'Cratering'

            # Calculate burst energy as max of residual kinetic and
            # current kinetic energy
            residual_kinetic_energy = (
                self.calculate_kinetic_energy(
                    result['mass'].iloc[0],
                    result['velocity'].iloc[0]
                ) -
                self.calculate_kinetic_energy(
                    result['mass'].iloc[-1],
                    result['velocity'].iloc[-1])
            )
            current_kinetic_energy = (
                self.calculate_kinetic_energy(
                    result['mass'].iloc[-1],
                    result['velocity'].iloc[-1]
                )
            )

            outcome['burst_energy'] = max(
                residual_kinetic_energy,
                current_kinetic_energy)

        return outcome

    def calculate_mass(self, radius, density):
        """
        Calculate the mass of a sphere given its density and radius.

        Parameters:
        -----------

        radius: float
            The radius of the sphere.
        density: float
            The density of the sphere

        Returns:
        --------

        mass: float
            The mass of the sphere.
        """

        volume = (4/3) * np.pi * radius ** 3
        mass = density * volume

        return mass

    def calculate_kinetic_energy(self, mass, velocity):
        """
        Calculate the kinetic energy of a body given its mass and velocity,
        and convert it to kilotons.

        Parameters:
        -----------

        mass: float
            The mass of the body in kilograms.

        velocity: float
            The velocity of the body in meters per second.

        Returns:
        --------

        energy_kilotons: float
            The kinetic energy of the body in kilotons of TNT equivalent.
        """

        JOULES_PER_KILOTON = 2.3900573613767E-13

        energy_joules = 0.5 * mass * velocity ** 2
        energy_kilotons = energy_joules * JOULES_PER_KILOTON

        return energy_kilotons
