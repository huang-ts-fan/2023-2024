#ifndef ELEMENT_H
#define ELEMENT_H

#include <vector>

// Class representing an element in the mesh
// Contains the indices of the nodes that make up the element
class Element {
public:
    std::vector<int> nodeIndices;
    Element(const std::vector<int>& indices) : nodeIndices(indices) {}
};

#endif