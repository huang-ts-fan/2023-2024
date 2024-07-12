// Octree.cpp
#include "Octree.h"
#include <iostream>
#include <limits>
#include <cmath>

// Calculate the distance between two nodes
double calculateDistance1(const Node& a, const Node& b) {
    return std::sqrt(std::pow(a.x - b.x, 2) + std::pow(a.y - b.y, 2) + std::pow(a.z - b.z, 2));
}

// Constructor
OctreeNode::OctreeNode() : hasPoint(false), children(8) {}

// Insert a node into the octree
void OctreeNode::insert(const Node& node, const Node& min, const Node& max) {
    if (!hasPoint) {
        point = node;
        hasPoint = true;
        return;
    }

    int index = 0;
    if (node.x > (min.x + max.x) / 2) index |= 4;
    if (node.y > (min.y + max.y) / 2) index |= 2;
    if (node.z > (min.z + max.z) / 2) index |= 1;

    // Create a new octree node for the child if it doesn't exist
    Node newMin = min, newMax = max;
    if (index & 4) newMin.x = (min.x + max.x) / 2; else newMax.x = (min.x + max.x) / 2;
    if (index & 2) newMin.y = (min.y + max.y) / 2; else newMax.y = (min.y + max.y) / 2;
    if (index & 1) newMin.z = (min.z + max.z) / 2; else newMax.z = (min.z + max.z) / 2;

    if (!children[index]) children[index] = std::make_unique<OctreeNode>();
    children[index]->insert(node, newMin, newMax);
}

// Find the nearest node to a target node
Node OctreeNode::findNearest(const Node& target, const Node& min, const Node& max, double& bestDist) const {
    if (!hasPoint) return Node(); // Return an invalid node

    // Check if the current node is closer than the best node
    Node bestPoint = point;
    double dist = calculateDistance1(target, point);
    if (dist < bestDist) {
        bestDist = dist;
        bestPoint = point;
    }

    int index = 0;
    if (target.x > (min.x + max.x) / 2) index |= 4;
    if (target.y > (min.y + max.y) / 2) index |= 2;
    if (target.z > (min.z + max.z) / 2) index |= 1;

    Node newMin = min, newMax = max;
    // Adjust the bounds for searching the children

    if (children[index]) {
        Node childBest = children[index]->findNearest(target, newMin, newMax, bestDist);
        double childDist = calculateDistance1(target, childBest);
        if (childDist < bestDist) {
            bestDist = childDist;
            bestPoint = childBest;
        }
    }

    return bestPoint;
}

Octree::Octree(const Node& min, const Node& max) : min(min), max(max) {
    root = std::make_unique<OctreeNode>();
}

void Octree::insert(const Node& node) {
    root->insert(node, min, max);
}

Node Octree::findNearest(const Node& target) const {
    double bestDist = std::numeric_limits<double>::max();
    return root->findNearest(target, min, max, bestDist);
}
