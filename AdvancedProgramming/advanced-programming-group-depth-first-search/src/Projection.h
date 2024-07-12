// Group Name: Depth First Search
// Group Members:
// - Alex Njeumi(Acse-ann23)
// - Yixiao Jing(acse-yj823)
// - Andrei Danila(edsml-acd23)
// - Fan Huang(acse-fh223)
// - Shrreya Behll(edsml-sb3323)
// - Wenxin Zhang(acse-wz2723)
#ifndef PROJECTION_H
#define PROJECTION_H

#include <string>
#include <vector>

/**
 * @class Projection
 * @brief Provides static methods for generating 2D projections from 3D volumetric data.
 *
 * The Projection class contains a set of static methods designed to create different types of
 * intensity projections. These projections are useful in various fields, especially in medical
 * imaging for visualizing the structure of complex volumes. Each method takes a set of volumetric
 * slices and generates a 2D image based on specific intensity criteria:
 *
 * - Maximum Intensity Projection (MIP): Highlights the highest intensity values, useful for
 *   visualizing bright structures against a darker background.
 * - Average Intensity Projection (AIP): Provides an overview of the average intensity values,
 *   useful for assessing the overall distribution of densities within the volume.
 * - Minimum Intensity Projection (MinIP): Emphasizes the lowest intensity values, often used
 *   for visualizing fluid-filled spaces and airways.
 */
class Projection {
public:
    static void generateMIP(const std::string& filename, int width, int height, int depth, std::vector<unsigned char*>& slices);
    static void generateAIP(const std::string& filename, int width, int height, int depth, std::vector<unsigned char*>& slices);
    static void generateMinIP(const std::string& filename, int width, int height, int depth, std::vector<unsigned char*>& slices);
};

#endif // PROJECTION_H
