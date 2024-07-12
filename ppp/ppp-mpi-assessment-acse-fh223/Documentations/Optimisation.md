### Optimisation of MPI Parallel Simulation Code for Efficiency Improvement

---

#### 1. Project Background

This project aims to solve the reaction-diffusion equation on a 2D grid with `Neumann` or `Periodic` boundary conditions using MPI parallelisation. The initial code is a serial implementation that employs `Neumann` and `Periodic` boundary conditions. The goal is to optimize this serial code for parallel execution to enhance computational efficiency, especially for large-scale simulations.

---

#### 2. Initial Serial Implementation

The initial code is a simple serial implementation with fixed grid dimensions and Neumann boundaries. It employs a `vector of vectors`, which is less efficient than using contiguous memory allocation. The structure of the serial code is as follows:

1. **Grid and Time Step Calculation**: Calculate the grid spacing (`dx`, `dy`) and time step (`dt`).
2. **Data Initialisation**: Initialize the concentration profiles `C1` and `C2`.
3. **Single Iteration Computation**: Compute new concentrations for each grid point.
4. **Data Output**: Write the concentration profiles to files at specified time intervals.

---

#### 3. Parallel Implementation and Optimisation

##### 3.1 Parallelisation with MPI

To parallelise the code, we used the MPI library. The parallelisation process involved several key steps:

- **MPI Initialisation**: Initialise MPI environment using `MPI_Init`, obtain the rank of each process with `MPI_Comm_rank`, and determine the total number of processes with `MPI_Comm_size`.
- **Data Decomposition**: Divide the 2D grid into subgrids, with each process handling a subgrid(strip). We use vertical decomposition to distribute the columns among processes.
- **Non-blocking Communication**: Use `MPI_Isend` and `MPI_Irecv` for non-blocking data exchange to minimise communication overhead.
- **Boundary Condition Handling**: Implement "Nuemann" and "Periodic" boundary conditions and ensure correct and timely data updates at the boundaries.
- **Result Collection and Output**: Each process computes its subgrid(strip) and outputs results independently.

**Tips**: Output files from parallel simulations can be combined to generate animations using our Python scripts.

##### 3.2 Performance Optimisation Techniques

Several optimisation techniques were employed to enhance the performance of the parallel implementation:

- **Pointer Swapping**: Instead of copying data between grids, pointers to the grids were swapped to reduce memory operation time.
- **Data Communication Optimisation**: Non-blocking communication functions (`MPI_Isend` and `MPI_Irecv`) were used, and batch communication operations were implemented.
- **Load Balancing**: The computational load was evenly distributed among processes to ensure balanced work distribution.
- **Memory Optimisation**: Data structures were optimised to reduce memory usage and improve cache efficiency.

---

#### 4. Performance Comparison: Serial vs Parallel

We compared the execution times of the serial and parallel implementations (with nuemann boundary condition). The tests were conducted on a multi-core machine with the same configuration, using a grid size of `imax=301` and `jmax=301`, a time step of 0.1, and a total simulation time of 30.0.

| Execution Mode | Number of Processes | Execution Time (seconds) |
| -------------- | ------------------- | ----------------------- |
| Serial         | 1                   | 256.986                    |
| Parallel       | 2                   | 133.446                     |
| Parallel       | 4                   | 68.5135                     |
| Parallel       | 8                   | 129.518                     |

The results show that parallel computing significantly reduces the execution time. The execution time decreases as the number of processes increases (the number of processes increases from 1 to 4). However, a further increase in the number of processes (from 4 to 8) has started to lead to diminishing returns due to communication overhead, probably because our boundaries are too narrow and transmitting boundary information consumes more time. Also, as we open more processes, we consume more time waiting for the processes to complete their tasks.

---

#### 5. Potential Optimisation Areas

Our application of MPI parallelisation has led to significant performance gains, but there are still other areas of optimisation to be explored:

##### 5.1 Communication Optimisation

- **Reduce Communication Frequency**: Optimise the algorithm to minimise the frequency of communication, especially during boundary condition handling.

##### 5.2 Load Balancing

- **Dynamic Load Balancing**: Adjust the distribution of computational tasks dynamically based on runtime load to avoid overloading any single process.

##### 5.3 Memory Optimisation

- **Reduce Memory Usage**: Optimise data structures to minimise memory usage without compromising accuracy.
- **Cache Optimisation**: Utilize caching techniques to improve data access speeds and reduce memory access times.

##### 5.4 Parallel Algorithm Optimisation

- **Improved Parallel Algorithms**: Research and implementation of more efficient parallel algorithms to further improve computational efficiency. We simulated diffusion using a square grid setup, and in a grid with a structure similar to this, changing the subdomain division rule from a strip to a shape closer to a square may be effective in improving the running efficiency of each process, thus saving us a lot of time.
- **Multi-level Parallelism**: Combining the use of multi-threading and multi-processing techniques to fully utilise multi-core and multi-node computing resources.

---