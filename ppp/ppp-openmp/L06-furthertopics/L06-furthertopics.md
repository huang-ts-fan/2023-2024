# Shared Memory Programming with OpenMP

## Lecture 06: Further topics in OpenMP

### Overview

- Nested parallelism
- Orphaned constructs
- Thread-private globals
- Timing routines

### Nested parallelism

- Nested parallelism is supported in OpenMP.
- If a `parallel` section is encountered within another `parallel`
  section, a new team of threads will be created.
- This is enabled with the `OMP_NESTED` environment variable or the
  `omp_set_nested()` function.
- Not often needed, but can be useful if the outer level does not
  contain enough parallelism
- Usually disabled by default
  - Do not enable nested parallelism unless you are using it!
- If nested parallelism is disabled, code with nested parallel regions
    will still execute, but the inner teams will contain only one
    thread.

### Nested parallelism: Example

``` c++
#pragma omp parallel
{
  int myid = omp_get_thread_num();
  if (myid==0) { 
#pragma omp parallel for
    for (int i=0;i<n;i++) {
      x[i] = 1.0;
    }
  }else if (myid==1){
#pragma omp parallel for
    for (int j=0;j<n;j++) {
      y[j] = 2.0;
    }
  }
}
```

### Controlling the number of threads

- Setting the environment variable `export OMP_NUM_THREADS=2,4` will
  use 2 threads at the outer level and 4 threads for each of the inner
  teams.
- Alternatively you can use `omp_set_num_threads()` or the
  `num_threads` clause on the parallel region.

### `omp_set_num_threads()`

- Useful if you want inner regions to use different numbers of
    threads:

``` c++
omp_set_num_threads(2);

#pragma omp parallel for
for (int i=0; i<4; i++) {
  omp_set_num_threads(innerthreads[i]);

#pragma omp parallel for 
  for (int j=0; j<N; j++) {
    a[j][i] = b[j][i] * 17;
  }
}
```

- The function call overrides the value(s) in the environment variable
  `OMP_NUM_THREADS`.

### `num_threads` clause

- Another way to control the number of threads used at each level is
  with the `num_threads` clause:

``` c++
#pragma omp parallel for num_threads(2)
for (int i=0; i<4; i++) {

#pragma omp parallel for num_threads(innerthreads[i])
  for (int j=0; j<N; j++) {
    a[j][i] = b[j][i] * 17; 
  }
}
```

- The value set in the clause overrides the value in the environment
    variable `OMP_NUM_THREADS` and that set by `omp_set_num_threads()`.

### More control\... {#more-control}

- Can also control the maximum number of threads running at any one
    time.

`export OMP_THREAD_LIMIT=64`

- \...and the maximum depth of nesting
    `export OMP_MAX_ACTIVE_LEVELS=2` or call
    `omp_set_max_active_levels()`.

### Utility routines for nested parallelism

- `omp_get_level()`
  - Returns the level of parallelism of the calling thread.
  - Returns 0 in the sequential part.
- `omp_get_active_level()`
  - Returns the level of parallelism of the calling thread, ignoring
        levels which are inactive (teams only contain one thread).
- `omp_get_ancestor_thread_num(level)`
  - Returns the thread ID of this thread's ancestor at a given
        level.
  - ID of my parent:
        `omp_get_ancestor_thread_num(omp_get_level()-1)`.
- `omp_get_team_size(level)`
  - Returns the number of threads in this thread's ancestor team at
        a given level.

### Nested loops

- For perfectly nested rectangular loops we can parallelise multiple
    loops in the nest with the `collapse` clause:

``` c++
#pragma omp parallel for collapse(2)
for (int i=0; i<N; i++) {
  for (int j=0; j<M; j++) {
    // ...
  }
}
```

- Argument is number of loops to collapse starting from the outside.
- Will form a single loop of length `NxM` and then parallelise and
  schedule that.
- Useful if `N` is O(number of threads) so parallelising the outer
  loop may not have good load balance.
- More efficient than using nested teams.

### Synchronisation in nested parallelism

- Note that barriers (explicit or implicit) only affect the innermost
  enclosing parallel region.
- No way to have a barrier across multiple teams
- In contrast, critical regions, atomics and locks affect all the
  threads in the program.
- If you want mutual exclusion within teams but not between them, need
  to use locks (or atomics).

### Orphaned directives

- Directives can be present in functions called from inside parallel
  regions
- Example:

``` c++
#pragma omp parallel
{
  foo();
}

void foo() {
#pragma omp for
  for (int i=0; i<N; i++) {
    a[i] += 23.5;
  }
}
```

- This is very useful, as it allows a modular programming style.
- But it can also be rather confusing if the call tree is complicated:
  - Q. What happens if `foo()` is also called from outside a
        parallel region?
  - A. The worksharing loop is all executed by the master thread.
- There are some extra rules about data scope attributes.

### Data scoping rules

- When we call a function from inside a parallel region:
  - Variables in the argument list inherit their data scope
    attribute from the calling routine.
  - Global variables in C/C++ unless declared `threadprivate` (see
    later).
- `static` local variables in C/C++ are shared.
- All other local variables are private.

### `threadprivate` global variables

- It can be convenient for each thread to have its own copy of
  variables with global scope (e.g. or file-scope and namespace-scope
  variables in C/C++).
- Outside parallel regions and in `master` directives, accesses to
  these variables refer to the master thread's copy.

### `#pragma omp threadprivate (list)`

- This directive must be at file or namespace scope, after all
  declarations of variables in `list` and before any references to
  variables in `list`. See standard document for other restrictions.
- The `copyin` clause allows the values of the master thread's
  `threadprivate` to be copied to all other threads at the start of a
  parallel region.

### Timing routines

- OpenMP supports a portable timer:
  - `double omp_get_wtime(void)` returns current wall clock time
    relative to arbitrary origin.
  - `double omp_get_wtick(void)` return the clock precision.

### Using timers example

``` c++
double start_time = omp_get_wtime();

// work to be timed

double wtime = omp_get_wtime() - start_time;
```

- Note: timers are local to a thread: must make both calls on the same
  thread.
- No guarantees about resolution, but you can query it using
  `omp_get_wtick()`.
