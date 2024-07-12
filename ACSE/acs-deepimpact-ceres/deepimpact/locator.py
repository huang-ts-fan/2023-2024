"""Module dealing with postcode information."""

import numpy as np
import pandas as pd
import os

__all__ = ['GeospatialLocator', 'great_circle_distance']


def great_circle_distance(latlon1, latlon2):
    """
    Calculate the great circle distance (in metres) between pairs of
    points specified as latitude and longitude on a spherical Earth
    (with radius 6371 km).

    Parameters:
    -----------

    latlon1: arraylike
        latitudes and longitudes of first point (as [n, 2] array for n points)
    latlon2: arraylike
        latitudes and longitudes of second point (as [m, 2] array for m points)

    Returns:
    --------

    distance: numpy.ndarray
        Distance in metres between each pair of points (as an n x m array)

    Examples:
    ---------

    >>> import numpy
    >>> fmt = lambda x: numpy.format_float_scientific(x, precision=3)
    >>> with numpy.printoptions(formatter={'all': fmt}):
    ...    print(great_circle_distance([[54.0, 0.0], [55, 0.0]], [55, 1.0]))
    [[1.286e+05]
     [6.378e+04]]
    """

    latlon1, latlon2 = map(np.atleast_2d, [latlon1, latlon2])
    distance = np.empty((len(latlon1), len(latlon2)), float)

    # Earth radius in meters
    earth_radius = 6_371_000

    # Convert latitude and longitude from degrees to radians for all points
    lat1 = np.radians(latlon1[:, 0])
    lon1 = np.radians(latlon1[:, 1])
    lat2 = np.radians(latlon2[:, 0])
    lon2 = np.radians(latlon2[:, 1])

    # Calculate differences
    dlat = abs(lat2.reshape(1, -1) - lat1.reshape(-1, 1))
    dlon = abs(lon2.reshape(1, -1) - lon1.reshape(-1, 1))

    # Haversine formula
    part1 = np.sin(dlat/2)**2 + np.cos(lat1).reshape(-1, 1) * \
        np.cos(lat2).reshape(1, -1) * np.sin(dlon/2)**2
    part2 = 2 * np.arcsin(np.sqrt(part1))

    # Calculate the distance in meters
    distance = earth_radius * part2
    return distance


class GeospatialLocator(object):
    """
    Class to interact with a postcode database file and a population grid file.
    https://chat.openai.com/share/aed3e848-4b08-4afb-b3eb-56d67437eeec
    """
    cencus_name = 'UK_residential_population_2011_latlon.asc'

    def __init__(self, postcode_file=os.sep.join((os.path.dirname(__file__),
                                                 '..', 'resources',
                                                  'full_postcodes.csv')),
                 census_file=os.sep.join((os.path.dirname(__file__),
                                         '..', 'resources',
                                          cencus_name)),
                 norm=great_circle_distance):
        """
        Parameters:
        -----------

        postcode_file: str, optional
            Filename of a .csv file containing geographic
            location data for postcodes.

        census_file:  str, optional
            Filename of a .asc file containing census data on a
            latitude-longitude grid.

        norm: function
            Python function defining the distance between points in
            latitude-longitude space.

        """

        self.postcodes = pd.read_csv(postcode_file)
        self.cesus = np.loadtxt(census_file, skiprows=6)
        self.norm = norm

        with open(census_file, 'r') as file:
            self.ncols = int(file.readline().split()[1])
            self.nrows = int(file.readline().split()[1])
            self.nodata_value = float(file.readline().split()[1])

        unfiltered_latitudes = self.cesus[:self.nrows]
        unfiltered_longitudes = self.cesus[self.nrows:2*self.nrows]
        unfiltered_populations = self.cesus[2*self.nrows:]

        valid_points = unfiltered_populations != self.nodata_value
        self.latitudes = unfiltered_latitudes[valid_points]
        self.longitudes = unfiltered_longitudes[valid_points]
        self.populations = unfiltered_populations[valid_points]

    def get_postcodes_by_radius(self, X, radii):
        """
        Return postcodes within specific distances of
        input location.
        https://chat.openai.com/share/4c837ecd-06e2-4c01-840a-db4b01148bd5

        Parameters:
        -----------

        X : arraylike
            Latitude-longitude pair of centre location
        radii : arraylike
            array of radial distances from X

        Returns:
        --------
        postcodes_radii: list of lists
            Contains the lists of postcodes closer than the elements
            of radii to the location X.


        Examples:
        ---------

        >>> locator = GeospatialLocator()
        >>> locator.get_postcodes_by_radius((51.4981, -0.1773),
        ... [1.5e-3])
        [[]]
        >>> locator.get_postcodes_by_radius((51.4981, -0.1773),
        ... [1.5e-3, 4.0e-3])
        [[], []]
        """

        distances = great_circle_distance(np.array(
            self.postcodes[['Latitude', 'Longitude']]), X)
        postcodes_radii = [self.postcodes.loc[(distances[:, 0] <= radius),
                                              'Postcode'].tolist()
                           for radius in radii]

        return postcodes_radii

    def get_population_by_radius(self, X, radii):
        """
        Return the population within specific distances of input location.

        Parameters:
        -----------

        X : arraylike
            Latitude-longitude pair of centre location
        radii : arraylike
            array of radial distances from X

        Returns:
        --------

        population_radii: list
            Contains the population closer than the elements of radii to
            the location X. Output should be the same shape as the radii array.

        Examples:
        ---------

        >>> loc = GeospatialLocator()
        >>> loc.get_population_by_radius((51.4981, -0.1773), [1e2, 5e2, 1e3])
        [0, 7412, 27794]

        """

        assert X[0] >= self.latitudes.min() and X[0] <= \
            self.latitudes.max(), \
            "Latitude provided is out of range"
        assert X[1] >= self.longitudes.min() and X[1] <= \
            self.longitudes.max(), \
            "Longitude provided is out of range"

        distances = great_circle_distance(
            np.array([self.latitudes, self.longitudes]).T, X)

        radii = np.array(radii).reshape(-1, 1)
        population_radii = np.sum((distances[:, 0] <= radii) *
                                  self.populations, axis=1)
        population_radii = [int(population) for population in population_radii]

        return population_radii
