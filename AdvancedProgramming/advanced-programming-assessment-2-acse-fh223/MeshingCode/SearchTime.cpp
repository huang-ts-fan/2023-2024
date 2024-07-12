#include <iostream>
#include <vector>
#include <random>
#include <cmath>
#include <limits>
#include <chrono>
#include <fstream>

#include "Node.h"
#include "Element.h"
#include "Mesh.h"
#include "MeshMapper.h"
#include "Octree.h"

// Calculate the distance between two nodes
double calculateDistance(const Node& a, const Node& b) {
    return std::sqrt(std::pow(a.x - b.x, 2) + std::pow(a.y - b.y, 2) + std::pow(a.z - b.z, 2));
}

// Find the two nearest nodes to a given node
std::pair<int, int> findTwoNearestNodes(const std::vector<Node>& nodes, int index) {
    int nearest1 = -1, nearest2 = -1;
    double dist1 = std::numeric_limits<double>::max(), dist2 = dist1;

    for (int i = 0; i < nodes.size(); ++i) {
        if (i == index) continue; // Skip the node itself

        double dist = calculateDistance(nodes[index], nodes[i]);
        if (dist < dist1) {
            dist2 = dist1;
            nearest2 = nearest1;
            dist1 = dist;
            nearest1 = i;
        } else if (dist < dist2) {
            dist2 = dist;
            nearest2 = i;
        }
    }
    return {nearest1, nearest2};
}

// Create a mesh of triangles from a set of nodes
std::vector<Element> createTriangles(const std::vector<Node>& nodes) {
    std::vector<Element> elements;
    for (int i = 0; i < nodes.size(); ++i) {
        std::pair<int, int> nearest = findTwoNearestNodes(nodes, i);
        int nearest1 = nearest.first;
        int nearest2 = nearest.second;
        elements.emplace_back(Element({i, nearest1, nearest2}));
    }
    return elements;
}

int main() {

    // Save the search times to a CSV file
    std::ofstream outFile("search_times.csv");
    outFile << "NodeCount,DirectSearchTime,OctreeSearchTime\n";

    std::mt19937 generator(32); // Set seed for random number generator
    // Set the range for the random node coordinates
    std::uniform_real_distribution<double> distCoord(0.0, 1.0);
    // Set the number of nodes to test
    std::vector<int> nodeCounts = {2000, 4000, 6000, 8000, 10000};

    // Test the performance of the octree and direct search(vector) for different numbers of nodes
    for (int numNodes : nodeCounts) {

        // Vector to store the nodes
        std::vector<Node> nodes;
        for (size_t i = 0; i < numNodes; ++i) {
            nodes.push_back(Node(distCoord(generator), distCoord(generator), distCoord(generator)));
        }

        // Define the boundaries of the octree
        Node min(0.0, 0.0, 0.0), max(1.0, 1.0, 1.0);
        Octree tree(min, max);

        // Insert nodes into the octree
        auto startInsert = std::chrono::high_resolution_clock::now();
        for (const auto& node : nodes) {
            tree.insert(node);
        }
        auto endInsert = std::chrono::high_resolution_clock::now();
        auto insertDuration = std::chrono::duration_cast<std::chrono::milliseconds>(endInsert - startInsert).count();
        // std::cout << "Insertion into Octree took: " << insertDuration << " ms\n";

        // Use the octree to find the nearest node to each node
        auto startSearch = std::chrono::high_resolution_clock::now();
        for (const auto& node : nodes) {
            tree.findNearest(node);
        }
        auto endSearch = std::chrono::high_resolution_clock::now();
        auto searchDuration = std::chrono::duration_cast<std::chrono::milliseconds>(endSearch - startSearch).count();
        // std::cout << "Searching in Octree took: " << searchDuration << " ms\n";
        long long octreeSearchDuration = insertDuration + searchDuration;
        std::cout << "Octree searching took: " << octreeSearchDuration << " ms\n";

        // Use direct search to find the nearest node to each node
        auto startDirectSearch = std::chrono::high_resolution_clock::now();
        for (size_t i = 0; i < nodes.size(); ++i) {
            findTwoNearestNodes(nodes, i);
        }
        auto endDirectSearch = std::chrono::high_resolution_clock::now();
        auto directSearchDuration = std::chrono::duration_cast<std::chrono::milliseconds>(endDirectSearch - startDirectSearch).count();
        std::cout << "Direct searching took: " << directSearchDuration << " ms\n";

        // Write the search times to a CSV file
        outFile << numNodes << "," << directSearchDuration << "," << octreeSearchDuration << "\n";

    }
    
    // Close the file
    outFile.close();

    return 0;
}