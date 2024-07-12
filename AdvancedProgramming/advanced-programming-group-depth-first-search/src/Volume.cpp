// Group Name: Depth First Search
// Group Members:
// - Alex Njeumi(Acse-ann23)
// - Yixiao Jing(acse-yj823)
// - Andrei Danila(edsml-acd23)
// - Fan Huang(acse-fh223)
// - Shrreya Behll(edsml-sb3323)
// - Wenxin Zhang(acse-wz2723)
#include "stb_image.h"
#include "stb_image_write.h"

#include "Volume.h"

#include <iostream>
#include <filesystem>
#include <sstream>

namespace fs = std::__fs::filesystem;

/**
 * @brief Initializes an empty volume with zero dimensions.
 *
 * Sets up an empty volume with no width, height, or depth, and initializes internal structures for
 * storing volume data. This constructor prepares the Volume object for loading volumetric data.
 */
Volume::Volume() : width(0), height(0), depth(0) {}

/**
 * @brief Cleans up loaded volume data.
 *
 * Frees the memory allocated for storing the slices of the volume, ensuring no memory leaks occur.
 * This destructor is crucial for managing the lifecycle of the volumetric data.
 */
Volume::~Volume() {
    for (auto& slice : slices) {
        stbi_image_free(slice);
    }
}

/**
 * @brief Loads volume data from a directory of image files.
 *
 * Iterates through image files in a specified directory, loading them as slices of the volume.
 * Only files with a .png extension are considered. Images are expected to be named in a way that
 * sorting them alphabetically orders them correctly by slice index.
 *
 * @param directory Directory containing the slice images.
 * @param startIndex Index of the first slice to load.
 * @param finalIndex Index of the last slice to load.
 * @return true if the volume is loaded successfully, false otherwise.
 */
bool Volume::loadFromDirectory(const std::string& directory, int startIndex, int finalIndex) {
    std::vector<std::string> fileNames;
    for (const auto& entry : fs::directory_iterator(directory)) {
        if (entry.path().extension() == ".png") {
            fileNames.push_back(entry.path());
        }
    }
    std::sort(fileNames.begin(), fileNames.end());
    if (finalIndex == 0) {
        finalIndex = fileNames.size()-1;
    }
    if (startIndex < 0 || finalIndex >= fileNames.size() || startIndex > finalIndex) {
        std::cerr << "Invalid start or final index." << std::endl;
        return false;
    }
    depth = finalIndex - startIndex + 1;
    for (int i = startIndex; i <= finalIndex; ++i) {
        int w, h, n;
        unsigned char* img = stbi_load(fileNames[i].c_str(), &w, &h, &n, 0);
        if (img == nullptr) {
            std::cerr << "Failed to load image: " << fileNames[i] << std::endl;
            return false;
        }
        if (i == startIndex) {
            width = w;
            height = h;
        }
        slices.push_back(img);
    }
    return true;
}

/**
 * @brief Loads and optionally filters volume data from a directory of image files.
 *
 * Similar to loadFromDirectory, but includes an additional step that may apply filtering to the
 * loaded slices. This method demonstrates an extension point for preprocessing slice data.
 *
 * @param directoryPath Directory containing the slice images.
 * @param startIndex Index of the first slice to load.
 * @param finalIndex Index of the last slice to load.
 * @return true if the volume is loaded and filtered successfully, false otherwise.
 */
bool Volume::loadFromDirectory_filter(const std::string& directoryPath, int startIndex, int finalIndex) {
    std::vector<std::string> fileNames;
    for (const auto& entry : fs::directory_iterator(directoryPath)) {
        fileNames.push_back(entry.path().string());
    }
    if (finalIndex == 0 || finalIndex >= fileNames.size()) {
        finalIndex = fileNames.size() - 1;
    }
    if (startIndex < 0 || finalIndex >= fileNames.size() || startIndex > finalIndex) {
        std::cerr << "Invalid start or final index." << std::endl;
        return false;
    }
    depth = finalIndex - startIndex + 1;
    int channels;
    unsigned char* img = stbi_load(fileNames[startIndex].c_str(), &width, &height, &channels, 1);
    if (!img) {
        std::cerr << "Failed to preload image: " << fileNames[startIndex] << std::endl;
        return false;
    }
    stbi_image_free(img);
    volumeDouble.resize(depth, std::vector<std::vector<double>>(height, std::vector<double>(width)));
    for (int d = startIndex; d <= finalIndex; ++d) {
        img = stbi_load(fileNames[d].c_str(), &width, &height, &channels, 1);
        if (!img) {
            std::cerr << "Failed to load image: " << fileNames[d] << std::endl;
            return false;
        }
        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                volumeDouble[d-startIndex][y][x] = static_cast<double>(img[y * width + x]);
            }
        }
        stbi_image_free(img);
    }
    return true;
}

/**
 * @brief Accessors for the volume data in double-precision format.
 *
 * getVolumeDoubleNonConst returns a non-const reference allowing modification of the volume data,
 * while getVolumeDouble provides read-only access to the data.
 *
 * @return Reference or const reference to the volume's double-precision data.
 */
