"""Module to calculate the damage and impact risk for given scenarios"""
import os
import pandas as pd
import numpy as np
from deepimpact.locator import GeospatialLocator

__all__ = ['damage_zones', 'impact_risk']


def solve(E_k, z_b, pressures):
    """
    Solve for the radii of a system using the given parameters and
    pressure values.

    Parameters:
    - E_k (float): Elastic modulus of the material.
    - z_b (float): Characteristic length scale.
    - pressures (list of float): List of pressure values at which to
    determine the radii.

    Returns:
    list of float or None: A list containing the radii corresponding to
    the input pressures. If the Newton-Raphson method fails to converge,
    the corresponding entry in the list will be None.

    Notes:
    This function uses the Newton-Raphson method to solve for the radii
    of a system based on the given pressure values and the pressure
    equation defined within the function. The pressure equation, along
    with its first and second derivatives, is used in the iterative
    process to find the root.

    """
    # pressure equation
    def pressured0(r):
        return 3e11 * ((r**2 + z_b**2) / E_k**(2/3))**-1.3 + 2e7 * \
            ((r**2 + z_b**2) / E_k**(2/3))**-0.57

    # first derivative of the pressure equation
    def pressured1(r):
        return 3e11 * (-1.3) * r**(-2.3) + 2e7 * (-0.57) * r**(-1.57)

    # second derivative of the pressure equation
    def pressured2(r):
        return 3e11 * (-1.3)*(-2.3) * r**(-3.3) + 2e7 * \
            (-0.57)*(-1.57) * r**(-2.57)

    # Newton-Raphson method to estimate the radii
    def newton_raphson(pressure,
                       initial_guess=1e4,
                       max_iterations=100000,
                       tol=1e-8):
        r = initial_guess
        for _ in range(max_iterations):
            F_prime_0 = pressured0(r) - pressure
            F_prime_1 = pressured1(r)
            F_prime_2 = pressured2(r)

            r_next = r - (F_prime_0 / F_prime_1) - \
                (0.5 * F_prime_0**2 * F_prime_2 / F_prime_1**3)

            if abs(r_next - r) < tol:
                return r_next

            r = r_next

        # Should have returned 0 if there is no conversion, as 'None'
        # causes conflicts when doing radius calculations in postcode

        # return 0
        return None

    radii = [newton_raphson(pressure) for pressure in pressures]
    return radii


def damage_zones(outcome, lat, lon, bearing, pressures):
    """
    Calculate the latitude and longitude of the surface zero location and the
    list of airblast damage radii (m) for a given impact scenario.

    Parameters:
    -----------

    outcome: Dict
        the outcome dictionary from an impact scenario
    lat: float
        latitude of the meteoroid entry point (degrees)
    lon: float
        longitude of the meteoroid entry point (degrees)
    bearing: float
        Bearing (azimuth) relative to north of meteoroid trajectory (degrees)
    pressures: float, arraylike
        List of threshold pressures to define airblast damage levels

    Returns:
    --------

    blat: float
        latitude of the surface zero point (degrees)
    blon: float
        longitude of the surface zero point (degrees)
    damrad: arraylike, float
        List of distances specifying the blast radii
        for the input damage levels

    Examples:
    ---------

    >>> import deepimpact
    >>> outcome = {'burst_altitude': 8e3, 'burst_energy': 7e3,
                   'burst_distance': 90e3, 'burst_peak_dedz': 1e3,
                   'outcome': 'Airburst'}
    >>> deepimpact.damage_zones(outcome, 52.79, -2.95, 135,
                                pressures=[1e3, 3.5e3, 27e3, 43e3])

    """

    # get the dictionary every elements
    # if not exist return 0
    burst_distance = outcome.get('burst_distance', 0)
    # earth radius (m)
    Rp = 6371e3
    # the distance of lat lon both so that we can use Vincenty's formulae
    d = burst_distance / Rp
    # convert to radians
    bearing_rad = np.radians(bearing)
    lat_rad = np.radians(lat)
    lon_rad = np.radians(lon)

    # get the radians values of blat and blon
    blat = np.arcsin(np.sin(lat_rad) * np.cos(d) +
                     np.cos(lat_rad) * np.sin(d) * np.cos(bearing_rad))

    blon = lon_rad + np.arctan2(np.sin(bearing_rad) * np.sin(d) * np.cos(
        lat_rad),
                                np.cos(d) - np.sin(lat_rad) * np.sin(blat))

    # convert to degrees back
    blat = np.degrees(blat)
    blon = np.degrees(blon)
    # get the elements from the outcome dict
    z_b = outcome.get('burst_altitude', 0)
    E_k = outcome.get('burst_energy', 1)  # can't be 0

    # calculating the damage radius for each pressure level
    damrad = solve(E_k, z_b, pressures)
    blat = float(blat)
    blon = float(blon)

    return blat, blon, damrad


