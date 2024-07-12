# Shared Memory Programming with OpenMP

## Lecture 05: Synchronisation

### Learning Objectives

By the end of this lecture, you should be able to:

- **Understand the Necessity of Synchronization in Parallel Programming**: Recognize why synchronization is crucial for managing shared resources and ensuring the correct ordering of operations in concurrent environments.
- **Effectively Use the `barrier` Directive**: Apply the `barrier` directive to synchronize threads at specific points in a program, ensuring that all threads reach the same execution point before proceeding.
- **Implement Critical Sections with `critical` and `atomic` Directives**: Differentiate between the `critical` and `atomic` directives for protecting updates to shared variables and understand when to use each directive for optimal performance.
- **Utilize Locks for Advanced Synchronization**: Demonstrate the ability to use OpenMP lock routines to handle complex synchronization scenarios where more control over thread interaction is required.
- **Choose Appropriate Synchronization Mechanisms**: Select the most suitable synchronization mechanism based on the specific needs of the program, balancing overhead, complexity, and scalability.

### Why is synchronization required?

- Need to synchronise actions on shared variables.
- Need to ensure correct ordering of reads and writes.
- Need to protect updates to shared variables (not atomic by default)

### `barrier` directive

- No thread can proceed past a barrier until all the other threads
    have arrived.
- Note that there is an implicit barrier at the end of `for`,
    `sections` and `single` directives.
- Syntax:

``` c++
#pragma omp barrier
```

- Either all threads or none must encounter the barrier: otherwise
    DEADLOCK!!

**Example:**

``` c++
#pragma omp parallel private(myid,neighb) shared(a,b,c)
{
  myid = omp_get_thread_num();
  neighb = myid – 1;

  if (myid.eq.0)
    neighb = omp_get_num_threads()-1;
  // ...
  
  a[myid] *= 3.5; 

  // Barrier required to force synchronisation on a[].
#pragma omp barrier
    
  b[myid] = a[neighb] + c;

  // ...
}
```

### Critical sections

- A critical section is a block of code which can be executed by only
  one thread at a time.
- Can be used to protect updates to shared variables.
- Syntax:

``` c++
#pragma omp critical
{
  // structured block
}
```

### Critical sections example: appending to a shared list

``` c++
#pragma omp parallel for shared(list, N) private(newitem_p)
for (int i=0; i<N; i++) {
  newitem_p = createitem(i); 

#pragma omp critical
  {
    append(&list, p_newitem);
  }

}
```

### CRITICAL directive example: pushing and popping a task stack

``` c++
#pragma omp parallel shared(stack) private(p_next,p_new,done)
{
  while (!done) {
#pragma omp critical
    {
      p_next = pop(&stack);
    }

    p_new = process(p_next);
#pragma omp critical
    {
      if (p_new != NULL)
        push(p_new, &stack);

      done = isempty(&stack);
    }
  }
}
```

### `atomic` directive

- Used to protect a single update to a shared scalar variable of basic
  type.
- Applies only to a single statement.
- Syntax:

``` c++
#pragma omp atomic
statement
```

- where *statement* must have one of the forms: `x binop=expr`, `x++`,
    `++x`, `x--` or `--x`

- and `binop` is one of `+`, `*`, `-`, `/`, `&`, `^`, `<<`, `>>`.

- Note that the evaluation of `expr` is not atomic.

- May be more efficient than using `critical` directives, e.g. if
  different array elements can be protected separately.

- No interaction with `critical` directives.

### `atomic` directive example - compute degree of each vertex in a graph

``` c++
#pragma omp parallel for
for (int j=0; j<nedges; j++){
#pragma omp atomic
  degree[edge[j].vertex1]++;
    
#pragma omp atomic
  degree[edge[j].vertex2]++;
}
```

### Lock routines

- Occasionally we may require more flexibility than is provided by
    `critical` directive.
- A lock is a special variable that may be *set* by a thread. No other
  thread may *set* the lock until the thread which set the lock has
  *unset* it.
- Setting a lock can either be blocking or non-blocking.\
- A lock must be initialised before it is used, and may be destroyed
  when it is not longer required.
- Lock variables should not be used for any other purpose.

### Lock routines - syntax

``` c++
#include <omp.h>

void omp_init_lock(omp_lock_t *lock);
void omp_set_lock(omp_lock_t *lock);
int omp_test_lock(omp_lock_t *lock);
void omp_unset_lock(omp_lock_t *lock);
void omp_destroy_lock(omp_lock_t *lock);
```

### Lock example - compute degree of each vertex in a graph

``` c++
omp_lock_t lockvar[nvertices]; 

for (int i=0; i<nvertexes; i++){
  omp_init_lock(&lockvar[i]);
}

#pragma omp parallel for
for (int j=0; j<nedges; j++){
  omp_set_lock(&lockvar[edge[j].vertex1]);
  degree[edge[j].vertex1]++;

  omp_unset_lock(&lockvar[edge[j].vertex1]);
  omp_set_lock(&lockvar[edge[j].vertex2]);
  degree[edge[j].vertex2]++;  

  omp_unset_lock(&lockvar[edge[j].vertex2]);
}
```

### Summary

- **Necessity of Synchronization**: We discussed the critical role synchronization plays in parallel programming, especially in managing shared variables. Ensuring the correct ordering of reads and writes prevents data races and ensures that program outputs are predictable and correct.

- **Barrier Directive**: The use of the `barrier` directive was explored in detail. This directive ensures that no thread can proceed past a certain point in the program until all participating threads have reached this barrier. This is crucial in scenarios where subsequent operations depend on the results of earlier operations handled by multiple threads.

- **Critical Sections**: We covered how to define critical sections within a parallel region to ensure that only one thread at a time executes a particular block of code. This is essential when performing operations that modify shared data, which could lead to inconsistencies if accessed concurrently.

- **Atomic Directive**: The `atomic` directive provides a more granular level of synchronization by ensuring that specific operations on shared variables are completed atomically. This directive is particularly useful for simple operations on basic data types, offering a performance advantage over broader critical sections.

- **Lock Routines**: Advanced synchronization techniques involving lock routines were introduced. These allow for more flexible and sophisticated control over thread interactions compared to `critical` directives, especially useful in complex synchronization scenarios where multiple resources are involved.

- **Practical Examples and Application**: Throughout the lecture, practical examples demonstrated how to apply these synchronization techniques in real-world scenarios. For instance, ensuring the atomicity of operations when updating shared structures like graphs or linked lists, and using locks to manage access to shared resources effectively.
