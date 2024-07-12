// Group Name: Depth First Search
// Group Members:
// - Alex Njeumi(Acse-ann23)
// - Yixiao Jing(acse-yj823)
// - Andrei Danila(edsml-acd23)
// - Fan Huang(acse-fh223)
// - Shrreya Behll(edsml-sb3323)
// - Wenxin Zhang(acse-wz2723)
#include "Slice.h"
#include "stb_image_write.h"
#include "stb_image.h"
#include <iostream>

/**
 * @brief Initializes a slice with given data and dimensions.
 *
 * This constructor takes ownership of the provided data pointer, setting up the slice dimensions according to the
 * provided width and height. It's designed to encapsulate a single 2D slice's data for further manipulation or analysis.
 *
 * @param data Pointer to the raw pixel data of the slice.
 * @param width The width of the slice in pixels.
 * @param height The height of the slice in pixels.
 */
Slice::Slice(unsigned char* data, int width, int height) : data(data), width(width), height(height) {}

/**
 * @brief Destructor for the Slice class.
 *
 * Cleans up resources associated with the slice. If the slice owns its data (as indicated by its design),
 * the destructor would be responsible for freeing that data to prevent memory leaks. However, specific
 * behavior may depend on ownership semantics which are not detailed here.
 */
Slice::~Slice() {}

/**
 * @brief Saves a particular slice to an image file, based on the specified orientation and index.
 *
 * This method supports saving slices from a volumetric dataset in three orientations (X, Y, Z). It
 * selects the appropriate slice based on the axis and index, then saves this slice to a file. For
 * axes X and Y, it constructs the slice by aggregating data across all Z slices at the given index.
 *
 * @param axis The axis along which the slice is taken ('X', 'Y', or 'Z'). Determines the orientation of the slice.
 * @param index The index of the slice along the specified axis. Must be within the bounds of the volume dimensions.
 * @param filename The path and filename where the slice image will be saved. The image is saved in PNG format.
 * @param depth The total number of slices in the Z direction (used for validation).
 * @param slices A vector of pointers, each pointing to the data of one Z slice in the volume.
 */
void Slice::saveSlice(const std::string& axis, int index, const std::string& filename, int depth, std::vector<unsigned char*>& slices) {
    if (axis == "Z" && index < depth) {
        stbi_write_png(filename.c_str(), width, height, 1, slices[index], width);
    } else if (axis == "X" && index < width) {
        std::vector<unsigned char> sliceData(height * depth);
        for (int z = 0; z < depth; ++z) {
            for (int y = 0; y < height; ++y) {
                sliceData[z * height + y] = slices[z][y * width + index];
            }
        }
        stbi_write_png(filename.c_str(), height, depth, 1, sliceData.data(), height);
    } else if (axis == "Y" && index < height) {
        std::vector<unsigned char> sliceData(width * depth);
        for (int z = 0; z < depth; ++z) {
            for (int x = 0; x < width; ++x) {
                sliceData[z * width + x] = slices[z][index * width + x];
            }
        }
        stbi_write_png(filename.c_str(), width, depth, 1, sliceData.data(), width);
    } else {
        std::cerr << "Invalid slice axis or index" << std::endl;
    }
}
