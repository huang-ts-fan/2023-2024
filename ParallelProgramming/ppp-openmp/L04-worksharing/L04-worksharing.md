# Shared Memory Programming with OpenMP

## Lecture 04: Work sharing directives

### Learning Objectives

By the end of this lecture, you should be able to:

- **Understand Work Sharing Directives**: Identify and explain the different types of work sharing directives within OpenMP, such as parallel loops and the single, master, and combined directives.
- **Implement Parallel Loops**: Apply the parallel loop construct to divide loop iterations among multiple threads, improving the efficiency of code execution in parallel regions.
- **Use Scheduling Clauses Effectively**: Describe how the `schedule` clause can be used to manage the distribution of loop iterations and choose the appropriate scheduling type based on the workload and data locality.
- **Control Thread Execution with `single` and `master` Directives**: Distinguish between the `single` and `master` directives for controlling which threads execute specific parts of the code.
- **Optimize Parallel Execution with `nowait` Clause**: Utilize the `nowait` clause to remove unnecessary barrier synchronizations, enhancing the performance of parallel regions.

### Work sharing directives

- Directives which appear inside a parallel region and indicate how
  work should be shared out between threads.
  - Parallel do/for loops.
  - Single directive.
  - Master directive.

### Parallel do loops

- Loops are the most common source of parallelism in most codes.
  Parallel loop directives are therefore very important!
- A parallel do/for loop divides up the iterations of the loop between
  threads.
- The loop directive appears inside a parallel region and indicates
  that the work should be shared out between threads, instead of
  replicated
- There is a synchronisation point at the end of the loop: all threads
  must finish their iterations before any thread can proceed

``` c++
#pragma omp for [clauses]
for (...){
  // ...
}
```

### Restrictions in C/C++

- Because the `for` loop in C/C++ is a general while loop, there are
  restrictions on the form it can take.
- It has to have a determinable trip count - it must be of the form:

``` c++
for (var = a; var logical-op b; incr-exp) {
}
```

- Where `logical-op` is one of `<`, `<=`, `>`, `>=`

- and `incr-exp` is `var = var +/- incr` or semantic equivalents such
  as `var++`.

- **Cannot** modify **var** within the loop body.

### Parallel loops: example

``` c++
#pragma omp parallel shared(a, b)
{
#pragma omp for
  for (int i=0;i<n;i++){
    b[i] = (a[i]*a[i-1])*0.5;
  }
}
```

### Combined parallel for directive

This construct is so common that there is a shorthand form which
combines `parallel` region and `for` directives:

``` c++
#pragma omp parallel for [clauses]
for (...) {
  // ...
}
```

### Parallel loops: example {#parallel-loops-example}

``` c++
#pragma omp parallel for shared(n, a, b)
for (int i=0;i<n;i++){
  b[i] = (a[i]*a[i-1])*0.5;
}
```

### Clauses

- The `for` directive can take `private`, `firstprivate` and
  `reduction` clauses which refer to the scope of the loop.
- Note that the parallel loop index variable is `private` by default.
- The `parallel for` directive can take all clauses available for
  `parallel` directive.
- **Beware!** `parallel for` directive is not the same as `for`
  directive nor the same as `parallel` directive.

### Dividing work among threads

- With no additional clauses, the `for` directive will partition the
    iterations as equally as possible between the threads.
- However, this is implementation dependent, and there is still some
    ambiguity:
  - For example, given 7 iterations and 3 threads, work might be
        partitioned as 3,3,1 or 3,2,2.

### `schedule` clause

- The `schedule` clause gives a variety of options for specifying
    which loops iterations are executed by which thread.
- Syntax:

``` c++
schedule(kind[, chunksize])
```

where `kind` is one of `static`, `dynamic`, `guided`, `auto` or
`runtime` and `chunksize` is an integer expression with positive value.

- For example,

``` c++
#pragma omp for schedule(dynamic, 4)
```

### `static` schedule

- With no `chunksize` specified, the iteration space is divided into
  (approximately) equal chunks, and one chunk is assigned to each
  thread in order (**block** schedule).
- If `chunksize` is specified, the iteration space is divided into
  chunks, each of `chunksize` iterations, and the chunks are assigned
  cyclically to each thread in order (**block cyclic** schedule).

![](static_schedule.png)

### `dynamic` schedule

- The `dynamic` schedule divides the iteration space up into chunks of
  size *chunksize*, and assigns them to threads on a
  *first-come-first-served* basis.
  - i.e. as a thread finish a chunk, it is assigned the next chunk
    in the list.
- When no *chunksize* is specified, it defaults to 1.

### `guided` schedule

