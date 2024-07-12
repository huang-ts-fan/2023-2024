import numpy as np
import pandas as pd
import deepimpact
from pathlib import Path


def test_sea_scenario():
    inputs = {
        "radius": 35,
        "angle": 45,
        "strength": 1e7,
        "density": 3000,
        "velocity": 19e3,
        "dt": 0.25
    }
    earth = deepimpact.Planet()
    result = earth.solve_atmospheric_entry(**inputs)

    # Get the test_directory
    test_dir = Path(__file__).parent
    filename = test_dir / "scenario.npz"

    scenario_data = np.load(filename)

    df = pd.DataFrame({
        'velocity': scenario_data['velocity'],
        'mass': scenario_data['mass'],
        'angle': scenario_data['angle'],
        'altitude': scenario_data['altitude'],
        'distance': scenario_data['distance'],
        'radius': scenario_data['radius'],
        'time': np.arange(0, 10, 0.25)
    })

    result = result.head(len(df))

    result_last_row = result.iloc[-1]
    scenario_last_row = df.iloc[-1]

    for result, expected in zip(result_last_row, scenario_last_row):
        assert np.isclose(result, expected, rtol=0.01)


def test_sea_airburst():
    inputs = {
        "radius": 18,
        "angle": 45,
        "strength": 1e7,
        "density": 3000,
        "velocity": 1e4,
        "dt": 0.25
    }
    earth = deepimpact.Planet()
    result = earth.solve_atmospheric_entry(**inputs)

    assert result['altitude'].iloc[-1] > 0


def test_sea_crater():
    inputs = {
        "radius": 18,
        "angle": 45,
        "strength": 1e9,
        "density": 3000,
        "velocity": 1e4,
        "dt": 0.25
    }
    earth = deepimpact.Planet()
    result = earth.solve_atmospheric_entry(**inputs)

    assert result['altitude'].iloc[-1] < 0


def test_sea_rebound_stop():
    inputs = {
        "init_altitude": 100e3,
        "radius": 18,
        "angle": 2,
        "strength": 1e7,
        "density": 3000,
        "velocity": 1e4,
        "dt": 0.25
    }
    earth = deepimpact.Planet()
    result = earth.solve_atmospheric_entry(**inputs)

    assert result['angle'].iloc[-1] < 0


def test_sea_terminal_velocity_stop():
    inputs = {
        "radius": 5,
        "angle": 20,
        "strength": 1e6,
        "density": 1500,
        "velocity": 12e4,
        "dt": 0.01
    }
    earth = deepimpact.Planet(Ch=0)
    result = earth.solve_atmospheric_entry(**inputs)

    assert result['altitude'].iloc[-1] > 0


def test_calculate_energy_airburst_and_analyse_outcome():
    inputs = {
        "radius": 18,
        "angle": 45,
        "strength": 1e7,
        "density": 3000,
        "velocity": 1e4,
        "dt": 0.25
    }
    earth = deepimpact.Planet()
    result = earth.solve_atmospheric_entry(**inputs)
    energy_df = earth.calculate_energy(result)
    outcome = earth.analyse_outcome(energy_df)

    assert outcome["outcome"] == "Airburst"
    assert outcome["burst_altitude"] > 0


def test_calculate_energy_crater_and_analyse_outcome():
    inputs = {
        "radius": 18,
        "angle": 45,
        "strength": 1e9,
        "density": 3000,
        "velocity": 1e4,
        "dt": 0.25
    }
    earth = deepimpact.Planet()
    result = earth.solve_atmospheric_entry(**inputs)
    energy_df = earth.calculate_energy(result)
    outcome = earth.analyse_outcome(energy_df)

    assert outcome["outcome"] == "Cratering"
    assert outcome["burst_altitude"] < 0
