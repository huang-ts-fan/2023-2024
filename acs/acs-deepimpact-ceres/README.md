# ACS-1-deepimpact

The deepimpact project involved modeling asteroids entering the atmosphere of a planet, and their potential catastrophic impacts.
Whilst powerful and accurate estimators for this already exist, the goal of this project was to perform estimations of the asteroid's
impact and damage much faster, allowing for action to be taken by the UK government on a smaller time scale.

Project Goals:

Development of a Numerical Simulator: The core of the project is the creation of a fast, accurate solver that can predict the path and 
interactions of the asteroids with the atmosphere. This simulator aims to consider various factors such as size, velocity, trajectory, and density/strength of the asteroid.

Hazard Mapping for the UK: Utilizing the simulator, deepimpact implements a hazard mapping tool. This tool will be instrumental in assessing the potential risks and impact zones, specifically focusing on the UK, and allowing the government to react swiftly and effectively.

A detailed explenation on the functions of the deepimpact module, how they work, and how they are called can be found in the Sphinx documentation for this project.

--------------------------------------------------------------------------------------

N.B:

A push and merge was made to the GitHub repository on Friday with a few lines of code 
added (but commented out) to highlight where these changes are and what they would need
to be for the code to run without errors. They were added to show understanding of the
root problems with the final version of our code, that we had not previously discovered,
but proved catastrophic for the final version.

## Installation

To install the module and any pre-requisites, from the base directory run
```
pip install -r requirements.txt
pip install -e .
```  

## Downloading postcode data

To download the postcode data
```
python download_data.py
```

## Automated testing

To run the pytest test suite, from the base directory run
```
pytest tests/
```

Note that you should keep the tests provided, adding new ones as you develop your code. If any of these tests fail it is likely that the scoring algorithm will not work.

## Documentation

To generate the documentation (in html format)
```
python -m sphinx docs html
```

See the `docs` directory for the preliminary documentation provided that you should add to.

## Example usage

For example usage see `example.py` in the examples folder:
```
python examples/example.py
```

## User Interface

We provide a user interface that allows users to observe the hazard of small asteroidshow under varying conditions on a map. Try this out in `UserInterface.ipynb`.

## More information

For more information on the project specfication, see the python notebooks: `ProjectDescription.ipynb`, `AirburstSolver.ipynb` and `DamageMapper.ipynb`.