def impact_risk(planet,
                impact_file=os.sep.join((os.path.dirname(__file__),
                                         '..', 'resources',
                                         'impact_parameter_list.csv')),
                pressure=30.e3, nsamples=None):
    """
    Perform an uncertainty analysis to calculate the probability for
    each affected UK postcode and the total population affected.

    Parameters:
    -----------

    planet: deepimpact.Planet instance
        The Planet instance from which to solve the atmospheric entry

    impact_file: str
        Filename of a .csv file containing the impact parameter list
        with columns for 'radius', 'angle', 'velocity', 'strength',
        'density', 'entry latitude', 'entry longitude', 'bearing'

    pressure: float
        A single pressure at which to calculate the damage zone for each impact

    nsamples: int or None
        The number of iterations to perform in the uncertainty analysis.
        If None, the full set of impact parameters provided in impact_file
        is used.

    Returns:
    --------

    probability: DataFrame
        A pandas DataFrame with columns for postcode and the
        probability the postcode was inside the blast radius.
    population: dict
        A dictionary containing the mean and standard deviation of the
        population affected by the impact, with keys 'mean' and 'stdev'.
        Values are floats.

    """

    affected_postcode = {}
    # read the csv from the impact file
    impact_parameters = pd.read_csv(impact_file)
    if nsamples is None:
        nsamples = len(impact_parameters)
    locator = GeospatialLocator()
    # initial arrays to store affected populations
    populations = np.empty(nsamples)

    # extract necessary columns
    radii, velocities, densities, strengths, angles, entry_latitudes, \
        entry_longitudes, bearings = \
        [impact_parameters[col].values for col in ['radius', 'velocity',
                                                   'density', 'strength',
                                                   'angle', 'entry latitude',
                                                   'entry longitude',
                                                   'bearing']]
    # loop the all elements in the nsamples
    for i in range(nsamples):
        atmospheric_entry = planet.solve_atmospheric_entry(radii[i],
                                                           velocities[i],
                                                           densities[i],
                                                           strengths[i],
                                                           angles[i])
        energy = planet.calculate_energy(atmospheric_entry)
        outcome = planet.analyse_outcome(energy)

        blat, blon, blast_radius = damage_zones(outcome,
                                                entry_latitudes[i],
                                                entry_longitudes[i],
                                                bearings[i],
                                                [pressure])
        postcodes = locator.get_postcodes_by_radius((blat, blon),
                                                    [blast_radius[0]])

        # Required in case there are no postcodes within the radius of a
        # given impact (such as high alt low energy blast). This was discovered
        # running the Glasgow scenario, as there was no catch for this event
        # in the code prior. This was added to run the simulations on Friday.

        # if not postcodes[0]:
        #     continue

        for postcode in postcodes:
            if postcode[0] in affected_postcode:
                affected_postcode[postcode[0]] += 1/nsamples
            else:
                affected_postcode[postcode[0]] = 1/nsamples

        populations[i] = locator.get_population_by_radius((blat,
                                                           blon),
                                                          [blast_radius[0]])[0]

    probability = pd.DataFrame(list(affected_postcode.items()),
                               columns=['postcode', 'probability'])
    mean_val = float(np.mean(populations))
    std_val = float(np.std(populations))
    population = {'mean': mean_val, 'stdev': std_val}

    return probability, population
