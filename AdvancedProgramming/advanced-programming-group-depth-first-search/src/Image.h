// Group Name: Depth First Search
// Group Members:
// - Alex Njeumi(Acse-ann23)
// - Yixiao Jing(acse-yj823)
// - Andrei Danila(edsml-acd23)
// - Fan Huang(acse-fh223)
// - Shrreya Behll(edsml-sb3323)
// - Wenxin Zhang(acse-wz2723)
#ifndef IMAGE_H
#define IMAGE_H

#include <vector>
#include <string>

/**
 * @class Image
 * @brief Represents an image, encapsulating data and operations for image processing.
 *
 * The Image class is designed to manage and manipulate image data. It supports loading and saving images,
 * accessing image properties (such as width, height, and color channels), and performing basic image
 * processing operations like conversion to grayscale. The class uses a 3D vector to store image data,
 * which accommodates both color (RGB) and grayscale images, enabling a wide range of image processing
 * tasks.
 *
 * ## Constructors:
 * - Image(): Default constructor, initializes an empty image.
 * - explicit Image(const std::string& filename): Initializes an image by loading data from the specified file.
 *
 * ## Destructor:
 * - ~Image(): Cleans up resources.
 *
 * ## Member Functions:
 * - loadImage(const std::string& filename): Loads image data from a file.
 * - saveImage(const std::string& filename) const: Saves the image data to a file.
 * - getWidth() const: Returns the width of the image.
 * - getHeight() const: Returns the height of the image.
 * - getChannels() const: Returns the number of color channels in the image.
 * - getData() const: Provides read-only access to the image data.
 * - setData(const std::vector<std::vector<std::vector<unsigned char> > >& data): Sets the image's data.
 * - static convertToGrayscale(const Image& img): Converts a given image to grayscale and returns the new image.
 *
 * ## Private Member Variables:
 * - width, height, channels: Dimensions and channel information of the image.
 * - data: Stores the image's pixel data, accommodating both color and grayscale formats.
 *
 * ## Usage:
 * The Image class is intended for use in applications requiring direct manipulation of image pixels,
 * such as in computer vision, image processing, and graphic design tools. It provides a foundational
 * structure that can be extended or used in conjunction with other classes for more complex image
 * processing operations.
 */
class Image {
public:
    Image();
    explicit Image(const std::string& filename);
    Image(int w, int h, int c = 3); // Create an image with dimensions and optional channel count
    ~Image();

    bool loadImage(const std::string& filename);
    bool saveImage(const std::string& filename) const;

    int getWidth() const;
    int getHeight() const;
    int getChannels() const;
    const std::vector<std::vector<std::vector<unsigned char> > >& getData() const;
    static Image convertToGrayscale(const Image& img);

    void setData(const std::vector<std::vector<std::vector<unsigned char> > >& data);
private:
    int width, height, channels;
    std::vector<std::vector<std::vector<unsigned char> > > data; // 3D vector for RGB, 2D vector for grayscale

    void allocateData(int w, int h, int c);
};

#endif // IMAGE_H
