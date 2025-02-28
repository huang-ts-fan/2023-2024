# Patterns for Parallel Programming in Python - MPI assessment


## Submission due 5pm BST Friday 17th May 2024

Please see the [Coursework Assignment brief](Coursework_Assignment.pdf) for full details of the assessment. Your work must be uploaded here.

## Code Repository Structure Overview:
- **Documentations:** Contains all the documentation files.
- **serial_out_neu:** Contains the produced files from `Serial_Reaction_Equations.cpp` with Neumann Boundary Condition.
- **serial_out_periodic:** Contains the produced files from `Serial_Reaction_Equations.cpp` with Periodic Boundary Condition. 
- **MPI_out_neu:** Contains the produced files from `MPI_Neu.cpp`. 
- **MPI_out_periodic:** Contains the produced files from `MPI_Periodic.cpp`. 
- **Videos:** The animations generated by reading the files stored in `serial_out_neu`, `MPI_out_neu`, `serial_out_periodic`, `MPI_out_periodic`using Python will be stored in this folder in `mp4` format.
- **Serial_Reaction_Equations.cpp:** The source code for the serial version of the simulation program.
- **MPI_Neu.cpp:** The source code for the parallel version of the simulation program using MPI with Neumann boundary conditions.
- **MPI_Periodic.cpp:** The source code for the parallel version of the simulation program using MPI with periodic boundary conditions.
- **Serial_Video.py:** Python script to generate animations from the output files of the serial simulation.
- **MPI_Video.py:** Python script to generate animations from the output files of the parallel simulation.


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

For more information, please refer to the [Documentations](Documentations/README.md).