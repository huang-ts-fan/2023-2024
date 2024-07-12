# Shared Memory Programming with OpenMP

## Lecture 03: Parallel Regions

### Learning Objectives

By the end of this lecture, you should be able to:

- **Understand the Execution of Code within Parallel Regions**: Recognize how code inside a `#pragma omp parallel` block is executed concurrently by all threads, and how code outside is executed sequentially by the master thread.
- **Grasp OpenMP API Functions**: Explain the purpose and use of OpenMP runtime library functions such as `omp_get_num_threads` and `omp_get_thread_num`, which help in identifying the number of threads and the specific thread running the code.
- **Apply Clauses to Control Data Environment**: Implement `shared`, `private`, and `default` clauses to manage variable accessibility and behavior within parallel regions, and understand the implications of each choice on parallel execution.
- **Initiate Private Variables Correctly**: Understand the importance of correctly initializing private variables using the `firstprivate` clause to ensure that each thread starts with a predefined value from the master thread, avoiding uninitialized data issues.
- **Utilize the `reduction` Clause for Accumulative Operations**: Learn to use the `reduction` clause to perform safe and efficient reduction operations like summing across threads without data race issues.

### Parallel region directive

- Code within a parallel region is executed by all threads.

  ``` c++
  // Sequential code: only run by main thread.
  foo(); 

  #pragma omp parallel
  {   
    // Code in this section is executed by all threads.
    bar();
  }

  // Sequential code: only run by main thread.
  foobar();
  ```

### Introduction to the OpenMP API

To use OpenMP *functions* you must include the header `omp.h`.

#### `omp_get_num_threads`

  ``` c++
  int omp_get_num_threads(void);
  ```

The `omp_get_num_threads` routine returns the number of threads in the current team/region. The binding region for an `omp_get_num_threads` region is the innermost enclosing parallel region.

- Returns `1` if `omp_get_num_threads` is called from the sequential part of a program.
- Otherwise, `omp_get_num_threads` called from a parallel region returns the number of threads executing the parallel region. This will be the same value as the environment variable `OMP_NUM_THREADS` if it is set.

#### `omp_get_thread_num`

  ``` c++
  int omp_get_thread_num(void);
  ```

The `omp_get_thread_num` routine returns the thread number, within the current team, of the calling thread. The thread number is an integer between 0 and one less than the value returned by `omp_get_num_threads`, inclusive. The thread number of the master thread of the team is 0. The routine returns 0 if it is called from the sequential part of a program.

### Clauses

Additional information can be passed to the parallel region directive through the use of clauses. Clauses are comma or space separated.

  ``` c++
  #pragma omp parallel [clauses]
  ```

#### Shared and private variable clauses

- Inside a parallel region, variables can be defined as,
  - `shared(list)`: All threads in the list share the same copy,
  - `private(list)`: All threads have their own copy.
  - `default(private|shared|none)`: Sets the default policy.
- Not specifying a `default` clause is the same as specifying
    `default(shared)`.
  - **Not specifying a default clause is considered bad practice!**
  - As a rule-of-thumb, always use `default(none)`.

**Example: Each thread initializes its own part of a shared array.**

``` c++
#include <omp.h>

// ...

int n=1000;
float a[4][1000]; 

#pragma omp parallel default(none) shared(a,n)
{
  // Note that myid and i are private as they
  // are defined within the parallel region.
  int myid = omp_get_thread_num();
  for (int i=0; i<n; i++){ 
    a[myid][i] = 1.0;
  }
}
```

**Example: Multi-line directives.**

``` c++
#pragma omp parallel default(none) \
        private(i,myid) shared(a,n)
```

#### Initialization of private variables

**Never rely on the compiler to initialize variables for you.** This is a common source of bugs because different compiler and compiler options will have different behavior. **Always initialize them yourself.** This also applies to private variables in a parallel region.

- On entry to a parallel region variables listed as being private are uninitialized within the parallel regions. This is true even if you initialized the variable outside the parallel region.
- After the parallel region ends the original variable is unaffected by any changes to private copies.
- Variables declared inside the scope of the parallel region are automatically private.
- C++ class objects are created using the default constructor (ie this is where it gets initialized).

#### Initializing private variables using the `firstprivate(list)` clause

In OpenMP, the `firstprivate(list)` clause is used to initialize private variables at the start of a parallel region, ensuring each thread gets its own copy with the initial value as it was before entering the parallel region. This is particularly useful in scenarios where the private variables need to start with a specific value that exists prior to the parallel execution.

