# Correcting the import to be callable in the package.
# import deepimpact.solver as solver
import solver  # Incorrect, original state
import pandas as pd
from scipy.interpolate import interp1d
import numpy as np
from scipy.optimize import minimize
import os

# The missing function calls to be callable in the package.
# __all__ = ['find_parameters']


def simulate_energy_deposition(radius, strength, density=3300, angle=18.3,
                               velocity=19.2e3):
    """
    Simulates the energy deposition of an asteroid entering the Earth's
    atmosphere.
    This function models the atmospheric entry of an asteroid based on its
    physical parameters and calculates the energy deposition at various
    altitudes. It uses a planet model with a specified atmospheric density
    function and simulates the asteroid's entry using given parameters like
    radius, strength, density, entry angle, and velocity.

    Parameters:
    -----------

    radius : float
        The radius of the asteroid in meters.
    strength : float
        The strength of the asteroid in Pascals (Pa). This represents the
        maximum pressure the asteroid can withstand before breaking up.
    density : float, optional
        The density of the asteroid in kg/m^3. Default is 3300 kg/m^3.
    angle : float, optional
        The entry angle of the asteroid to the horizontal in degrees. Default
        is 18.3 degrees.
    velocity : float, optional
        The entry velocity of the asteroid in meters per second (m/s). Default
        is 19.2 km/s.

    Returns:
    --------

    pandas.DataFrame
        A DataFrame containing the simulation results. It includes columns for
        time, altitude, velocity, mass, angle, and energy deposition, showing
        how these values change as the asteroid descends through the
        atmosphere.

    Notes:
    ------

    The simulation assumes a tabular atmospheric density model and uses an
    instance of the `Planet` class from the `solver` module to calculate
    the atmospheric entry dynamics and energy loss.
    """
    earth = solver.Planet(atmos_func='tabular')

    df = earth.solve_atmospheric_entry(radius=radius, angle=angle,
                                       strength=strength, density=density,
                                       velocity=velocity, dt=0.05)
    result = earth.calculate_energy(df)

    return result


def read_data(file_path=os.sep.join(
    (os.path.dirname(__file__), '..', 'resources',
     'ChelyabinskEnergyAltitude.csv'))):
    """
    Reads energy deposition data from a specified CSV file.

    This function loads data from a CSV file containing altitude and energy
    information, typically used for analyzing events such as the Chelyabinsk
    meteor.
    The function is designed to be flexible, allowing the user to specify a
    different file path if needed.

    Parameters:
    -----------

    file_path : str, optional
        The path to the CSV file to be read. By default, it reads from
        'ChelyabinskEnergyAltitude.csv' located in the '../resources' directory
        relative to the script location.

    Returns:
    --------

    pandas.DataFrame
        A DataFrame with two columns: 'altitude' and 'energy'. 'altitude'
        column contains the altitude data, and 'energy' column contains the
        corresponding energy deposition data.
    """
    data = pd.read_csv(file_path, skiprows=1, names=['altitude', 'energy'])
    return data


def calculate_fit(radius, strength):
    """
    Calculates the fit of the simulated energy deposition against observed
    data.

    This function first interpolates the observed energy deposition data over
    a range of altitudes. It then simulates the energy deposition of an
    asteroid with specified radius and strength, and compares the simulated
    data with the interpolated observed data to calculate the fit.

    Parameters:
    -----------

    radius : float
        The radius of the asteroid in meters.
    strength : float
        The strength of the asteroid in Pascals (Pa).

    Returns:
    --------

    numpy.ndarray
        An array containing the differences between the simulated energy
        deposition and the observed data for a range of altitudes.
        The length of the array corresponds to the number of altitude
        points in the specified range.

    Notes:
    ------

    The function assumes that the observed data is available in a specific CSV
    file format and uses linear interpolation (interp1d) for the observed data.
    The altitude range for comparison is set between 21619.2 and 42192.2
    meters.
    """

    return_val = interp1d(read_data()['altitude'], read_data()['energy'],
                          fill_value='extrapolate')

    result = simulate_energy_deposition(radius, strength)

    a = result[result['altitude'] <= 42192.2].index
    b = result[result['altitude'] >= 21619.2].index
    altitude = result['altitude'][a[1]:b[-1]]

    fit_list = np.zeros(len(altitude))
    for i in range(a[1], a[1]+len(altitude)):
        fit_list[i-a[1]] = return_val(altitude[i]/1000)
    return fit_list


def objective_function(params):
    """
    Objective function to evaluate the fit of simulated asteroid parameters
    against observed energy deposition data.

    This function calculates the sum of squared differences between the
    simulated energy deposition curve (dedz) and the observed data curve.
    It is intended for use in an optimization algorithm to find the asteroid
    parameters that best match the observed data.

    Parameters:
    -----------

    params : list or array-like
        A list or array containing two elements: radius and strength of
        the asteroid. Radius is in meters, and strength is in Pascals (Pa).

    Returns:
    --------

    float
        The sum of squared differences between the simulated energy deposition
        curve and the observed data curve. A lower value indicates a better
        fit.

    Notes:
    ------

    - The function assumes that the observed data is available and has been
      processed to be comparable with the simulation results.
    - The altitude range for the comparison is set between 21619.2
    and 42192.2 meters.
    """

    radius, strength = params

    result = simulate_energy_deposition(radius, strength)

    a = result[result['altitude'] <= 42192.2].index
    b = result[result['altitude'] >= 21619.2].index

    simulated_curve = result['dedz'][a[1]:b[-1]]
    interpolated_curve = calculate_fit(radius, strength)
    # Calculate the sum of squared differences
    # between observed and simulated curves
    return np.sum((simulated_curve - interpolated_curve)**2)


def find_parameters(bounds=[(1e-3, None), (1e-3, None)],
                    initial_guess=[10, 1e5]):
    """
    Finds the best-fit parameters for an asteroid's atmospheric entry
    simulation.

    This function uses the Nelder-Mead optimization method to find the
    asteroid parameters (radius and strength) that best fit the observed
    energy deposition data. It aims to minimize the objective function,
    which measures the difference between the simulated and observed data.

    Parameters
    ----------
    bounds : list of tuples, optional
        The bounds within which the optimizer should search for the best-fit
        parameters. Each tuple in the list corresponds to the bounds for
        one of the parameters (radius and strength, respectively).
        The default bounds are set from 1e-3 upwards for both parameters.
    initial_guess : list, optional
        The initial guess for the parameters. It should be a list containing
        two elements: the initial guess for the radius (in meters) and
        the strength (in Pascals). The default values are 10 meters for
        radius and 1e5 Pascals for strength.

    Returns
    -------
    tuple
        A tuple containing the best-fit radius and strength (in that order).
        These values are the result of the optimization process.

    Notes
    -----
    - The Nelder-Mead method is used for optimization, which is a simplex
    method that does not require gradient information.
    - The success and accuracy of the optimization depend on the quality of
    the initial guess, the set bounds, and the objective function's
    formulation.
    """

    result = minimize(objective_function, initial_guess, method='Nelder-Mead',
                      bounds=bounds)

    # Check and analyze the results
    if result.success:
        best_radius, best_strength = result.x
        return best_radius, best_strength
