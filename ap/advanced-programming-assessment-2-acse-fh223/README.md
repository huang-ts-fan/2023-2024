[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-24ddc0f5d75046c5622901739e7c5dd533143b0c8e959d652212380cedb1ea36.svg)](https://classroom.github.com/a/N6LlQXNE)

### Overview of Implemented Optimisations: 

We implement an **octree** data structure to optimize the search task of finding the nearest node in 3D space. Compared to a brute force search directly in a dynamic array, the octree speeds up the search process by reducing the number of necessary comparisons through spatial partitioning, and the optimized algorithm has a lower time complexity than a direct traversal search. The error calculation is based on **round-trip mapping**. Instead of simply using a one-to-one mapping strategy during mesh mapping, we use a **distance-based weighting** strategy to compute the physical quantity values of the target nodes. This approach better takes into account the geometric relationships in space and can provide more accurate mapping results. 

The folder `MeshingCode` contains the optimized codes.
The file `Report.pdf` contains brief explanations of the architecture and the code.

Since we need to compare the computational efficiency and accuracy of the optimized algorithms separately, we removed the original `main.cpp` and wrote `SearchTime.cpp` and `ErrorTest.cpp` to test the performance of the optimized algorithms separately.

Compile 'SearchTime.cpp' 

```bash
g++ -o SearchTime SearchTime.cpp Mesh.cpp Octree.cpp MeshMapper.cpp -std=c++17
```

Run 'SearchTime.cpp' 

```bash
./SearchTime
```

Run 'SearchTime.cpp' will output a file named 'search_time.csv' which records the search time of the optimized algorithm and the direct traversal search algorithm. We will draw a graph to compare the search time of the two algorithms based on the data in 'search_time.csv'.

Compile 'ErrorTest.cpp' 

```bash
g++ -o ErrorTest ErrorTest.cpp Mesh.cpp Octree.cpp MeshMapper.cpp -std=c++17
```

Run 'ErrorTest.cpp' 

```bash
./ErrorTest
```

Run 'ErrorTest.cpp' will output a file named 'ini_opt_errors.csv' which records the errors of temperature and pressure by using round-trip mapping. We will draw a graph to compare the errors of the optimized algorithm and the direct traversal search algorithm based on the data in 'ini_opt_errors.csv'.

Image is plot by the python file 'PlotImage.py', using 'search_time.csv' and 'ini_opt_errors.csv'.

