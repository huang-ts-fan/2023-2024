# Shared Memory Programming with OpenMP

## Course assignments

It is **important** that you read all the following instructions carefully.

* **Submission deadline: 16:00 3rd May.**

This folder contains the assignments for the course:
* `assignment-1/`
* `assignment-2/`
* `assignment-3/`

Each assignment is a self-contained folder with a `README.md` file that
describes the assignment.

For portability, a `CMakelists.txt` file is provided which you should use to
compile all the assignments using `cmake`. To compile your code from the
command-line, `cd` to this folder and execute the following steps:

```bash
mkdir build
cd build
cmake ..
make
```

You can then run the compiled code from the `build` folder. It is best
practice to compile your code in a separate folder, as shown above.
This is called `out of source builds` and is a good habit to get into.

Your IDE should be able to compile the code without you needing to use the
command-line (you may need to explicitly tell it to use `CMakeLists.txt`).
However, you are strongly encouraged to learn how to compile code from the
command-line.


The grading is semi-automated using [GitHub
Actions](https://docs.github.com/en/actions). You can use this feature to
get instant feedback on their assessments by pushing your changes to the
assessment repository and clicking on the "Actions" tab of your repository on GitHub. You are free to push to the repository as
many times as you want, but only the last commit before the deadline will be considered for grading.

**Updates to GitHub actions may be during the course of the assignment so you should check the Teams channel for any updates.**

Changing the names of any files or functions may break testing. Similarly, adding new dependencies (i.e. additional header files or libraries) may break testing carried out by GitHub actions. It is the student's responsibility to check the results of the tests in GitHub Actions.

While you may decide to modify the contents of `.github/workflows/`, please be aware that all these changes will be overwritten when grading is performed.

The grading of this assignment will be based on the following criteria:
* All changes to the code should be clearly commented.
* You should regularly commit your code to the repository so that the history of your work is available. Make your commit messages clear and informative.
* The code should be well-structured and easy to read.
* The code should compile without warnings and errors.
* The code should give the expected result for different numbers of OpenMP threads.
* Single thread performance: The performance of the code when using a single OpenMP thread will be compared to the performance of the unmodified sequential code. The performance of the code should be at least 90% of the performance of the sequential code.
* Parallel efficiency: The performance of the code when using multiple OpenMP threads will be compared to the performance of the unmodified sequential code by calculating the parallel efficiency.