std::vector<std::vector<std::vector<double>>>& Volume::getVolumeDoubleNonConst() {
    return volumeDouble;
}

/**
 * @brief Sets the volume's data with a provided 3D vector.
 *
 * Allows for the replacement of the entire volume's data with new data. This method can be used for
 * updating the volume after processing or transformations.
 *
 * @param volumeData New data to replace the current volume data.
 */
void Volume::setData(std::vector<std::vector<std::vector<double>>>& volumeData){
    volumeDouble = volumeData;
}

/**
 * @brief Converts the volume's data into a vector of unsigned char pointers.
 *
 * Useful for interfacing with APIs that require raw pointers to pixel data. This method may involve
 * converting the internal double-precision data into 8-bit unsigned char values.
 *
 * @return A vector of pointers, each pointing to the data of one slice in the volume.
 */
std::vector<unsigned char*> Volume::convertToCharPointers() const {
    std::vector<unsigned char*> charData(depth);
    for (int z = 0; z < depth; ++z) {
        charData[z] = new unsigned char[width * height];
        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                int index = y * width + x;
                double value = clamp(volumeDouble[z][y][x], 0.0, 255.0);
                charData[z][index] = static_cast<unsigned char>(value);
            }
        }
    }
    return charData;
}
/**
 * @brief Accessors for the dimensions of the volume.
 *
 * These methods return the width, height, and depth of the volume, respectively, providing information
 * about the size of the volumetric data.
 *
 * @return The dimension specified by the method name.
 */
int Volume::getWidth() const { return width; }
int Volume::getHeight() const { return height; }
int Volume::getDepth() const { return depth; }

/**
 * @brief Returns a reference to the raw slice data.
 *
 * Provides access to the underlying slice data stored as raw unsigned char pointers, allowing for direct
 * manipulation or analysis of the slice data.
 *
 * @return A reference to the vector of slice pointers.
 */
std::vector<unsigned char*>& Volume::getSlices() { return slices; }


/**
 * @brief Saves the volume data back to a series of image files.
 *
 * Exports the volume data to image files, storing each slice as a separate image. The files are saved
 * within a specified directory, with filenames indicating the slice index.
 *
 * @param directory Directory where the slice images will be saved.
 */
void Volume::saveVolume(const std::string& directory) const {
    // Ensure the directory exists
    std::filesystem::create_directories(directory);

    for (int z = 0; z < depth; ++z) {
        // Construct the filename for each slice
        std::stringstream ss;
        ss << directory << "/image_" << std::setw(4) << std::setfill('0') << z << ".png";
        std::string filename = ss.str();

        // Allocate memory for the image
        unsigned char* img = new unsigned char[width * height];

        // Convert the volumeDouble data to unsigned char
        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                double value = clamp(volumeDouble[z][y][x], 0.0, 255.0);
                img[y * width + x] = static_cast<unsigned char>(value);
            }
        }

        // Write the slice to a PNG file
        stbi_write_png(filename.c_str(), width, height, 1, img, width);

        // Free the allocated memory for the image
        delete[] img;
    }
    std::cout << "Volume saved successfully." << std::endl;
}

bool Volume::loadFromDirectory_time(const std::string& directoryPath, int startIndex, int finalIndex) {
    std::vector<std::string> fileNames;
    for (const auto& entry : fs::directory_iterator(directoryPath)) {
        std::string filePath = entry.path().string();
        // check if the file is an image
        if (filePath.ends_with(".png") || filePath.ends_with(".jpg") || filePath.ends_with(".jpeg") || filePath.ends_with(".bmp")) {
            fileNames.push_back(filePath);
        }
    }

    // if finalIndex is not specified, set it to the last image
    if (finalIndex == 0 || finalIndex >= fileNames.size()) {
        finalIndex = fileNames.size() - 1;
    }
    // check if the start and final index are valid
    if (startIndex < 0 || finalIndex >= fileNames.size() || startIndex > finalIndex) {
        std::cerr << "Invalid start or final index." << std::endl;
        return false;
    }

    depth = finalIndex - startIndex + 1;
    int channels;
    unsigned char* img = stbi_load(fileNames[startIndex].c_str(), &width, &height, &channels, 1);
    if (!img) {
        std::cerr << "Failed to preload image: " << fileNames[startIndex] << std::endl;
        return false;
    }
    stbi_image_free(img);

    volumeDouble.resize(depth, std::vector<std::vector<double>>(height, std::vector<double>(width)));
    for (int d = startIndex; d <= finalIndex; ++d) {
        img = stbi_load(fileNames[d].c_str(), &width, &height, &channels, 1);
        if (!img) {
            std::cerr << "Failed to load image: " << fileNames[d] << std::endl;
            return false;
        }
        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                volumeDouble[d - startIndex][y][x] = static_cast<double>(img[y * width + x]);
            }
        }
        stbi_image_free(img);
    }
    return true;
}