- The `guided` schedule is similar to `dynamic`, but the chunks start
  off large and get smaller exponentially.
- The size of the next chunk is proportional to the number of
  remaining iterations divided by the number of threads.
- The *chunksize* specifies the minimum size of the chunks.
- When no *chunksize* is specified it defaults to 1.

### `dynamic` and `guided` schedules

![](dynamic_guided_schedule.png)

### `auto` schedule

- Lets the runtime have full freedom to choose its own assignment of
    iterations to threads
- If the parallel loop is executed many times, the runtime can evolve
    a good schedule which has good load balance and low overheads.

### `runtime` schedule

- Allows the schedule to be set using the environment variable
  `OMP_SCHEDULE`
  - e.g. `export OMP_SCHEDULE=dynamic,1`
- Convenient for experimenting with schedules and chunksizes without
  having to recompile.

### Choosing a schedule

When to use which schedule?

- `static` best for load balanced loops - least overhead.
- `static,n` good for loops with mild or smooth load imbalance, but
  can induce overheads.
- `dynamic` useful if iterations have widely varying loads, but ruins
  data locality (remember NUMA).
- `guided` often less expensive than `dynamic`, but beware of loops
  where the first iterations are the most expensive!
- `auto` allows compiler-specific options.

### `single` directive

- Indicates that a block of code is to be executed by a single thread
  only.
- The first thread to reach the `single` directive will execute the
  block.
- There is a synchronisation point at the end of the block: all the
  other threads wait until block has been executed.
- Directive must contain a structured block: cannot branch into or out
  of it.
- The `single` directive can take `private` and `firstprivate`
  clauses.

``` c++
#pragma omp single [clauses]
{
   // ..
}
```

### `single` directive: example:

``` c++
#pragma omp parallel
{
  setup(x);
    
#pragma omp single
  {
    input(y);
  } 

  work(x,y);  
}
```

### `nowait` clause

- The implicit barrier synchronization at the end of the `for` or
  `single` directive can be removed by adding the `nowait` clause.
  - Use with care as it can easily introduce race conditions!

``` c++
#pragma omp parallel
{
  foo(...);
#pragma omp for nowait
  for (...) {
  }
  bar(...);
}
```

### `master` directive

- Indicates that a block of code should be executed by the master
  thread (thread 0) only.
- There is **no synchronisation** at the end of the block: other
  threads skip the block and continue executing: Note this is
  different from `single` in this respect.
- Syntax:

``` c++
#pragma omp master
{
 // structured block
}
```

### Summary

### Lecture Summary: Work Sharing Directives in OpenMP

- **Introduction to Work Sharing Directives**: We explored various directives that control how tasks are divided among threads within OpenMP parallel regions. These include the parallel loop (for/do) directives, which are crucial for splitting the iterations of loops among threads to enhance computational efficiency.

- **Parallel Loop Constructs**: The lecture detailed how parallel do/for loops distribute loop iterations across threads. We emphasized the importance of synchronization at the end of these loops, ensuring that all threads must complete their assigned iterations before proceeding.

- **Loop Scheduling and Its Impact**: Various scheduling strategies (`static`, `dynamic`, `guided`, `auto`, and `runtime`) were discussed, illustrating how they influence the distribution of loop iterations. We reviewed how these schedules can be applied to optimize performance based on different workload characteristics.

- **Detailed Directive Usage**: The combined `parallel for` directive, which merges the functionalities of a parallel region and a for loop into a concise form, was highlighted. This directive simplifies the parallelization of loops by automatically handling thread creation and distribution of iterations.

- **Managing Data in Parallel Loops**: Clauses such as `private`, `firstprivate`, and `reduction` play critical roles in managing how data is handled within parallel loops. For instance, the `private` clause ensures that each thread has its own copy of a variable, whereas `reduction` helps in performing thread-safe reduction operations on variables across all threads.

- **Advanced Scheduling Techniques**: The lecture provided insights into the practical applications of scheduling clauses, discussing how to select the appropriate scheduling type (`static` vs. `dynamic` vs. `guided`) based on the computational load and data access patterns. This section helped clarify how different scheduling options can be leveraged to balance load and optimize parallel execution.

- **Single and Master Directives**: We examined the `single` and `master` directives, which are used to restrict the execution of specific code blocks to a single thread or the master thread, respectively. These directives are essential for operations that must not be parallelized, such as initialization steps or operations that involve handling I/O.

- **Effective Use of the `nowait` Clause**: The `nowait` clause was discussed as a way to optimize performance by eliminating the implicit barrier at the end of work sharing constructs, allowing threads to proceed without waiting for others to finish.
