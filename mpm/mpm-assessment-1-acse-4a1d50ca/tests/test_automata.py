"""
Test automata module functions

Note: To ensure automata can be imported successfully, we recommend setting your PYTHONPATH prior to running this test file. This can be done in a terminal via, e.g.

export PYTHONPATH=/path_to/mpm-assessment-1

or similar.

"""
import os

import numpy as np

import automata

BASE_PATH = os.path.dirname(__file__)


class TestLorenz96(object):
    """Class for testing the lorenz96 automata"""

    def test_lorenz96_basic(self):
        """Test Lorenz 96 implementation using pre-defined data"""
        initial64 = np.load(os.sep.join((BASE_PATH,
                                        'lorenz96_64_init.npy')))

        onestep64 = np.load(os.sep.join((BASE_PATH,
                                        'lorenz96_64_onestep.npy')))
        assert np.isclose(automata.lorenz96(initial64, 1), onestep64).all()

        thirtystep64 = np.load(os.sep.join((BASE_PATH,
                                        'lorenz96_64_thirtystep.npy')))
        assert np.isclose(automata.lorenz96(initial64, 30), thirtystep64).all()

    def test_steady_state(self):
        """Test the steady state where all x[:] = 8"""
        initial = np.array([8.0] * 10)
        result = automata.lorenz96(initial, 1)
        assert np.isclose(result[-1], initial).all()

    def test_forcing_increase(self):
        """Test that forcing causes the values to increase appropriately from x[:] = 7"""
        initial = np.array([7.0] * 10)
        result = automata.lorenz96(initial, 1)
        # This is an assertion to check if the values increased but the exact behavior would depend on α,β,γ.
        assert np.all(result[-1] > initial)

    def test_single_cell_perturbation(self):
        initial_state = np.full((64,), 8.0)
        initial_state[10] = 9.0  # Perturb one cell
        result = automata.lorenz96(initial_state, 1)

        # Expected changes based on the provided update rule and example
        expected = np.full((64,), 8.0)
        expected[9] = 800/101
        expected[10] = 908/101
        expected[11] = 8
        expected[12] = 816/101

        assert np.isclose(result, expected).all(), "Test failed for single cell perturbation"

    def test_boundary_condition(self):
        initial_state = np.full((64,), 8.0)
        initial_state[0] = 9.0  # Perturb the first cell to check periodic boundary
        result = automata.lorenz96(initial_state, 1)

        expected = np.full((64,), 8.0)
        expected[-1] = 800/101
        expected[0] = 908/101
        expected[2] = 816/101

        assert np.isclose(result, expected).all(), "Test failed for boundary condition"



class TestLife(object):
    """Class for testing the life automata"""

    def test_life_basic(self):
        """Test basic rules implementation"""
        initial_state_basic = np.array([
            [0, 1, 0],
            [0, 1, 0],
            [0, 1, 0]
        ])
        expected_output_basic = np.array([
            [0, 0, 0],
            [1, 1, 1],
            [0, 0, 0]
        ])
        result_basic = automata.life(initial_state_basic, 1, rules="basic")
        assert np.array_equal(result_basic, expected_output_basic)

    def test_life_2colour(self):
        """Test 2colour rules implementation"""
        initial_state_2colour = np.array([
            [0, 1, 0],
            [0, -1, 0],
            [0, 1, 0]
        ])
        expected_output_2colour = np.array([
            [0, 0, 0],
            [1, -1, 1],
            [0, 0, 0]
        ])
        result_2colour = automata.life(initial_state_2colour, 1, rules="2colour")
        assert np.array_equal(result_2colour, expected_output_2colour)

    def test_life_3d(self):
        """Test 3d rules implementation"""
        initial_state_3d = np.array([
            [
                [0, 0, 0],
                [0, 1, 0],
                [0, 0, 0]
            ],
            [
                [0, 1, 0],
                [1, 0, 1],
                [0, 1, 0]
            ],
            [
                [0, 0, 0],
                [0, 1, 0],
                [0, 0, 0]
            ]
        ])
        # As before, a hypothetical expected output for illustration:
        expected_output_3d = np.array([
            [
                [0, 1, 0],
                [1, 0, 1],
                [0, 1, 0]
            ],
            [
                [1, 0, 1],
                [0, 0, 0],
                [1, 0, 1]
            ],
            [
                [0, 1, 0],
                [1, 0, 1],
                [0, 1, 0]
            ]
        ])
        result_3d = automata.life(initial_state_3d, 1, rules="3d")
        assert np.array_equal(result_3d, expected_output_3d)
