# Shared Memory Programming with OpenMP

## Lecture 07: OpenMP Tips, tricks and gotchas

### Directives

- Mistyping the sentinel (e.g. `#pragma opm`) typically raises no
  error message.
  - Extra nasty bug if it is something like `#pragma opm atomic` as
    it creates a race condition!
  - Write a script to search your code for your common typos

### Writing code that works without OpenMP too

- The preprocessor macro `_OPENMP` is defined if code is compiled with
  the OpenMP switch.
  - You can use this to conditionally compile code so that it works
      with and without OpenMP enabled.
- If you want to link dummy OpenMP library routines into sequential
  code, there is code in the standard you can copy (e.g. Appendix A in
  4.0).

### Parallel regions

- The overhead of executing a parallel region is typically in the tens
    of microseconds range
  - Depends on compiler, hardware, no. of threads
- The sequential execution time of a section of code has to be several
  times this to make it worthwhile parallelising.
- If a code section is only sometimes long enough, use the `if` clause
  to decide at runtime whether to go parallel or not.
  - Overhead on one thread is typically much smaller (\<1μs).

### Is my loop parallelisable?

- Quick and dirty test for whether the iterations of a loop are
  independent.
- Run the loop in reverse order!!
- Not infallible, but counterexamples are quite hard to construct.

### Loops and nowait

``` c++
#pragma omp parallel
{
#pragma omp for schedule(static) nowait
  for(i=0;i<N;i++){
    a[i] = ...
  }

#pragma omp for schedule(static)
  for(i=0;i<N;i++){
    ... = a[i];
  }
}
```

- This is safe so long as the number of iterations in the two loops
  and the schedules are the same (must be static, but you can specify
  a chunksize).
- Guaranteed to get same mapping of iterations to threads.

### Default schedule

- Note that the default schedule for loops with no schedule clause is
  implementation defined.
- Does not have to be `static`.
- In practice, it nearly always is, nevertheless you should not rely
  on this!
- Also note that `schedule(static)` does not completely specify the
  distribution of loop iterations.
  - Do not write code that relies on a particular mapping of
    iterations to threads.

### Tuning the chunksize

- Tuning the chunksize for static or dynamic schedules can be tricky
  because the optimal chunksize can depend quite strongly on the
  number of threads.
- It is often more robust to tune the *number of chunks per thread*
  and derive the chunksize from that.
  - Chunksize expression does not have to be a compile-time
    constant.

### `single` or `master`?

- Both constructs cause a code block to be executed by one thread
  only, while the others skip it: which should you use?
- `master` has lower overhead (it is just a test, whereas `single`
  requires some synchronisation).
- But beware that `master` has no implied barrier!
- If you expect some threads to arrive before others, use `single`,
  otherwise use `master`.

### Data sharing attributes

- Do not forget that private variables are uninitialised on entry to
  parallel regions!
- Can use `firstprivate`, but it's more likely to be an error.
  - Use cases for firstprivate are surprisingly rare.

### `default(none)`

- The default behaviour for parallel regions and worksharing construct
  is `default(shared)`.
- This is extremely dangerous - makes it far too easily to
  accidentally share variables.
- Possibly the worst design decision in the history of OpenMP!
- Always, always use `default(none)`.
  - No exceptions!
  - Everybody suffers from *variable blindness*.

### Spot the bug!

``` c++
#pragma omp parallel for private(temp)
for (i=0;i<N;i++){
  for (j=0;j<M;j++){
    temp = b[i]*c[j];

    a[i][j] = temp*temp+d[i]; 
  }
}
```

- May always get the right result with sufficient compiler
  optimisation!

### Huge long loops

- What should you do in this situation? (typical old-fashioned code)

``` c++
for(int i=0;i<n;i++){ 
  ... several pages of code referencing 100+ variables
}
```

- Determining the correct scope (private/shared/reduction) for all
  those variables is tedious, error prone and difficult to test
  adequately.

- Start by refactoring sequential code to:

``` c++
for(int i=0;i<n;i++){ 
   loopbody(...);
}
```

- Make all loop temporary variables local to loopbody().
  - And/or declare temporaries in the scope of the loop body.
- Pass the rest through argument list.
- Much easier to test for correctness!
- Then parallelise\...\...

### Reduction race trap

``` c++
#pragma omp parallel shared(sum, b)
{
  sum = 0.0;

#pragma omp for reduction(+:sum)
  for(i=0;i<n:i++) {
    sum += b[i];
  }

  ... = sum; 
}
```

-   There is a race between the initialisation of `sum` and the updates
    to it at the end of the loop.

### Critical and atomic

- You can not protect updates to shared variables in one place with
  atomic and another with critical, if they might contend.
- No mutual exclusion between these:
  - Critical protects code, atomic protects memory locations.

``` c++
#pragma omp parallel
{ 
#pragma omp critical** 
  a+=2; 

#pragma omp atomic
  a+=3;
}
```

### Allocating storage based on number of threads

- Sometimes you want to allocate some storage whose size is determined
  by the number of threads.
  - But how do you know how many threads the next parallel region
      will use?
- Can call `omp_get_max_threads()`. The number of threads used for the
  next parallel region will not exceed this
  - Except if a `num_threads` clause is used.
- Note that the implementation can always deliver fewer threads than
  this value.
  - If your code depends on there actually being a certain number of
    threads, you should always call `omp_get_num_threads()` to
    check.

### Environment for performance

- There are some environment variables you should set to maximise
  performance.
  - Don't rely on the defaults for these!
- `OMP_WAIT_POLICY=active` encourages idle threads to spin rather than
  sleep.
- `OMP_DYNAMIC=false` stops runtime delivering fewer threads than you
  asked for.
- `OMP_PROC_BIND=true` prevents threads migrating between cores.

### Debugging tools

- Traditional debuggers such as DDT or Totalview have support for
  OpenMP.
- This is good, but they are not much help for tracking down race
  conditions.
  - Debugger changes the timing of event on different threads.
- Race detection tools work in a different way.
  - Capture all the memory accesses during a run, then analyse this
      data for races which *might have* occured.
  - Intel Inspector XE.

### Timers

- Make sure your timer actually does measure wall clock time!
- Use `omp_get_wtime()`!
- Do not use `clock()` for example.
  - Measures CPU time accumulated across all threads.
  - You would not see any speedup\...
