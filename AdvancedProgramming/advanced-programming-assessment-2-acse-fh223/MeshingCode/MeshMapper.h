#ifndef MESHMAPPER_H
#define MESHMAPPER_H

#include <iostream>
#include <unordered_map>
#include <vector>
#include <cassert>

#include "Node.h"
#include "Element.h"
#include "Mesh.h"

// Class representing a mesh mapper
class MeshMapper {
public:
    // Barycentric interpolation within a triangle
    static void BarycentricInterpolation(
        const Node& p, const Node& p0, const Node& p1, const Node& p2,
        double& w0, double& w1, double& w2);

    // Map values from one mesh to another using isogeometric linear triangles this is the initial implementation
    static void MapMeshValuesInitial(const Mesh& sourceMesh, Mesh& targetMesh);
    // Based on the initial implementation, optimise the mapping
    static void MapMeshValuesOptimise(const Mesh& sourceMesh, Mesh& targetMesh);
};

#endif