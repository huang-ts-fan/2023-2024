# Shared Memory Programming with OpenMP

## Assignment 2: Area of the Mandelbrot Set

### Introduction

This exercise demonstrates some of the issues that need to be considered when
adapting serial code to a parallel version.

*The Mandelbrot Set* is the set of complex numbers `c` for which the iteration:

$$z_{i+1} = z_i^2 + c$$

does not diverge from the initial condition $z=c$. To approximate whether a
point $c$ lies in the set, a finite number of iterations are performed, and if
the condition $|z| > 2$ is satisfied, then the point is considered to be outside
the Mandelbrot Set. What we are interested in is calculating the area of the
Mandelbrot Set. There is no known theoretical value for this, and estimates are
based on a procedure similar to that used here.

The method we shall use generates a grid of points in a box of the complex plane
containing the upper of the (symmetric) Mandelbrot Set. Then each point is
iterated using the equation above a finite number of times (say 2000). If within
that number of iterations, the threshold condition $|z| > 2$ is satisfied, then
that point is considered to be outside of the Mandelbrot Set. Then counting the
number of points within the Set and those outside will lead to an estimate of
the area of the Set.

### Objective

Parallelize the serial code provided using the OpenMP. This may include:
1. OpenMP compiler directives.
2. Environment variables.
3. OpenMP API calls.
4. [Challenge] try different compilers and compiler flags.

### Suggestions to get you started

* Start a parallel region before the main loop.
  * Ensure that any private, shared or reduction variables within the region are correctly declared.
* Distribute the outermost loop across the threads available.
  * Each thread has an equal amount of computation to perform.

### Evaluation

You can evaluate your solution on the cluster by submitting `assessment-2/evaluate.pbs` and examining the output files generated. The script will run your code with a different number of threads and compare the results. It will also calculate the speedup and efficiency for each case.

```bash
cd your_repo_root
qsub assessment-2/evaluate.pbs
```

#### 1. Verify correctness

The most important test is that you are getting the correct answer. When running in parallel you should be getting the same answer as the serial version of the code. If you are not, then you need to investigate why. Use `OMP_NUM_THREADS` to test using a different number of threads.

#### 2. Calculating Parallel Speedup and Efficiency

Parallel computing aims to decrease the time it takes to run a program by dividing the work among multiple processing elements. Two key metrics used to evaluate the effectiveness of parallelization are **parallel speedup** and **parallel efficiency**. Here’s a step-by-step guide on how to calculate these metrics:

##### **Parallel Speedup**

Parallel speedup is a measure of how much faster a parallel algorithm executes compared to its sequential counterpart. It is calculated as follows:

$$ Speedup, S = \frac{T_s}{T_p} $$

Where:
- $T_s$ is the execution time of the best sequential algorithm (running on a single processor).
- $T_p$ is the execution time of the parallel algorithm (running on multiple processors).

**Steps to calculate Speedup:**
- Measure the time it takes to execute the task using a single processor.
- Measure the time it takes to execute the same task using multiple processors.
- Divide the time of the single processor by the time of multiple processors.

**Example:**
If a task takes 200 seconds to complete on one processor and 40 seconds to complete on five processors, the speedup is:

$$ S = \frac{200}{40} = 5 $$

This means the parallel algorithm is 5 times faster than the sequential algorithm.

##### **Parallel Efficiency**

Parallel efficiency is a measure of the utilization of all processors in the system during the parallel execution. It gives an idea of how effectively the parallelism is being exploited. It is calculated as follows:

$$Efficiency, E =  \frac{S}{p} = \frac{T_s}{p \times T_p} $$

where:
- $S$ is the speedup as calculated above.
- $p$ is the number of processors used in the parallel algorithm.

**Steps to calculate Efficiency:**
- Calculate the speedup, S, as described above.
- Count the number of processors used in the parallel execution.
- Divide the speedup by the number of processors.

**Example:**
Using the speedup example above with 5 processors:

$$ E = \frac{5}{5} = 1 $$

An efficiency of 1 (or 100% when expressed as a percentage) indicates perfect scaling, where each processor contributes equally without any loss of computing time or resources.

**Interpreting Efficiency:**
- An efficiency close to 1 indicates good scaling: the overhead of managing parallel tasks does not significantly impact performance.
- Efficiency less than 1 indicates that there are diminishing returns with the addition of more processors, often due to communication overhead, synchronization delays, or idle processors.

Summary: Understanding these speedup and parallel efficiency can help developers and researchers optimize parallel algorithms and hardware configurations. Speedup shows the raw performance gain, while efficiency provides insight into how well the parallel system is working relative to its capacity. For most practical purposes, achieving high efficiency is as crucial as achieving high speedup to ensure that resources are being used optimally.

#### Amdahl's Law

Amdahl's Law is a fundamental principle used to predict the theoretical maximum improvement in parallel processing systems. It was formulated by Gene Amdahl in 1967 and provides an insight into the limitations of parallel computing.

#### Description of Amdahl's Law

Amdahl's Law states that the speedup of a program using multiple processors in parallel computing is limited by the time needed for the sequential fraction of the program. The law can be expressed with the following formula:

$$Speedup, S = \frac{1}{(1 - P) + \frac{P}{N}} $$

Where:
- $P$ is the proportion of the program that can be parallelized.
- $N$ is the number of processors.
- $1 - P$ is the proportion of the program that must be executed sequentially.

##### Implications of Amdahl's Law

The key takeaway from Amdahl's Law is that adding more processors will eventually lead to diminishing returns because of the sequential part of the program that cannot be parallelized. Even if you increase the number of processors infinitely, the speedup of the application will approach a limit, which is determined by the sequential portion of the application.

For instance, if 95% of a program can be parallelized, the maximum theoretical speedup using Amdahl’s Law would be:

$$ \text{Speedup} = \frac{1}{(1 - 0.95) + \frac{0.95}{N}} $$

As $N$ approaches infinity, the speedup approaches $\frac{1}{0.05} = 20$. This means no matter how many additional processors are used, the speedup of the program cannot exceed 20 times.

##### Why Perfect Parallelization is Not Possible

Amdahl's Law highlights a critical barrier to perfect parallelization due to the presence of a sequential part in most tasks. Here are the primary reasons why achieving perfect parallelization is not feasible:

- **Sequential Bottlenecks**: Certain parts of a program inherently need to be processed in a specific sequence. For example, a calculation that requires the result from a previous step cannot be parallelized.
  
- **Overhead Costs**: Parallel programs incur overhead from initializing and managing multiple processors, coordinating between threads, and merging results. This overhead can sometimes offset the gains from parallel processing.

- **Resource Limitations**: Practical limitations in terms of memory access, bandwidth, and communication between processors also prevent ideal scaling.

- **Data Dependencies**: Often, tasks are dependent on data generated by other tasks, requiring synchronization and communication, which add to the overhead and reduce the efficiency of parallel execution.

Conclusion: Amdahl's Law is a critical concept in parallel computing, setting a theoretical limit to the benefits of parallelization. It helps in understanding the importance of the sequential part of a task and guides developers on the potential speedup that can be achieved by adding more processors. Understanding these limitations is crucial for designing efficient parallel algorithms and selecting appropriate tasks for parallelization.