- **Initialization of Private Variables**: Unlike the `private(list)` clause, which creates a new instance of the variable for each thread without initializing it, `firstprivate(list)` ensures that each thread's private copy of the variable is automatically initialized with the value that the variable had in the master thread at the time the parallel region was encountered.
  
- **Efficiency in Code**: Using `firstprivate(list)` can lead to more readable and efficient code by eliminating the need for manual initialization of private variables within the parallel region, thus reducing redundancy and potential for errors.

**Example:** In this example, `firstprivate(index)` ensures that each thread begins with `index` initialized to 10, thereby providing a consistent and predictable starting state for the operation within the loop.

```cpp
int index = 10;  // Initial index value
#pragma omp parallel for firstprivate(index)
for(int i = 0; i < n; ++i) {
    // Each thread starts with index = 10
    // Perform operations using index
}
```

#### Examples: Initializing private variables

``` c++
int n=1000;
float c[4][1000];
float b = 23.0;

#pragma omp parallel firstprivate(b) shared(c, n)
{
  int myid = omp_get_thread_num();
  
  for (int i=0; i<n; i++){
    b += c[myid][i];
  }
  c[myid][n] = b; 

}
```

### Understanding the `reduction` Clause in OpenMP

In OpenMP, the `reduction` clause is a powerful tool designed to perform a specific type of operation across all threads and combine the results into a single output variable. This clause simplifies the implementation of common patterns in parallel processing, such as summing values or finding a minimum or maximum.

#### Purpose of the `reduction` Clause

- **Associative Operations**: The `reduction` clause supports associative operations like addition, multiplication, and logical operations (AND, OR). It ensures that despite the parallel execution, the final result is the same as if the operations were performed in a serial manner.
- **Syntax**: The syntax of the `reduction` clause is `reduction(op:list)`, where `op` is the operator and `list` is the list of variables to be reduced.
  
```c++
reduction(op:list)
```

#### How it Works

- **Private Copies**: Initially, each thread creates a private copy of the variables listed in the `reduction` clause. This prevents race conditions and ensures that threads do not interfere with each other's calculations.
- **Thread-level Reduction**: Each thread performs the specified operation on its private copy as it processes its segment of the task.
- **Combining Results**: After all threads complete their computations, the results of these private copies are combined using the same operation specified in the `reduction` clause.

#### Example Usage

Consider a scenario where you need to sum the elements of an array distributed across different threads:

```c++
int sum = 0;
int data[N];  // Assume data is already populated

#pragma omp parallel for reduction(+:sum)
for (int i = 0; i < N; i++) {
    sum += data[i];
}

// 'sum' now contains the total sum of all elements in 'data'
```

In this example, the `reduction(+:sum)` clause tells OpenMP to perform a reduction on the `sum` variable using the addition operator. Each thread computes a partial sum of the array elements it processes. Finally, all partial sums are added together to achieve the total sum, which is stored in `sum`.

- **Efficiency**: The reduction mechanism is efficient because it allows concurrent computations without the need for explicit synchronization mechanisms, such as mutexes, which can degrade performance.
- **Correctness**: It ensures that the parallel computation yields the same result as a sequential computation, which is critical for the correctness of many algorithms.

The `reduction` clause in OpenMP simplifies the parallelization of code where a single result must be computed from multiple operations. By understanding and utilizing this clause effectively, developers can significantly enhance the performance and scalability of their applications.

### Summary

- **Parallel Region Execution**: We explored how code within `#pragma omp parallel` blocks is executed by all threads simultaneously, distinguishing between parallel and sequential execution. This fundamental structure underpins all parallel processing in OpenMP, ensuring that tasks within the parallel region are distributed across multiple threads.

- **OpenMP API Functions**: We delved into specific OpenMP API functions such as `omp_get_num_threads` and `omp_get_thread_num`. These functions are crucial for obtaining runtime information about the number of threads in a parallel region and identifying specific threads, respectively. Understanding these functions allows programmers to control and optimize parallel execution dynamics.

- **Data Sharing Attributes**: The lecture covered how to control data sharing within parallel regions using clauses like `shared`, `private`, and `default`. These clauses define how variables are accessed by threads, impacting thread safety and the correctness of the parallel program. The `default(none)` clause was particularly emphasized as a best practice for making variable sharing explicit, thus reducing programming errors.

- **Initialization of Private Variables**: The correct initialization of private variables using the `firstprivate` clause was discussed. This clause is essential for ensuring that each thread starts with a specific initial value for its private variables, enhancing reliability and predictability in parallel computations.

- **Reduction Operations**: We also covered the `reduction` clause, which is used to perform operations like addition or multiplication across all threads and combine their results safely without data races. This clause simplifies the implementation of cumulative operations across parallel regions.
