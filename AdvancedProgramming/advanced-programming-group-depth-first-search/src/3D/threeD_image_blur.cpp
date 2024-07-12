// Group Name: Depth First Search
// Group Members:
// - Alex Njeumi(Acse-ann23)
// - Yixiao Jing(acse-yj823)
// - Andrei Danila(edsml-acd23)
// - Fan Huang(acse-fh223)
// - Shrreya Behll(edsml-sb3323)
// - Wenxin Zhang(acse-wz2723)
#include "threeD_image_blur.h"
#include "../Volume.h"

#include <cmath>
#include <iostream>
#include <vector>
#include <algorithm>

/**
 * @brief Generates a 3D Gaussian kernel with a specified size and standard deviation (sigma).
 *
 * This function creates a cubic Gaussian kernel used for applying a 3D Gaussian blur. It calculates
 * the Gaussian values for each cell in the cube based on the distance from the center, normalizing
 * the kernel so that the sum of all values equals 1. This kernel is typically used to apply a
 * Gaussian blur to 3D data, such as medical images or any volumetric data.
 *
 * @param size The size of the kernel cube (must be odd).
 * @param sigma The standard deviation of the Gaussian distribution.
 * @return A 3D vector of doubles representing the Gaussian kernel.
 */
std::vector<std::vector<std::vector<double>>> generate3DGaussianKernel(int size, double sigma) {
    std::vector<std::vector<std::vector<double>>> kernel(size, std::vector<std::vector<double>>(size, std::vector<double>(size)));
    int center = size / 2;
    double sum = 0.0;

    for (int x = 0; x < size; ++x) {
        for (int y = 0; y < size; ++y) {
            for (int z = 0; z < size; ++z) {
                double dx = x - center;
                double dy = y - center;
                double dz = z - center;
                double value = exp(-(dx * dx + dy * dy + dz * dz) / (2 * sigma * sigma));
                kernel[x][y][z] = value;
                sum += value;
            }
        }
    }

    for (int x = 0; x < size; ++x) {
        for (int y = 0; y < size; ++y) {
            for (int z = 0; z < size; ++z) {
                kernel[x][y][z] /= sum;
            }
        }
    }

    return kernel;
}

/**
 * @brief Applies a 3D Gaussian blur to volumetric data using a precomputed Gaussian kernel.
 *
 * This function convolves the volume data with the given Gaussian kernel, effectively blurring the
 * data. This is useful for noise reduction and smoothing of 3D datasets. The kernel is applied to
 * each voxel in the volume considering its neighbors, weighted by the kernel values to achieve the
 * blurring effect. The size of the kernel determines the extent of the blur.
 *
 * @param volume The volume data to be blurred, represented by a Volume object.
 * @param kernel The 3D Gaussian kernel to use for the blurring operation.
 */
void apply3DGaussianBlur(Volume &volume, const std::vector<std::vector<std::vector<double>>>& kernel) {
    int size = kernel.size();
    int center = size / 2;
    auto volumeData = volume.getVolumeDoubleNonConst();
    auto blurredVolume = volume.getVolumeDoubleNonConst();

    for (int x = center; x < volumeData.size() - center; ++x) {
        for (int y = center; y < volumeData[0].size() - center; ++y) {
            for (int z = center; z < volumeData[0][0].size() - center; ++z) {
                double sum = 0.0;
                for (int kz = 0; kz < size; ++kz) {
                    int pz = z + (kz - center);
                    for (int ky = 0; ky < size; ++ky) {
                        int py = y + (ky - center);
                        for (int kx = 0; kx < size; ++kx) {
                            int px = x + (kx - center);
                            // Flip the loop order to prioritize sequential memory access
                            sum += volumeData[px][py][pz] * kernel[kx][ky][kz];
                        }
                    }
                }
                blurredVolume[x][y][z] = sum;
            }
        }
        std::cout << "Processing x=" << x << std::endl;
    }

    volume.setData(blurredVolume);
}

/**
 * @brief Applies a 3D median filter to volumetric data using a specified kernel size.
 *
 * This function filters the volume data by replacing each voxel value with the median value from a
 * neighborhood defined by the kernel size. It's particularly effective at removing 'salt-and-pepper'
 * noise from the volume while preserving edges. The median is computed in a histogram-based
 * approach to efficiently handle large datasets. This filtering process smoothens the volume data
 * without blurring the edges, maintaining the structural integrity of the volumetric data.
 *
 * @param volume The volume data to be filtered, represented by a Volume object.
 * @param kernelSize The size of the cubic kernel used for filtering (must be odd).
 */
void apply3DMedianFilter(Volume &volume, int kernelSize) {
    std::vector<std::vector<std::vector<double>>>& volumeData = volume.getVolumeDoubleNonConst();
    int size = volumeData.size();
    int depth = volumeData[0][0].size();
    int height = volumeData[0].size();
    int center = kernelSize / 2;
    auto filteredVolume = volumeData;
    const int bins = 256;
    double binSize = 255.0 / (bins - 1);

    for (int x = center; x < size - center; ++x) {
        for (int y = center; y < height - center; ++y) {
            std::vector<int> histogram(bins, 0);
            int totalElements = 0;
            for (int kx = -center; kx <= center; ++kx) {
                for (int ky = -center; ky <= center; ++ky) {
                    for (int kz = -center; kz <= center; ++kz) {
                        int binIndex = std::min(static_cast<int>(std::floor((volumeData[x + kx][y + ky][center + kz]) / binSize)), bins - 1);
                        histogram[binIndex]++;
                        totalElements++;
                    }
                }
            }
            for (int z = center; z < depth - center; ++z) {
                if (z > center) {
                    for (int kx = -center; kx <= center; ++kx) {
                        for (int ky = -center; ky <= center; ++ky) {
                            int oldBinIndex = std::min(static_cast<int>(std::floor(volumeData[x + kx][y + ky][z - center - 1] / binSize)), bins - 1);
                            int newBinIndex = std::min(static_cast<int>(std::floor(volumeData[x + kx][y + ky][z + center] / binSize)), bins - 1);
                            histogram[oldBinIndex]--;
                            histogram[newBinIndex]++;
                        }
                    }
                }
                int medianBin = 0, count = 0;
                for (; medianBin < bins; ++medianBin) {
                    count += histogram[medianBin];
                    if (count > totalElements / 2) break;
                }
                double medianValue = medianBin * binSize;
                filteredVolume[x][y][z] = medianValue;
            }
        }
        std::cout << "Processing x=" << x << std::endl;
    }
    volume.setData(filteredVolume);
}

