// Octree.h
#ifndef OCTREE_H
#define OCTREE_H

#include <vector>
#include <memory>
#include "Node.h" 

class OctreeNode {
public:
    Node point;
    // Check if the node has a point
    bool hasPoint;
    std::vector<std::unique_ptr<OctreeNode>> children;

    OctreeNode();
    void insert(const Node& node, const Node& min, const Node& max);
    // Find the nearest node to a target node
    Node findNearest(const Node& target, const Node& min, const Node& max, double& bestDist) const;
};

class Octree {
public:
    std::unique_ptr<OctreeNode> root;
    Node min, max; // Bounds of the octree

    Octree(const Node& min, const Node& max);
    void insert(const Node& node);
    Node findNearest(const Node& target) const;
};

#endif // OCTREE_H
