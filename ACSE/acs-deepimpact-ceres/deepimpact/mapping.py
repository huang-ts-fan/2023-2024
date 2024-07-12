"""This module contains some useful mapping functions"""
import folium
import pandas as pd
from .locator import GeospatialLocator
import deepimpact
from folium.plugins import HeatMap
import os
import collections.abc


__all__ = ['plot_heatmap', 'plot_meteors', 'plot_meteor', 'plot_circle']

pressures = [1e3, 4e3, 30e3, 50e3]
pressure_colours = ['green', 'yellow', 'red', 'black']


def plot_heatmap(probability, population,
                 latlongfile=os.sep.join((os.path.dirname(__file__),
                                          '..', 'resources',
                                          'full_postcodes.csv'))):
    """
    Creates a heatmap showing the probability of a given postcode being
    affected by the impact event.

    Parameters:
    -----------
    probability : pandas.DataFrame
        A DataFrame containing postcodes and their associated impact
        probabilities. It contains the columns 'postcode' and 'probability'.
    population : dict
        A dictionary containing population statistics.
    latlongfile : str, optional
        Path to the CSV file containing latitude and longitude data for each
        postcode. The CSV file should have columns 'Postcode', 'Latitude', and
        'Longitude'.

    Returns:
    --------
    fmap: folium.Map
        A Folium map object with the heatmap overlay.

    Example
    -------
    >>> probability_df = pd.DataFrame({
    ...     'postcode': ['CV130AA', 'CV130AE'],
    ...     'probability': [0.3, 0.1]
    ... })
    >>> population_dict = {'mean': 276347.9, 'stdev': 161686.5}
    >>> heatmap = plot_heatmap(probability_df, population_dict)
    >>> heatmap.save('heatmap.html')

    """

    fmap = folium.Map(location=[55.3781, -3.4360], zoom_start=6)
    data = pd.read_csv(latlongfile)

    merged_df = probability.merge(data,
                                  left_on='postcode',
                                  right_on='Postcode',
                                  how='left')

    fmap = folium.Map(location=[55.3781, -3.4360], zoom_start=6)

    heatmap_data = merged_df[
        ['Latitude', 'Longitude', 'probability']].values.tolist()

    HeatMap(heatmap_data,
            radius=25,
            blur=15,
            max_zoom=17,
            min_opacity=0.5).add_to(fmap)

    return fmap


def plot_meteors(tail=True,
                 filename=os.sep.join((os.path.dirname(__file__),
                                       '..', 'resources',
                                       'impact_parameter_list.csv'))):
    """
    This function reads a CSV file containing meteor impact parameters,
    calculates the outcome of each impact, and plots the resulting damage
    zones on a map.

    Parameters:
    -----------
    tail : bool, optional
        Whether or not to plot the tail of the asteroids. Default is True.
    filename : str, optional
        Path to the CSV file containing impact parameters. The CSV file should
        have columns for 'radius', 'angle', 'velocity', 'strength', 'density',
        'entry latitude', 'entry longitude', and 'bearing'. Default path is
        set to 'resources/impact_parameter_list.csv'.

    Returns:
    --------
    fmap: folium.Map
        A Folium map object with plotted meteor impacts.

    Example:
    --------
    >>> impact_map = plot_meteors()
    >>> impact_map.save('meteor_impacts.html')

    """

    data = pd.read_csv(filename)
    earth = deepimpact.Planet()
    geoLoc = GeospatialLocator()
    fmap = folium.Map(location=[54.271, -2.247],
                      zoom_start=6,
                      control_scale=True)
    for i in range(len(data)):
        lat = data['entry latitude'][i]
        lon = data['entry longitude'][i]
        bearing = data['bearing'][i]

        result = earth.solve_atmospheric_entry(
            data['radius'][i],
            data['velocity'][i],
            data['density'][i],
            data['strength'][i],
            data['angle'][i]
        )
        energy = earth.calculate_energy(result)
        outcome = earth.analyse_outcome(energy)
        burst_lat, burst_lon, damage_radii = \
            deepimpact.damage_zones(outcome, lat, lon, bearing, pressures)
        fmap = plot_meteor(geoLoc=geoLoc,
                           blat=burst_lat,
                           blon=burst_lon,
                           radius=damage_radii,
                           lat=lat,
                           lon=lon,
                           tail=tail,
                           fill=False,
                           fmap=fmap)

    return fmap


def plot_meteor(blat, blon,
                radius,
                lat=-9999, lon=-9999,
                tail=True,
                geoLoc=GeospatialLocator(),
                fill=True,
                fmap=None,
                **kwargs):
    """
    Plots a circle on a map (creating a new folium map instance if necessary).

    Parameters:
    -----------
    blat: float
        Blast latitude of asteroid
    blon: float
        Blast longitude of asteroid
    radius: float or list of floats
        radius(es) of circle(s) to plot (m)
    lat: float, optional
        Entry latitude of asteroid
    lon: float, optional
        Entry longitude of asteroid
    tail : bool, optional
        Whether or not to plot the tail of the asteroid. Default is True.
    geoLoc: deepimpact.locator.GeospatialLocator, optional
        GeospatialLocator instance to calculate population affected
    fmap: folium.Map, optional
        existing map object

    Returns:
    --------

    fmap: folium.Map
        Folium map object

    Examples
    --------

    >>> import folium
    >>> deepimpact.plot_circle(52.79, -2.95, 1e3, map=None)
    """

    if not fmap:
        fmap = folium.Map(location=[blat, blon], control_scale=True)
    if (not isinstance(radius, collections.abc.Sequence)):
        radius = [radius]

    c = 0
    for radius_ in radius:
        if fill:
            col = get_colour_by_affected(geoLoc, blat, blon, radius_)
            folium.Circle([blat, blon],
                          radius_,
                          fill=True,
                          fillOpacity=0.5,
                          **kwargs,
                          fill_color=col,
                          color=col,
                          weight=1).add_to(fmap)
        else:
            folium.Circle([blat, blon],
                          radius_,
                          fill=False,
                          **kwargs,
                          color=pressure_colours[c],
                          weight=1).add_to(fmap)
        c += 1
    if tail and lat != -9999 and lon != -9999:
        folium.PolyLine(locations=[[lat, lon], [blat, blon]],
                        color='black',
                        weight=2).add_to(fmap)

    return fmap


def plot_circle(lat, lon, radius, fmap=None, **kwargs):
    """
    Plot a circle on a map (creating a new folium map instance if necessary).
    Parameters
    ----------
    lat: float
        latitude of circle to plot (degrees)
    lon: float
        longitude of circle to plot (degrees)
    radius: float
        radius of circle to plot (m)
    fmap: folium.Map
        existing map object
    Returns
    -------
    Folium map object
    Examples
    --------
    >>> import folium
    >>> deepimpact.plot_circle(52.79, -2.95, 1e3, map=None)
    """

    if not fmap:
        fmap = folium.Map(location=[lat, lon], control_scale=True)

    folium.Circle([lat, lon], radius, fill=True,
                  fillOpacity=0.6, **kwargs).add_to(fmap)

    return fmap


def get_colour_by_affected(geoLoc, lat, lon, radius_):
    """
    Returns the colour of the circle based on the number of people affected.

    """

    affected = geoLoc.get_population_by_radius([lat, lon], [radius_])[0]
    if affected < 1e3:
        return "blue"
    elif affected < 1e4:
        return "green"
    elif affected < 5e4:
        return "yellow"
    elif affected < 1e5:
        return "orange"
    elif affected < 1e6:
        return "red"
    else:
        return "black"
