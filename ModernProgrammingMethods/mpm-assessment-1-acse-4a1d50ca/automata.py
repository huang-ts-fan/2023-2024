"""Implementations of Lorenz 96 and Conway's
Game of Life on various meshes"""

import numpy as np
import scipy
import matplotlib.pyplot as plt
from matplotlib.patches import Polygon


def lorenz96(initial_state, nsteps, constants=(1/101, 100, 8)):
    """
    Perform iterations of the Lorenz 96 update.

    Parameters
    ----------
    initial_state : array_like or list
        Initial state of lattice in an array of floats.
    nsteps : int
        Number of steps of Lorenz 96 to perform.

    Returns
    -------

    numpy.ndarray
         Final state of lattice in array of floats

    >>> x = lorenz96([8.0, 8.0, 8.0], 1)
    >>> print(x)
    array([8.0, 8.0, 8.0])
    """

    alpha, beta, gamma = constants
    N = len(initial_state)
    current_state = initial_state.copy()

    for _ in range(nsteps):
        x_minus_2 = np.roll(current_state, 2)
        x_minus_1 = np.roll(current_state, 1)
        x_i = current_state
        x_plus_1 = np.roll(current_state, -1)
        
        current_state = alpha * (beta * x_i + (x_minus_2 - x_plus_1) * x_minus_1 + gamma)

    return current_state


def life(initial_state, nsteps, rules="basic", periodic=False):
    """
    Perform iterations of Conway’s Game of Life.
    Parameters
    ----------
    initial_state : array_like or list of lists
        Initial 2d state of grid in an array of ints.
    nsteps : int
        Number of steps of Life to perform.
    rules : str
        Choose a set of rules from "basic", "2colour" or "3d".
    periodic : bool
        If True, use periodic boundary conditions.
    Returns
    -------
    numpy.ndarray
         Final state of grid in array of ints.
    """

    def count_neighbors_2d(x, y, state):
        dx = [0, 0, 1, -1, 1, 1, -1, -1]
        dy = [1, -1, 0, 0, 1, -1, 1, -1]
        count = 0
        colour_sum = 0
        for i in range(8):
            nx, ny = x + dx[i], y + dy[i]
            if periodic:
                nx = nx % len(state)
                ny = ny % len(state[0])
            if 0 <= nx < len(state) and 0 <= ny < len(state[0]) and state[nx][ny] != 0:
                count += 1
                colour_sum += state[nx][ny]
        return count, colour_sum

    def count_neighbors_3d(x, y, z, state):
        dx = [-1, 0, 1, -1, 0, 1, -1, 0, 1, -1, 0, 1, -1, 0, 1, -1, 0, 1, -1, 0, 1, -1, 0, 1, -1, 0, 1]
        dy = [-1, -1, -1, 0, 0, 0, 1, 1, 1, -1, -1, -1, 0, 0, 0, 1, 1, 1, -1, -1, -1, 0, 0, 0, 1, 1, 1]
        dz = [-1, -1, -1, -1, -1, -1, -1, -1, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1]
        count = 0
        for i in range(27):
            if dx[i] == 0 and dy[i] == 0 and dz[i] == 0:  # Exclude the cell itself
                continue
            nx, ny, nz = x + dx[i], y + dy[i], z + dz[i]
            if periodic:
                nx = nx % len(state)
                ny = ny % len(state[0])
                nz = nz % len(state[0][0])
            if 0 <= nx < len(state) and 0 <= ny < len(state[0]) and 0 <= nz < len(state[0][0]) and state[nx][ny][nz] == 1:
                count += 1
        return count

    if rules == "3d":
        # Handle 3D logic
        state = [[[cell for cell in row] for row in plane] for plane in initial_state]
        for step in range(nsteps):
            new_state = [[[0 for _ in range(len(state[0][0]))] for _ in range(len(state[0]))] for _ in range(len(state))]
            for i in range(len(state)):
                for j in range(len(state[0])):
                    for k in range(len(state[0][0])):
                        neighbors = count_neighbors_3d(i, j, k, state)
                        if state[i][j][k] == 1:  # Cell is alive
                            if neighbors == 5 or neighbors == 6:
                                new_state[i][j][k] = 1
                            else:
                                new_state[i][j][k] = 0
                        else:  # Cell is dead
                            if neighbors == 4:
                                new_state[i][j][k] = 1
            state = new_state
        return state

    else:
        # Handle 2D logic (includes both basic and 2colour rules)
        state = [row[:] for row in initial_state]
        for step in range(nsteps):
            new_state = [[0 for _ in range(len(state[0]))] for _ in range(len(state))]
            for i in range(len(state)):
                for j in range(len(state[0])):
                    neighbors, colour_sum = count_neighbors_2d(i, j, state)
                    if rules == "basic":
                        # Implement basic rules
                        if state[i][j] == 1:  # Cell is alive
                            if neighbors < 2 or neighbors > 3:
                                new_state[i][j] = 0
                            else:
                                new_state[i][j] = 1
                        else:  # Cell is dead
                            if neighbors == 3:
                                new_state[i][j] = 1
                    elif rules == "2colour":
                        # Implement 2colour rules
                        if state[i][j] != 0:  # Cell is alive
                            if neighbors < 2 or neighbors > 3:
                                new_state[i][j] = 0
                            else:
                                new_state[i][j] = state[i][j]
                        else:  # Cell is dead
                            if neighbors == 3:
                                new_state[i][j] = 1 if colour_sum > 0 else -1
            state = new_state
        return state


# The routines below are plotting aids. They do not need to modified and should not be called
# in the final versions of your functions.


def plot_lorenz96(data, label=None):
    """
    Plot 1d array on a circle

    Parameters
    ----------
    data: arraylike
        values to be plotted
    label:
        optional label for legend.
    """

    offset = 8

    data = np.asarray(data)
    theta = 2*np.pi*np.arange(len(data))/len(data)

    vector = np.empty((len(data), 2))
    vector[:, 0] = (data+offset)*np.sin(theta)
    vector[:, 1] = (data+offset)*np.cos(theta)

    theta = np.linspace(0, 2*np.pi)

    rings = np.arange(int(np.floor(min(data))-1),
                      int(np.ceil(max(data)))+2)
    for ring in rings:
        plt.plot((ring+offset)*np.cos(theta),
                 (ring+offset)*np.sin(theta), 'k:')

    fig_ax = plt.gca()
    fig_ax.spines['left'].set_position(('data', 0.0))
    fig_ax.spines['bottom'].set_position(('data', 0.0))
    fig_ax.spines['right'].set_color('none')
    fig_ax.spines['top'].set_color('none')
    plt.xticks([])
    plt.yticks(rings+offset, rings)
    plt.fill(vector[:, 0], vector[:, 1],
             label=label, fill=False)
    plt.scatter(vector[:, 0], vector[:, 1], 20)


def plot_array(data, show_axis=False,
               cmap=plt.cm.get_cmap('seismic'), **kwargs):
    """Plot a 1D/2D array in an appropriate format.

    Mostly just a naive wrapper around pcolormesh.

    Parameters
    ----------

    data : array_like
        array to plot
    show_axis: bool, optional
        show axis numbers if true
    cmap : pyplot.colormap or str
        colormap

    Other Parameters
    ----------------

    **kwargs
        Additional arguments passed straight to pyplot.pcolormesh
    """
    plt.pcolormesh(1*data[-1::-1, :], edgecolor='y',
                   vmin=-2, vmax=2, cmap=cmap, **kwargs)

    plt.axis('equal')
    if show_axis:
        plt.axis('on')
    else:
        plt.axis('off')
