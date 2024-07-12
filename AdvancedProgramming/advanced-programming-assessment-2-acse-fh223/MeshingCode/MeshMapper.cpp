#include "MeshMapper.h"
#include <cmath> 

// Barycentric interpolation within a triangle
void MeshMapper::BarycentricInterpolation(
	const Node& p, const Node& p0, const Node& p1, const Node& p2,
	double& w0, double& w1, double& w2)
{
	double detT = (p1.y - p2.y) * (p0.x - p2.x) + (p2.x - p1.x) * (p0.y - p2.y);
	w0 = ((p1.y - p2.y) * (p.x - p2.x) + (p2.x - p1.x) * (p.y - p2.y)) / detT;
	w1 = ((p2.y - p0.y) * (p.x - p2.x) + (p0.x - p2.x) * (p.y - p2.y)) / detT;
	w2 = 1.0 - w0 - w1;
}

// Map values from one mesh to another using isogeometric linear triangles this is the initial implementation
void MeshMapper::MapMeshValuesInitial(const Mesh& sourceMesh, Mesh& targetMesh)
{
    // Map nodes and elements
    std::unordered_map<int, int> nodeMapping; 
    std::unordered_map<int, int> elementMapping; 

    // Here, we assume a simple one-to-one mapping based on the order of nodes and elements
    for (int i = 0; i < sourceMesh.nodes.size(); ++i) {
    nodeMapping[i] = i < targetMesh.nodes.size() ? i : -1;
    }

    for (int i = 0; i < sourceMesh.elements.size(); ++i) {
    elementMapping[i] = i < targetMesh.elements.size() ? i : -1;
    }

    // Map temperatures and pressures
    targetMesh.temperatures.assign(targetMesh.nodes.size(), 0.0);
    targetMesh.pressures.assign(targetMesh.nodes.size(), 0.0);


    // Iterate over the target mesh nodes and interpolate the temperatures and pressures
    for (int i = 0; i < targetMesh.nodes.size(); ++i) {
        const auto& targetNode = targetMesh.nodes[i];
        double totalWeight = 0.0;
        double interpolatedTemperature = 0.0;
        double interpolatedPressure = 0.0;

        for (const auto& sourceElement : sourceMesh.elements) {
            const Node& p0 = sourceMesh.nodes[sourceElement.nodeIndices[0]];
            const Node& p1 = sourceMesh.nodes[sourceElement.nodeIndices[1]];
            const Node& p2 = sourceMesh.nodes[sourceElement.nodeIndices[2]];

            double w0, w1, w2;
            BarycentricInterpolation(targetNode, p0, p1, p2, w0, w1, w2);

            int sourceIndex0 = sourceElement.nodeIndices[0];
            int sourceIndex1 = sourceElement.nodeIndices[1];
            int sourceIndex2 = sourceElement.nodeIndices[2];

            // Check if the source indices are valid
            if (nodeMapping.count(sourceIndex0) && nodeMapping.count(sourceIndex1) &&
                nodeMapping.count(sourceIndex2)) {
                int targetIndex0 = nodeMapping[sourceIndex0];
                int targetIndex1 = nodeMapping[sourceIndex1];
                int targetIndex2 = nodeMapping[sourceIndex2];

                assert(targetIndex0 != -1 && targetIndex1 != -1 && targetIndex2 != -1);

                // Perform barycentric interpolation for temperatures and pressures
                interpolatedTemperature += w0 * sourceMesh.temperatures[sourceIndex0] +
                w1 * sourceMesh.temperatures[sourceIndex1] +
                w2 * sourceMesh.temperatures[sourceIndex2];

                interpolatedPressure += w0 * sourceMesh.pressures[sourceIndex0] +
                w1 * sourceMesh.pressures[sourceIndex1] +
                w2 * sourceMesh.pressures[sourceIndex2];

                totalWeight += 1.0;
            }
        }

        // Normalize the interpolated values
        if (totalWeight > 0.0) {
                    targetMesh.temperatures[i] = interpolatedTemperature / totalWeight;
                    targetMesh.pressures[i] = interpolatedPressure / totalWeight;
        }
    }
}


void MeshMapper::MapMeshValuesOptimise(const Mesh& sourceMesh, Mesh& targetMesh) {
    // Clear the target mesh temperatures and pressures
    targetMesh.temperatures.clear();
    targetMesh.temperatures.resize(targetMesh.nodes.size(), 0.0);
    targetMesh.pressures.clear();
    targetMesh.pressures.resize(targetMesh.nodes.size(), 0.0);

    std::vector<double> weights(targetMesh.nodes.size(), 0.0); // Store the weights for normalization

    for (size_t i = 0; i < targetMesh.nodes.size(); ++i) {
        const Node& targetNode = targetMesh.nodes[i];

        // Calculate the distance-weighted average of the source mesh temperatures and pressures
        for (size_t j = 0; j < sourceMesh.nodes.size(); ++j) {
            const Node& sourceNode = sourceMesh.nodes[j];

            // Calculate the distance between the source and target nodes
            double distance = sqrt(pow(sourceNode.x - targetNode.x, 2) +
                                   pow(sourceNode.y - targetNode.y, 2) +
                                   pow(sourceNode.z - targetNode.z, 2));
            // Calculate the weight based on the distance, avoiding division by zero
            double weight = 1.0 / (distance + 1e-6);

            // Use the weight to update the temperature and pressure of the target node
            targetMesh.temperatures[i] += weight * sourceMesh.temperatures[j];
            targetMesh.pressures[i] += weight * sourceMesh.pressures[j];
            weights[i] += weight;
        }

        // Normalize the temperature and pressure of the target node
        if (weights[i] > 0) {
            targetMesh.temperatures[i] /= weights[i];
            targetMesh.pressures[i] /= weights[i];
        }
    }
}