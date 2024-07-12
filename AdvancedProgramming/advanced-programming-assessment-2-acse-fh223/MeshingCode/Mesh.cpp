#include "Mesh.h"

Mesh::Mesh(const std::vector<Node>& _nodes, const std::vector<Element>& _elements,
	const std::vector<double>& _temperatures, const std::vector<double>& _pressures)
	: nodes(_nodes), elements(_elements), temperatures(_temperatures), pressures(_pressures)
{
}

// Display mesh information
void Mesh::displayInfo() const
{
	std::cout << "Mesh Information:" << std::endl;
	// Display nodes
	std::cout << "Nodes:" << std::endl;
	for (const auto& node : nodes)
	{
		std::cout << "  (" << node.x << ", " << node.y << ", " << node.z << ")" << std::endl;
	}

	// Display elements
	std::cout << "Elements:" << std::endl;
	for (const auto& element : elements)
	{
		std::cout << "  Node Indices: ";
		for (int index : element.nodeIndices) {
			std::cout << index << " ";
		}
		std::cout << std::endl;
	}

	// Display temperatures
	std::cout << "Temperatures:" << std::endl;
	for (double temp : temperatures)
	{
		std::cout << temp << " ";
	}
	std::cout << std::endl;

	// Display pressures
	std::cout << "Pressures:" << std::endl;
	for (double pressure : pressures)
	{
		std::cout << pressure << " ";
	}
	std::cout << std::endl;
}

// Set the temperatures of the nodes
void Mesh::setTemperatures(const std::vector<double>& _temperatures)
{
	temperatures = _temperatures;
}

// Set the pressures of the nodes
void Mesh::setPressures(const std::vector<double>& _pressures)
{
	pressures = _pressures;
}

// Get the temperatures of the nodes
std::vector<double> Mesh::getTemperatures() const
{
	return temperatures;
}

// Get the pressures of the nodes
std::vector<double> Mesh::getPressures() const
{
	return pressures;
}

