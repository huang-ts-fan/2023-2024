#ifndef MESH_H
#define MESH_H

#include <iostream>
#include <unordered_map>
#include <vector>
#include <cassert>

#include "Node.h"
#include "Element.h"

// Class representing a mesh
// Contains the nodes, elements, temperatures, and pressures of the mesh
class Mesh 
{
public:
    std::vector<Node> nodes;
    std::vector<Element> elements;
    std::vector<double> temperatures;
    std::vector<double> pressures;

    // Constructor
    Mesh(const std::vector<Node>& _nodes, const std::vector<Element>& _elements,
        const std::vector<double>& _temperatures, const std::vector<double>& _pressures);
    // Display mesh information
    void displayInfo() const;
    // Set the temperatures of the nodes
    void setTemperatures(const std::vector<double>& _temperatures);
    // Set the pressures of the nodes
    void setPressures(const std::vector<double>& _pressures);
    // Get the temperatures of the nodes
    std::vector<double> getTemperatures() const;
    // Get the pressures of the nodes
    std::vector<double> getPressures() const;
};

#endif