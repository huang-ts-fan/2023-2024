// Group Name: Depth First Search
// Group Members:
// - Alex Njeumi(Acse-ann23)
// - Yixiao Jing(acse-yj823)
// - Andrei Danila(edsml-acd23)
// - Fan Huang(acse-fh223)
// - Shrreya Behll(edsml-sb3323)
// - Wenxin Zhang(acse-wz2723)
#ifndef SLICE_H
#define SLICE_H

#include <string>
#include <vector>

/**
 * @class Slice
 * @brief Manages a single slice of 3D volumetric data, providing functionalities for handling and exporting the slice.
 *
 * The Slice class encapsulates the data for a single 2D slice extracted from a 3D volume, along with its dimensions.
 * It is designed to handle operations specific to a single slice, such as saving the slice data to an image file.
 * This class simplifies the manipulation and storage of 2D sections from larger volumetric datasets, which is common
 * in medical imaging, scientific visualization, and 3D data analysis.
 *
 * ## Constructor:
 * - Slice(unsigned char* data, int width, int height): Initializes a new slice with specified data and dimensions.
 *
 * ## Destructor:
 * - ~Slice(): Cleans up resources, ensuring proper memory management for the slice's data.
 *
 * ## Member Function:
 * - saveSlice(const std::string& axis, int index, const std::string& filename, int depth, std::vector<unsigned char*>& slices):
 *   Saves the current slice to a file, potentially involving additional processing based on the volumetric context
 *   and desired orientation.
 *
 * ## Private Members:
 * - data: Pointer to the slice's pixel data.
 * - width, height: Dimensions of the slice, specifying its width and height in pixels.
 */
class Slice {
public:
    Slice(unsigned char* data, int width, int height);
    ~Slice();

    void saveSlice(const std::string& axis, int index, const std::string& filename, int depth, std::vector<unsigned char*>& slices);
private:
    unsigned char* data;
    int width, height;
};

#endif // SLICE_H
