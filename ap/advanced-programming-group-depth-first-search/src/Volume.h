// Group Name: Depth First Search
// Group Members:
// - Alex Njeumi(Acse-ann23)
// - Yixiao Jing(acse-yj823)
// - Andrei Danila(edsml-acd23)
// - Fan Huang(acse-fh223)
// - Shrreya Behll(edsml-sb3323)
// - Wenxin Zhang(acse-wz2723)
#ifndef VOLUME_H
#define VOLUME_H
#include <string>
#include <vector>

/**
 * @class Volume
 * @brief Manages and processes 3D volumetric data.
 *
 * The Volume class is designed to handle 3D data, offering functionalities to load volumetric data from a
 * directory containing image slices, convert this data for processing, and manipulate or analyze the volume
 * through various operations. It supports both raw pixel data management and operations on double-precision
 * volumetric data, accommodating a wide range of applications from medical imaging to scientific visualization.
 *
 * ## Constructors:
 * - Volume(): Initializes an empty volume with zero dimensions.
 *
 * ## Destructor:
 * - ~Volume(): Ensures proper cleanup of allocated resources.
 *
 * ## Member Functions:
 * - loadFromDirectory(const std::string&, int, int): Loads volumetric data from a sequence of image files.
 * - loadFromDirectory_filter(const std::string&, int, int): Loads and applies a filtering operation during load.
 * - convertToCharPointers() const: Converts and returns the volume data as a vector of unsigned char pointers.
 * - getVolumeDoubleNonConst(), getVolumeDouble() const: Accessors for the volume data in double-precision format.
 * - setData(std::vector<std::vector<std::vector<double>>> &): Sets the volume data with a provided 3D vector.
 * - getWidth() const, getHeight() const, getDepth() const: Accessors for the volume dimensions.
 * - getSlices(): Returns a reference to the raw slice data.
 * - saveVolume(const std::string&) const: Saves the volume data back to a series of image files.
 *
 * ## Private Members:
 * - width, height, depth: Dimensions of the volume.
 * - slices: Vector storing pointers to raw slice data.
 * - volumeDouble: 3D vector for storing volume data in double precision, useful for advanced processing.
 * - clamp<T>(T value, T low, T high) const: Utility template function to clamp values within a specified range.
 */
class Volume {
public:
    Volume();
    ~Volume();

    bool loadFromDirectory(const std::string& directory, int startIndex, int finalIndex);
    bool loadFromDirectory_filter(const std::string& directoryPath, int startIndex, int finalIndex);
    bool loadFromDirectory_time(const std::string& directoryPath, int startIndex, int finalIndex);
    std::vector<unsigned char*> convertToCharPointers() const;
    std::vector<std::vector<std::vector<double>>>& getVolumeDoubleNonConst();
    const std::vector<std::vector<std::vector<double>>>& getVolumeDouble() const;
    void setData(std::vector<std::vector<std::vector<double>>>& volumeData);

    int getWidth() const;
    int getHeight() const;
    int getDepth() const;
    std::vector<unsigned char*>& getSlices();
    void saveVolume(const std::string& directory) const;

private:
    int width, height, depth;
    std::vector<unsigned char*> slices;
    std::vector<std::vector<std::vector<double>>> volumeDouble;
    template<typename T>
    T clamp(T value, T low, T high) const {
        return (value < low) ? low : (value > high) ? high : value;
    }
};

#endif // VOLUME_H
