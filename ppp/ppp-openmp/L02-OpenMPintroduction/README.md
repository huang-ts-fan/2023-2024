# README.md

## Introduction to OpenMP on Imperial College Cluster

Welcome to your first experience with OpenMP programming and running jobs on the Imperial College high-performance computing (HPC) cluster. This guide will walk you through accessing the cluster, setting up your environment, compiling and running your first OpenMP program, and managing jobs using a queuing system.

### Accessing the Cluster

First, you need to log into the Imperial College cluster. This is done via SSH (Secure Shell), which allows you to securely access a remote computer. Use the following command, replacing `username` with your actual username provided by the college:

```sh
ssh username@login.cx3.hpc.ic.ac.uk
```

### Setting Up Your Environment

Once logged in, it's recommended to clone the necessary GitHub repository directly on the cluster. This way, you have all the required files available on the cluster's filesystem. You can also use VSCode to connect to the cluster remotely, which simplifies developing code directly on the server. Here's how to clone the repository:

```sh
git clone git@github.com:ese-msc-2023/ppp-openmp.git
cd ppp-openmp/L02-OpenMPintroduction
ls
```

The output should list several files, including `CMakeLists.txt`, `hello_world.cpp`, and `hello_world.pbs`, which are essential for building and running your program.

### Compiling the Program

Before compiling the program, create a build directory and load necessary modules such as GCC for the compiler and CMake for building the software:

```sh
mkdir -p build
cd build
module load GCC
module load CMake
cmake ..
make
```

These commands set up a dedicated build directory, load the necessary compiler and build tools, and compile the program using CMake and Make.

### Submitting Jobs to the Queue

The HPC uses a job scheduling system to manage the computing resources. In this case, we use the PBS (Portable Batch System) to submit jobs. To run your compiled program, submit it to the queue:

```sh
qsub ../hello_world.pbs
```

You can check the status of your job using:

```sh
qstat -u username
```

### Understanding the PBS Script

The `hello_world.pbs` file contains directives for the job scheduler:

- **Job Name and Resource Request**: Specifies the job name, number of CPUs, memory, and time required.
- **Output Files**: Defines where to store the output (`stdout`) and errors (`stderr`).
- **Environment Settings**: Sets the number of OpenMP threads (`OMP_NUM_THREADS=16`).
- **Execution Commands**: Includes commands to run your program and output system configuration to `lscpu.txt`.

### Viewing Output and Errors

After your job completes, you can view the output and any errors with:

```sh
cat stdout
cat stderr
```

If your program has any issues, the `stderr` file will contain the error messages. Additionally, the `lscpu.txt` file can be useful for debugging and understanding on which CPU your job was executed.

