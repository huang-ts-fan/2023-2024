// Group Name: Depth First Search
// Group Members:
// - Alex Njeumi(Acse-ann23)
// - Yixiao Jing(acse-yj823)
// - Andrei Danila(edsml-acd23)
// - Fan Huang(acse-fh223)
// - Shrreya Behll(edsml-sb3323)
// - Wenxin Zhang(acse-wz2723)
#include "Image.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#include <iostream>

/**
 * @brief Default constructor, initializes an empty image with zero width, height, and channels.
 */
Image::Image() : width(0), height(0), channels(0) {}

class string;

/**
 * @brief Overloaded constructor that loads an image from a specified file.
 * @param filename Path to the image file to be loaded.
 */
Image::Image(const std::string& filename) {
    loadImage(filename);
}

Image::Image(int w, int h, int c) : width(w), height(h), channels(c) {
    allocateData(w, h, c);
}

/**
 * @brief Destructor, used for cleaning up resources. Currently does not perform any specific action.
 */
Image::~Image() {}

/**
 * @brief Loads an image from a file.
 * @param filename Path to the image file to be loaded.
 * @return true if the image is loaded successfully, false otherwise.
 */
bool Image::loadImage(const std::string& filename) {
    data.clear();
    unsigned char* raw_data = stbi_load(filename.c_str(), &width, &height, &channels, 0);
    if (!raw_data) {
        std::cerr << "Error loading image: " << filename << std::endl;
        return false;
    }

    allocateData(width, height, channels);

    int index = 0;
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            for (int ch = 0; ch < channels; ++ch) {
                data[y][x][ch] = raw_data[index++];
            }
        }
    }

    stbi_image_free(raw_data);
    return true;
}

/**
 * @brief Saves the image to a file.
 * @param filename Path where the image will be saved.
 * @return true if the image is saved successfully, false otherwise.
 */
bool Image::saveImage(const std::string& filename) const {
    int size = width * height * channels;
    std::vector<unsigned char> flat_data(size);
    int index = 0;
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            for (int ch = 0; ch < channels; ++ch) {
                flat_data[index++] = data[y][x][ch];
            }
        }
    }

    return stbi_write_png(filename.c_str(), width, height, channels, flat_data.data(), width * channels) != 0;
}

/**
 * @brief Returns the width of the image in pixels.
 * @return The width of the image.
 */
int Image::getWidth() const { return width; }

/**
 * @brief Returns the height of the image in pixels.
 * @return The height of the image.
 */
int Image::getHeight() const { return height; }

/**
 * @brief Returns the number of color channels in the image.
 * @return The number of channels (e.g., 3 for RGB, 1 for grayscale).
 */
int Image::getChannels() const { return channels; }

/**
 * @brief Provides read-only access to the image's raw pixel data.
 * @return A constant reference to the image's data matrix.
 */
const std::vector<std::vector<std::vector<unsigned char> > >& Image::getData() const {
    return data;
}

/**
 * @brief Sets the image's pixel data.
 * @param data A 3D vector containing the new pixel data for the image.
 */
void Image::setData(const std::vector<std::vector<std::vector<unsigned char> > >& newData) {
    data = newData;
}

/**
 * @brief Allocates memory for the image data based on width, height, and channels.
 * @param w Width of the image.
 * @param h Height of the image.
 * @param c Number of color channels.
 */
void Image::allocateData(int w, int h, int c) {
    width = w;
    height = h;
    channels = c;
    data.resize(h, std::vector<std::vector<unsigned char> >(w, std::vector<unsigned char>(c, 0)));
}

/**
 * @brief Converts an image to grayscale.
 * @param img The image to be converted to grayscale.
 * @return A new Image object containing the grayscale image.
 */
Image Image::convertToGrayscale(const Image& img) {
    Image grayImage;
    int width = img.getWidth();
    int height = img.getHeight();
    grayImage.allocateData(width, height, 1);

    const auto& data = img.getData();
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            unsigned char gray = static_cast<unsigned char>(
                 0.2126 * data[y][x][0] +
                 0.7152 * data[y][x][1] +
                 0.0722 * data[y][x][2]);
            grayImage.data[y][x][0] = gray;
        }
    }
    return grayImage;
}
