// Group Name: Depth First Search
// Group Members:
// - Alex Njeumi(Acse-ann23)
// - Yixiao Jing(acse-yj823)
// - Andrei Danila(edsml-acd23)
// - Fan Huang(acse-fh223)
// - Shrreya Behll(edsml-sb3323)
// - Wenxin Zhang(acse-wz2723)
#include "Projection.h"
#include "stb_image_write.h"
#include "stb_image.h"
#include <algorithm>
#include <limits>

/**
 * @brief Generates a Maximum Intensity Projection (MIP) from volumetric data.
 *
 * MIP renders the highest value encountered along each ray traced through the data to the viewer's eye,
 * highlighting the brightest structures in the volume. Useful in medical imaging to visualize bones, vessels, etc.
 *
 * @param filename Path where the generated MIP image will be saved.
 * @param width Width of each slice.
 * @param height Height of each slice.
 * @param depth Number of slices.
 * @param slices Vector of pointers to the slice data.
 */
void Projection::generateMIP(const std::string& filename, int width, int height, int depth, std::vector<unsigned char*>& slices) {
    std::vector<unsigned char> mipData(width * height, 0);
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            unsigned char maxIntensity = 0;
            for (int z = 0; z < depth; ++z) {
                unsigned char currentIntensity = slices[z][y * width + x];
                if (currentIntensity > maxIntensity) {
                    maxIntensity = currentIntensity;
                }
            }
            mipData[y * width + x] = maxIntensity;
        }
    }
    stbi_write_png(filename.c_str(), width, height, 1, mipData.data(), width);
}

/**
 * @brief Generates an Average Intensity Projection (AIP) from volumetric data.
 *
 * AIP calculates the average value along each ray traced through the data, providing a view that represents
 * the average densities of structures throughout the volume. Often used to visualize soft tissues in medical imaging.
 *
 * @param filename Path where the generated AIP image will be saved.
 * @param width Width of each slice.
 * @param height Height of each slice.
 * @param depth Number of slices.
 * @param slices Vector of pointers to the slice data.
 */
void Projection::generateAIP(const std::string& filename, int width, int height, int depth, std::vector<unsigned char*>& slices) {
    std::vector<unsigned char> aipData(width * height, 0); // save AIP array
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            unsigned long sumIntensity = 0;
            for (int z = 0; z < depth; ++z) {
                sumIntensity += slices[z][y * width + x];
            }
            aipData[y * width + x] = static_cast<unsigned char>(sumIntensity / depth);
        }
    }
    stbi_write_png(filename.c_str(), width, height, 1, aipData.data(), width);
}

/**
 * @brief Generates a Minimum Intensity Projection (MinIP) from volumetric data.
 *
 * MinIP renders the lowest value encountered along each ray traced through the data to the viewer's eye,
 * making it useful for visualizing structures filled with air or fluid in medical imaging.
 *
 * @param filename Path where the generated MinIP image will be saved.
 * @param width Width of each slice.
 * @param height Height of each slice.
 * @param depth Number of slices.
 * @param slices Vector of pointers to the slice data.
 */
void Projection::generateMinIP(const std::string& filename, int width, int height, int depth, std::vector<unsigned char*>& slices) {
    std::vector<unsigned char> minipData(width * height); // save MinIP array

    std::fill(minipData.begin(), minipData.end(), std::numeric_limits<unsigned char>::max());

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            unsigned char minIntensity = std::numeric_limits<unsigned char>::max();
            for (int z = 0; z < depth; ++z) {
                unsigned char currentIntensity = slices[z][y * width + x];
                if (currentIntensity < minIntensity) {
                    minIntensity = currentIntensity;
                }
            }
            minipData[y * width + x] = minIntensity;
        }
    }
    stbi_write_png(filename.c_str(), width, height, 1, minipData.data(), width);
}
