from collections import OrderedDict
import pandas as pd
import numpy as np
import os

from pytest import fixture


# Use pytest fixtures to generate objects we know we'll reuse.
# This makes sure tests run quickly

@fixture(scope='module')
def deepimpact():
    import deepimpact
    return deepimpact


@fixture(scope='module')
def planet(deepimpact):
    return deepimpact.Planet()


@fixture(scope='module')
def loc(deepimpact):
    return deepimpact.GeospatialLocator()


@fixture(scope='module')
def result_solve_atmospheric_entry(planet):
    input = {'radius': 1.,
             'velocity': 2.0e4,
             'density': 3000.,
             'strength': 1e5,
             'angle': 30.0,
             'init_altitude': 1e5,
             }
    result = planet.solve_atmospheric_entry(**input)
    return result


@fixture(scope='module')
def result_calculate_energy(planet, result_solve_atmospheric_entry):
    result = planet.calculate_energy(result_solve_atmospheric_entry)
    return result


@fixture(scope='module')
def outcome(planet, result_calculate_energy):
    outcome = planet.analyse_outcome(result_calculate_energy)
    return outcome


def test_import(deepimpact):
    assert deepimpact


def test_planet_signature(deepimpact):
    inputs = OrderedDict(atmos_func='exponential',
                         atmos_filename=None,
                         Cd=1., Ch=0.1, Q=1e7, Cl=1e-3,
                         alpha=0.3, Rp=6371e3,
                         g=9.81, H=8000., rho0=1.2)

    # call by keyword
    _ = deepimpact.Planet(**inputs)

    # call by position
    _ = deepimpact.Planet(*inputs.values())


def test_attributes(planet):
    for key in ('Cd', 'Ch', 'Q', 'Cl',
                'alpha', 'Rp', 'g', 'H', 'rho0'):
        assert hasattr(planet, key)


def test_atmos_filename(planet):

    assert os.path.isfile(planet.atmos_filename)


def test_solve_atmospheric_entry(result_solve_atmospheric_entry):

    assert type(result_solve_atmospheric_entry) is pd.DataFrame

    for key in ('velocity', 'mass', 'angle', 'altitude',
                'distance', 'radius', 'time'):
        assert key in result_solve_atmospheric_entry.columns


def test_calculate_energy(planet, result_solve_atmospheric_entry):

    energy = planet.calculate_energy(result=result_solve_atmospheric_entry)

    assert type(energy) is pd.DataFrame

    for key in ('velocity', 'mass', 'angle', 'altitude',
                'distance', 'radius', 'time', 'dedz'):
        assert key in energy.columns


def test_analyse_outcome(outcome):
    assert type(outcome) is dict

    for key in ('outcome', 'burst_peak_dedz', 'burst_altitude',
                'burst_distance', 'burst_energy'):
        assert key in outcome.keys()


def test_scenario(planet):

    inputs = {'radius': 35.,
              'angle': 45.,
              'strength': 1e7,
              'density': 3000.,
              'velocity': 19e3}

    result = planet.solve_atmospheric_entry(**inputs)

    # For now, we just check the result is a DataFrame
    # and the columns are as expected.

    # You should add more tests here to check the values
    # are correct and match the expected output
    # given in the tests/scenario.npz file

    assert type(result) is pd.DataFrame

    for key in ('velocity', 'mass', 'angle', 'altitude',
                'distance', 'radius', 'time'):
        assert key in result.columns

    # Test values


def test_damage_zones(deepimpact):

    outcome = {'burst_peak_dedz': 1000.,
               'burst_altitude': 9000.,
               'burst_distance': 90000.,
               'burst_energy': 6000.,
               'outcome': 'Airburst'}

    blat, blon, damrad = deepimpact.damage_zones(outcome, 55.0, 0.,
                                                 135., [27e3, 43e3])

    assert type(blat) is float
    assert type(blon) is float
    assert type(damrad) is list
    assert len(damrad) == 2


