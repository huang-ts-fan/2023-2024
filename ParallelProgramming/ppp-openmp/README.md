# Parallel Programming Patterns
# Part 1: Shared Memory Programming with OpenMP (API version 4.5)

## Course Description

This series of lectures is designed as a hands-on introduction to parallel programming using OpenMP. Students are assumed to have a background in C/C++. Throughout the course, you'll learn how to write and optimize parallel programs effectively.

## Week schedule
- Monday:
  - 09:00-12:00
    - Introduction to Parallel Programming Patterns
    - Lecture 1: Concepts
    - Lecture 2: OpenMP Fundamentals
  - 14:00-17:00
    - Workshop: Introduction to HPC at Imperial College London
- Tuesday:
  - 09:00-12:00
    - Lecture 3: Parallel Regions
    - Lecture 4: Work sharing directives
  - 14:00-17:00:
    - Introduction to weeks assessment
    - Coursework
- Wednesday:
  - 09:00-12:00:
    - Lecture 5: Synchronization
    - Lecture 6: Further Topics
  - 14:00-17:00:
    - Coursework
- Thursday:
  - 09:00-12:00:
    - Lecture 7: OpenMP Tips, tricks, and gotchas
    - Lecture 8: Performance
  - 14:00-17:00:
    - Coursework
- Friday:
  - 09:00-12:00: Coursework
  - 16:00: Assessment deadline

## Development Environment Setup

### General Requirements

- IDE: Visual Studio Code (VSCode).
- Knowledge of basic terminal operations.
- [Visual Studio Code (VSCode)](https://code.visualstudio.com/):
  - Install the C/C++ extension from the VSCode marketplace.
    - C/C++ extension.
    - [Mermaid](https://marketplace.visualstudio.com/items?itemName=vstirbu.vscode-mermaid-preview) (Optional).
  - Configure `tasks.json` to use `gcc-13` for the `compilerPath`.

#### Mac Users (M1 Chip)

- Compiler Installation:
  - Open Terminal.
  - Install [Homebrew](https://brew.sh/) if not already installed.
  - Install GCC-13: `brew install gcc@13`
  - Install Mermaid: (optional)
    - `brew install node`
    - `npm install -g @mermaid-js/mermaid-cli`
    - `brew install mermaid-cli`
  - Verify installation: `gcc-13 --version`

- Configuring [Visual Studio Code (VSCode)](https://code.visualstudio.com/):
  - Install the C/C++ extension from the VSCode marketplace.
    - C/C++ extension
    - [Mermaid](https://marketplace.visualstudio.com/items?itemName=vstirbu.vscode-mermaid-preview) (Optional)
  - Configure `tasks.json` to use `gcc-13` for the `compilerPath`.

```
WARNING: On macOS, the default `gcc` command is typically aliased to Clang, Apple's default C/C++ compiler. Unlike GCC, Clang does not support OpenMP out of the box. This can lead to confusion if you try to compile OpenMP programs without the proper setup, as the compiler will not recognize OpenMP pragmas and directives, resulting in errors or ignored directives.

To ensure proper OpenMP support, please follow the instructions provided in this README to install and configure `gcc-13` via Homebrew, which provides genuine GCC with OpenMP support.
```

#### Windows Users
- Compiler Installation:
  - Download and install the [Intel Compiler Suite](https://software.intel.com/content/www/us/en/develop/tools/oneapi.html).

- Configuring VSCode:
  - Install the C/C++ extension from the VSCode marketplace.
  - Adjust `c_cpp_properties.json` to set the `compilerPath` to where the Intel compiler is installed.

#### Using Imperial College London [Research Computing Service (RCS)](https://www.imperial.ac.uk/admin-services/ict/self-service/research-support/rcs/)
- Remote Development:
  - Set up an SSH connection to `login.cx3.hpc.ic.ac.uk`.
  - Use [VSCode’s Remote - SSH extension](https://code.visualstudio.com/docs/remote/ssh) to connect and code directly on the cluster.
  - Load the necessary modules on the cluster for OpenMP compilation.

## Resources
- [OpenMP 4.5](https://www.openmp.org/updates/openmp-4-5-specs-released/) \[[PDF](https://www.openmp.org/wp-content/uploads/openmp-4.5.pdf)\]
- [Code Visual Studio](https://code.visualstudio.com/docs)
- [Imperial College London's RCS User Guide](https://icl-rcs-user-guide.readthedocs.io/en/latest/)
- [Introduction to HPC at Imperial](https://www.imperial.ac.uk/students/academic-support/graduate-school/professional-development/doctoral-students/research-computing-data-science/courses/introduction-to-hpc/)
