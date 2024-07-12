from setuptools import setup, find_packages

with open('requirements.txt') as f:
    required = f.read().splitlines()

setup(
    name="Olga", 
    version = "0.1",
    description = "Hurricaaaaaanes",
    install_requires = required,
    license='MIT',
    packages=find_packages(exclude=['notebooks*'])
)