def test_damage_zones_case_2(deepimpact):
    outcome = {'burst_altitude': 8e3, 'burst_energy': 7e3,
               'burst_distance': 90e3, 'burst_peak_dedz': 1e3,
               'outcome': 'Airburst'}
    blat, blon, damrad = deepimpact.damage_zones(outcome, 52.79, -2.95, 135,
                                                 [1e3, 3.5e3, 27e3, 43e3])
    assert type(blat) is float
    assert type(blon) is float
    assert type(damrad) is list
    assert len(damrad) == 4
    assert abs(blat - 52.21396905) < 1e-5
    assert abs(blon - (-2.01590886)) < 1e-5
    assert abs(damrad[0] - 117474.6796632462) < 1e-5


def test_damage_zones_case_3(deepimpact):
    outcome = {'burst_altitude': 8e3, 'burst_energy': 7e3,
               'burst_distance': 90e3, 'burst_peak_dedz': 1e3,
               'outcome': 'Airburst'}

    blat, blon, damrad = deepimpact.damage_zones(outcome, 53.02, -2.51, 115,
                                                 [2e3, 4.5e3, 37e3, 53e3])

    assert type(blat) is float
    assert type(blon) is float
    assert type(damrad) is list
    assert len(damrad) == 4
    assert abs(blat - 52.67175988) < 1e-5
    assert abs(blon - (-1.300221345)) < 1e-5
    assert abs(damrad[1] - 35768.268205174536) < 1e-5


def test_damage_zones_case_4(deepimpact):
    outcome = {'burst_altitude': 8e3, 'burst_energy': 7e3,
               'burst_distance': 90e3, 'burst_peak_dedz': 1e3,
               'outcome': 'Airburst'}

    blat, blon, damrad = deepimpact.damage_zones(outcome, 52.97, -2.50, 115,
                                                 pressures=[30e3])

    assert type(blat) is float
    assert type(blon) is float
    assert type(damrad) is list
    assert len(damrad) == 1
    assert abs(blat - 52.6217710) < 1e-5
    assert abs(blon - (-1.291603629)) < 1e-5
    assert abs(damrad[0] - 8643.027676043857) < 1e-5


def test_damage_zones_case_5(deepimpact):
    outcome = {'burst_altitude': 8e3, 'burst_energy': 7e3,
               'burst_distance': 90e3, 'burst_peak_dedz': 1e3,
               'outcome': 'Airburst'}
    blat, blon, damrad = deepimpact.damage_zones(outcome, 53.00, -2.50, 115,
                                                 [2e4, 4.5e4, 37e3, 53e3])

    assert type(blat) is float
    assert type(blon) is float
    assert type(damrad) is list
    assert len(damrad) == 4
    assert abs(blat - 52.65176434253817) < 1e-5
    assert abs(blon - (-1.290774748746865)) < 1e-5
    assert abs(damrad[0] - 12187.367560816681) < 1e-5


def test_great_circle_distance(deepimpact):

    pnts1 = np.array([[54.0, 0.0], [55.0, 1.0], [54.2, -3.0]])
    pnts2 = np.array([[55.0, 1.0], [56.0, -2.1], [54.001, -0.003]])

    data = np.array([[1.28580537e+05, 2.59579735e+05, 2.25409117e+02],
                    [0.00000000e+00, 2.24656571e+05, 1.28581437e+05],
                    [2.72529953e+05, 2.08175028e+05, 1.96640630e+05]])

    dist = deepimpact.great_circle_distance(pnts1, pnts2)

    assert np.allclose(data, dist, rtol=1.0e-4)


def test_locator_postcodes(loc):

    latlon = (52.2074, 0.1170)

    result = loc.get_postcodes_by_radius(latlon, [0.2e3, 0.1e3])

    assert type(result) is list
    if len(result) > 0:
        for element in result:
            assert type(element) is list


def test_population_by_radius(loc):

    latlon = (52.2074, 0.1170)

    result = loc.get_population_by_radius(latlon, [5e2, 1e3])

    assert type(result) is list
    if len(result) > 0:
        for element in result:
            assert type(element) is int


def test_impact_risk(deepimpact, planet):

    probability, population = deepimpact.impact_risk(planet)

    assert type(probability) is pd.DataFrame
    assert 'probability' in probability.columns
    assert type(population) is dict
    assert 'mean' in population.keys()
    assert 'stdev' in population.keys()
    assert type(population['mean']) is float
    assert type(population['stdev']) is float
    assert len(population) == 2
    assert abs(population['mean'] - 275452.8) < 1e-5
    assert abs(population['stdev'] - 160965.51590934003) < 1e-5
