# Shared Memory Programming with OpenMP

## Assignment 1: Hello World

Add an OpenMP parallel section around the `std::cout` statement in
`HelloWorld.cpp`. Do not change the `std::cout` statement itself.

Add additional `OpenMP` directives to the code to make the output from
`std::cout` appear in ascending order of thread number.

Compile the code, making sure you use the appropriate flag to
enable OpenMP. Test your code locally by setting the environment variable `OMP_NUM_THREADS` to different numbers of threads and running the code.
For example,

```
OMP_NUM_THREADS=4 ./HelloWorld
```

Once you are satisfied with your code, submit it to your assessment repository.
Check the result of GitHub Actions to see if your code passes the tests.