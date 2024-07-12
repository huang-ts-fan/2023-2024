#ifndef NODE_H
#define NODE_H

#include <vector>

// Class representing a node in the mesh
// Contains the x, y, and z coordinates of the node
class Node {
public:
    double x, y, z;
    Node(double _x, double _y, double _z) : x(_x), y(_y), z(_z) {}
    Node() : x(0), y(0), z(0) {}
};

#endif