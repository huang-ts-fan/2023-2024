# Shared Memory Programming with OpenMP

### Assignment 3: Molecular Dynamics

Your objective is to parallelize the serial C++ code provided.

The code is a molecular dynamics (MD) simulation of argon atoms in a box with
periodic boundary conditions. The atoms are initially arranged as a face-centred
cubic (fcc) lattice and then allowed to melt. The interaction of the particles
is calculated using a Lennard-Jones potential. The main loop of the program is
in the file `main.cpp`.

Once the lattice has been generated and the forces and velocities initialised,
the main loop begins. The following steps are undertaken in each iteration of
this loop:

* The particles are moved based on their velocities, and the velocities are partially updated (call to `domove()`).
* The forces on the particles in their new positions are calculated and the virial and potential energies accumulated (call to `forces()`).
* The forces are scaled, the velocity update is completed and the kinetic energy calculated (call to `mkekin()`).
* The average particle velocity is calculated and the temperature scaled (call to `velavg()`).
* The full potential and virial energies are calculated and printed out (call to `prnout()`).

#### Parallelisation hints

There are several dependencies within the program which will require use of the
critical construct as well as the reduction clause. Rather than trying to create
the perfect parallel version of the code in one go, it is recommended that you
parallelise the code in stages, checking that it is still working correctly, and
then commit the changes to your repository. This will make it easier to make
steady progress.

First, edit the function in `forces.cpp`. Add an `omp parallel` directive to the
outermost loop in this subroutine, identifying any private or reduction
variables (hint... there are two reduction variables). Identify the variable
within the loop which must be protected from possible race conditions and use
the `omp critical` directive to ensure this is the case.

Once this is done the code should be ready to run in parallel. Compare the
output using 2, 3 and 4 threads with the serial output to check that it is
working. Commit your working code, check GitHub actions, and then continue to
improve the parrallel performance.

Try adding the schedule clause with the kind `static,n` to the `for` directive
for different values of `n`. Does this have any effect on performance?

To reduce the overhead of starting and stopping the threads, you can change the
`parallel for` directive to a `for` directive and start the parallel region
outside the program's main loop. In `main.cpp` enclose the main loop in a
parallel region. Except for the forces routine, all the other work in this loop
should be executed by one thread only. Ensure that this is the case using the
`single` or `master` construct. Recall that any reduction variables updated
in a parallel region but outside of the `for` construct should be updated by
one thread only. As before, check your code is still working correctly.

Try using array reductions, or atomic directives, or lock routines (with one
lock variable per particle) instead of critical regions. How did this impact
the parallel performance of the code?

#### Evaluation of the code

* Test your code using a different number of threads.
* In each case:
  * Check that the results are identical in each case.
  * Compare the time taken for the calculations using different numbers of threads.
  * Calculate the speedup and efficiency for each case.