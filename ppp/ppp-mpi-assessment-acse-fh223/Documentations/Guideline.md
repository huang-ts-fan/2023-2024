# Parallel Simulation Code Documentation

## Overview

This document provides guidelines on how to compile and run our parallel simulation program using the MPI (Message Passing Interface) based on cpp. The program models chemical kinetics phenomena using a finite difference method for numerical calculations.

## Prerequisites

Before compiling and running the program, ensure the following prerequisites are met:

- **MPI Library**: The MPI libraries must be installed on the system. This library allows us to execute parallel processing programs.
- **C++ Compiler**:  Our main program is based on “C++”. To compile the program, you must use a "C++" compiler that supports MPI (e.g. the `mpicxx` compiler).

## Compilation Guide

To compile the program, follow these steps:

1. **Navigate to the Code Directory**: Open a terminal and change to the directory containing `Serial_Reaction_Equations.cpp` and `MPI_Neu.cpp` files. In the current code base, this is usually located in the root directory.
2. **Compile the Program**: Use the following command to compile the source code into an executable:
   ```bash
   mpicxx -o mpi_simulation MPI_Neu.cpp
   ```
   This command compiles `MPI_Neu.cpp` using the `mpicxx` compiler and generates an executable named `mpi_simulation`.

Tips: The `Serial_Reaction_Equations.cpp` file does not involve the use of the `MPI` library, and can be compiled and run as a regular C++ program.

## Running the Program

To run the program on local machine:

```bash
mpirun -np <number_of_processes> ./mpi_simulation
```

Replace `<number_of_processes>` with the number of MPI processes you wish to launch. The default number of processes used by the program should be **“number_of_processes = 4”**. 

```bash
mpirun -np 4 ./mpi_simulation
```

## Code Logic

### Data Structures

- **C1, C2**: Two-dimensional vectors storing the concentration of two chemicals across the simulation grid.
- **C1_old, C2_old**: Vectors used to hold the previous timestep's concentration data for computational updates.

### Key Functions

- **`grid_to_file`**: Outputs the current concentration data to files for analysis and visualization. Files are named based on the process rank and output iteration.
- **`do_iteration_neumann`**: Performs an iteration update using Neumann boundary conditions and MPI for data exchange between processes. We implement here the handling of boundary problems and **non-blocking peer-to-peer communication for parallel tasks.** 
- **`calc_constants`**: Calculates and sets essential constants for the simulation, such as time step `dt`, and grid spacing `dx`, `dy`.
- **`setup_data_profile`**: Initializes the grid's concentration profile, providing initial conditions for the simulation.
- **`main`**: The entry point of the program, handling MPI initialization, function calls for the simulation, and resource cleanup at the end. We have also included a timer here to compare the efficiency of running parallel and serial programs.

### Parallel Computation Logic

1. **Data Partitioning**: The entire grid is divided among processes, with each process responsible for a segment of the grid's computation. In the current version of the submitted code, we adopt a **vertical partitioning** strategy and design matching **MPI custom types for storing each whole row of data** to ensure the stability and accuracy of our boundary passing.
2. **Boundary Exchange**: Non-blocking communication using `MPI_Isend` and `MPI_Irecv` ensures that each process can acquire the necessary boundary data for its segment.
3. **Iteration Updates**: Each process updates its grid segment, `MPI_Waitall` waits for all communications to complete, then proceeds to the next time step.

### Boundary Conditions

**Neumann** boundary conditions are implemented, where the boundary grid points are set to the values of their adjacent interior points, ensuring a zero derivative at the boundaries.

## Conclusion

We have designed our parallel program to run substantially faster compared to the serial version, saving significant time costs. This document is intended to guide the user in compiling and running the files in the code repository and understanding the corresponding program design logic.

