#include <iostream>
#include <vector>
#include <random>
#include <cmath>
#include <limits>
#include <fstream>

#include "Node.h"
#include "Element.h"
#include "Mesh.h"
#include "MeshMapper.h"

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

    // Save the error values to a CSV file
    std::ofstream outFile("ini_opt_errors.csv");
    outFile << "NodeCount,iniTempError,iniPressError,optTempError,optPressError\n";

    std::mt19937 generator(32);
    std::uniform_real_distribution<double> distCoord(0.0, 1.0); // Coordinates
    std::uniform_real_distribution<double> distPress(20.0, 30.0); // Pressure
    std::uniform_real_distribution<double> distTemp(0.0, 100.0); // Temperature
    std::vector<int> nodeCounts = {2000, 4000, 6000, 8000, 10000};

    for (int numNodes : nodeCounts) {
        // Generate random nodes, temperatures, and pressures for mesh A
        std::vector<Node> nodesA;
        std::vector<double> tempsA, pressuresA;
        for (size_t i = 0; i < numNodes; ++i) {
            nodesA.push_back(Node(distCoord(generator), distCoord(generator), distCoord(generator)));
            tempsA.push_back(distTemp(generator));
            pressuresA.push_back(distPress(generator));
        }
        std::vector<Element> elementsA = createTriangles(nodesA);
        Mesh meshAInitial(nodesA, elementsA, tempsA, pressuresA);
        Mesh meshAOptimised(nodesA, elementsA, tempsA, pressuresA);

        // Assume mesh B is a different mesh with the same number of nodes and elements
        std::vector<Node> nodesB;
        for (size_t i = 0; i < numNodes; ++i) {
            nodesB.push_back(Node(distCoord(generator), distCoord(generator), distCoord(generator)));
        }
        std::vector<Element> elementsB = createTriangles(nodesB); 
        Mesh meshBInitial(nodesB, elementsB, {}, {});
        Mesh meshBOptimised(nodesB, elementsB, {}, {});

        // Map mesh values from mesh A to mesh B, initially and optimised
        MeshMapper::MapMeshValuesInitial(meshAInitial, meshBInitial);
        MeshMapper::MapMeshValuesOptimise(meshAOptimised, meshBOptimised);

        // Reverse map mesh values from mesh B to mesh A, initially and optimised
        Mesh meshAReverseInitial(nodesA, elementsA, {}, {});
        Mesh meshAReverseOptimised(nodesA, elementsA, {}, {});
        MeshMapper::MapMeshValuesInitial(meshBInitial, meshAReverseInitial);
        MeshMapper::MapMeshValuesOptimise(meshBOptimised, meshAReverseOptimised);

        // Calculate errors before optimisation
        double rmseTempInitial = 0.0, rmsePressureInitial = 0.0;
        for (size_t i = 0; i < numNodes; ++i) {
            double errorTempInitial = tempsA[i] - meshAReverseInitial.temperatures[i];
            double errorPressureInitial = pressuresA[i] - meshAReverseInitial.pressures[i];
            rmseTempInitial += errorTempInitial * errorTempInitial;
            rmsePressureInitial += errorPressureInitial * errorPressureInitial;
        }
        rmseTempInitial = std::sqrt(rmseTempInitial / numNodes);
        rmsePressureInitial = std::sqrt(rmsePressureInitial / numNodes);

        // Output errors before optimisation
        std::cout << "RMSE for Temperatures (Initial): " << rmseTempInitial << std::endl;
        std::cout << "RMSE for Pressures (Initial): " << rmsePressureInitial << std::endl;

        // Calculate errors after optimisation
        double rmseTempOptimised = 0.0, rmsePressureOptimised = 0.0;
        for (size_t i = 0; i < numNodes; ++i) {
            double errorTempOptimised = tempsA[i] - meshAReverseOptimised.temperatures[i];
            double errorPressureOptimised = pressuresA[i] - meshAReverseOptimised.pressures[i];
            rmseTempOptimised += errorTempOptimised * errorTempOptimised;
            rmsePressureOptimised += errorPressureOptimised * errorPressureOptimised;
        }
        rmseTempOptimised = std::sqrt(rmseTempOptimised / numNodes);
        rmsePressureOptimised = std::sqrt(rmsePressureOptimised / numNodes);

        // Output errors after optimisation
        std::cout << "RMSE for Temperatures (Optimised): " << rmseTempOptimised << std::endl;
        std::cout << "RMSE for Pressures (Optimised): " << rmsePressureOptimised << std::endl;

        // write errors to file
        outFile << numNodes << "," << rmseTempInitial << "," << rmsePressureInitial << "," << rmseTempOptimised << "," << rmsePressureOptimised << "\n";
    }

    // Close the file
    outFile.close();

    return 0;
}
