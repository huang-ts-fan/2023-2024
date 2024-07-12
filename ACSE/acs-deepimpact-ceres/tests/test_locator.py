import numpy as np
from pytest import fixture
from pathlib import Path


@fixture(scope='module')
def deepimpact():
    import deepimpact
    return deepimpact


@fixture(scope='module')
def loc(deepimpact):
    return deepimpact.GeospatialLocator()


def test_import(deepimpact):
    assert deepimpact


def test_postcodes(loc):
    test_dir = Path(__file__).parent

    n6_subset_file = test_dir / "N6_subset_postcodes.npy"
    n6_subset_posts = np.load(n6_subset_file)
    assert np.equal(loc.get_postcodes_by_radius((51.574339,
                                                 -0.149349),
                    [1e2]), n6_subset_posts).all()

    g9_1 = [['G90 8BT', 'G90 8BU', 'G90 8BX']]

    assert np.equal(loc.get_postcodes_by_radius((55.868692,
                                                 -4.243649), [1]), g9_1).all()
    bt_1e4_file = test_dir / "BT_1e4_postcodes.npy"
    bt_1e4 = np.load(bt_1e4_file)

    assert np.equal(loc.get_postcodes_by_radius((54.267412, -7.610088), [1e4]),
                    list(bt_1e4[0])).all()

    bt_double = [['BT945PT'], ['BT923AR', 'BT945NQ', 'BT945PS', 'BT945PT']]

    assert loc.get_postcodes_by_radius((54.267412, -7.610088),
                                       [1e2, 1e3]) == bt_double

    ZE = [['ZE2 9EQ'],
          ['ZE2 9EQ'],
          ['ZE2 9EQ', 'ZE2 9TN', 'ZE2 9TP'],
          ['ZE2 9EJ', 'ZE2 9EQ', 'ZE2 9TN', 'ZE2 9TP']]
    X = (60.835883, -0.907385)
    result_ZE = loc.get_postcodes_by_radius(X, [4.418731e+03,
                                                6.391348e+03,
                                                6.417627e+03,
                                                6.492337e+03])
    assert result_ZE == ZE


def test_population(loc):
    # after sorting the values by latitude and longitude
    population_of_first_point = [7, 384, 59, 37_211_378]
    assert loc.get_population_by_radius((60.835883, -0.907385),
                                        [1e2, 1e4, 6063,
                                         1e6]) == population_of_first_point


def test_great_circle_distance(deepimpact):
    assert deepimpact.great_circle_distance((51.4981, -0.1773),
                                            (51.4981, -0.1773)) == [[0.]]

    X = (60.835883, -0.907385)
    Y = (60.835883, -0.507456)

    assert np.allclose(deepimpact.great_circle_distance(X, Y),
                       np.array([[21670.80685992]]))
