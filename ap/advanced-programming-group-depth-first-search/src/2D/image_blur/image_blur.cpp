// Group Name: Depth First Search
// Group Members:
// - Alex Njeumi(Acse-ann23)
// - Yixiao Jing(acse-yj823)
// - Andrei Danila(edsml-acd23)
// - Fan Huang(acse-fh223)
// - Shrreya Behll(edsml-sb3323)
// - Wenxin Zhang(acse-wz2723)
#include "image_blur.h"
#include <numeric>
#include <algorithm>

/**
 * @brief Applies box blur to an image using a specified blur size.
 *
 * This function averages the pixel values within a square (box) defined by the blur size around
 * each pixel to smooth the image, effectively reducing noise and detail. The function supports
 * multi-channel images and ensures that the blurred image retains the same dimensions as the
 * original.
 *
 * @param img The image object to be blurred.
 * @param blurSize The size of the box used to calculate the average. The box will have dimensions
 *                 of (2*blurSize + 1) x (2*blurSize + 1).
 */
void applyBoxBlur(Image& img, int blurSize) {
    const auto& data = img.getData(); // Get the original image data
    int width = img.getWidth();
    int height = img.getHeight();
    int channels = img.getChannels(); // Assuming Image has a method to get the number of color channels
    std::vector<std::vector<std::vector<unsigned char> > > blurredData(height, std::vector<std::vector<unsigned char> >(width, std::vector<unsigned char>(channels, 0)));

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            std::vector<int> sum(channels, 0);
            int count = 0;
            for (int ny = std::max(0, y - blurSize); ny <= std::min(height - 1, y + blurSize); ++ny) {
                for (int nx = std::max(0, x - blurSize); nx <= std::min(width - 1, x + blurSize); ++nx) {
                    for (int ch = 0; ch < channels; ++ch) {
                        sum[ch] += data[ny][nx][ch];
                    }
                    ++count;
                }
            }
            for (int ch = 0; ch < channels; ++ch) {
                blurredData[y][x][ch] = static_cast<unsigned char>(sum[ch] / count); // Cast to unsigned char, ensuring the division result fits within the byte range
            }
        }
    }

    img.setData(blurredData); // Update the image with the blurred data
}

/**
 * @brief Applies Gaussian blur to an image using a specified standard deviation (sigma) and kernel size.
 *
 * Gaussian blur is applied by convolving the image with a Gaussian function, resulting in a smooth
 * and blurred image. This function calculates a Gaussian kernel based on the provided sigma and
 * kernel size, normalizes it, and then applies it to the image. The kernel size must be odd, and if
 * an even size is provided, it's incremented by one to make it odd. The function supports multi-channel
 * images.
 *
 * @param img The image object to be blurred.
 * @param sigma The standard deviation of the Gaussian function, controlling the extent of blurring.
 * @param kernelSize The size of the Gaussian kernel. It will be adjusted to the nearest odd number.
 */
void applyGaussianBlur(Image& img, double sigma, int kernelSize) {
    if (kernelSize % 2 == 0) kernelSize++;
    std::vector<std::vector<double> > kernel(kernelSize, std::vector<double>(kernelSize));
    double sum = 0.0;
    int radius = kernelSize / 2;
    for (int y = -radius; y <= radius; ++y) {
        for (int x = -radius; x <= radius; ++x) {
            double value = (1 / (2 * M_PI * sigma * sigma)) * exp(-(x * x + y * y) / (2 * sigma * sigma));
            kernel[y + radius][x + radius] = value;
            sum += value;
        }
    }
    // Normalize the kernel
    for (int y = 0; y < kernelSize; ++y) {
        for (int x = 0; x < kernelSize; ++x) {
            kernel[y][x] /= sum;
        }
    }

    // Apply Gaussian blur
    const auto& data = img.getData();
    int width = img.getWidth();
    int height = img.getHeight();
    int channels = img.getChannels();
    std::vector<std::vector<std::vector<unsigned char> > > blurredData(height, std::vector<std::vector<unsigned char> >(width, std::vector<unsigned char>(channels, 0)));

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            std::vector<double> sum(channels, 0.0);
            for (int ky = -radius; ky <= radius; ++ky) {
                for (int kx = -radius; kx <= radius; ++kx) {
                    int ny = std::min(std::max(y + ky, 0), height - 1);
                    int nx = std::min(std::max(x + kx, 0), width - 1);
                    for (int ch = 0; ch < channels; ++ch) {
                        sum[ch] += data[ny][nx][ch] * kernel[ky + radius][kx + radius];
                    }
                }
            }
            for (int ch = 0; ch < channels; ++ch) {
                blurredData[y][x][ch] = static_cast<unsigned char>(std::min(std::max(int(sum[ch]), 0), 255));
            }
        }
    }

    // Update the image with the blurred data
    img.setData(blurredData);
}

/**
 * @brief Applies median blur to an image using a specified kernel size.
 *
 * Median blur is a non-linear filter that replaces each pixel's value with the median value of the
 * intensities in the neighborhood defined by the kernel size. This method is particularly effective
 * at removing salt-and-pepper noise while preserving edges in the image. The function supports
 * multi-channel images and uses a sliding window approach to apply the median filter.
 *
 * @param img The image object to be processed.
 * @param kernelSize The size of the square kernel used for the median filtering, which defines the
 *                   neighborhood size for each pixel.
 */
void applyMedianBlur(Image& img, int kernelSize) {
    int width = img.getWidth();
    int height = img.getHeight();
    int channels = img.getChannels();
    const auto& data = img.getData(); // Get the original image data

    std::vector<std::vector<std::vector<unsigned char> > > resultData(height, std::vector<std::vector<unsigned char> >(width, std::vector<unsigned char>(channels, 0)));
    int offset = kernelSize / 2;

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            for (int ch = 0; ch < channels; ++ch) {
                std::vector<unsigned char> neighborhood; // Storing neighborhood pixel values
                for (int ky = -offset; ky <= offset; ++ky) {
                    for (int kx = -offset; kx <= offset; ++kx) {
                        int nx = std::min(std::max(x + kx, 0), width - 1);
                        int ny = std::min(std::max(y + ky, 0), height - 1);
                        neighborhood.push_back(data[ny][nx][ch]);
                    }
                }
                // Calculate the median
                std::nth_element(neighborhood.begin(), neighborhood.begin() + neighborhood.size() / 2, neighborhood.end());
                unsigned char medianValue = neighborhood[neighborhood.size() / 2];

                resultData[y][x][ch] = medianValue; // Applying median filtering
            }
        }
    }

    // Update the image with the processed data
    img.setData(resultData);
}
