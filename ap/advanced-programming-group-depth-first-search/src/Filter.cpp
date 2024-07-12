// Group Name: Depth First Search
// Group Members:
// - Alex Njeumi(Acse-ann23)
// - Yixiao Jing(acse-yj823)
// - Andrei Danila(edsml-acd23)
// - Fan Huang(acse-fh223)
// - Shrreya Behll(edsml-sb3323)
// - Wenxin Zhang(acse-wz2723)
#include "Filter.h"

// Edge detection functions
/**
 * @brief Applies edge detection on an image using specified X and Y operator templates.
 *
 * This function uses two 3x3 operator templates to detect edges in the image by calculating
 * the gradient magnitude for each pixel. The result is a grayscale image where edges are highlighted,
 * useful for identifying the boundaries within images. Supports customization through different
 * operators to achieve various edge detection effects.
 *
 * @param img The image on which to apply edge detection.
 * @param operatorX The 3x3 matrix representing the X direction operator.
 * @param operatorY The 3x3 matrix representing the Y direction operator.
 */
void Filter::applyEdgeDetection(Image& img, const float operatorX[3][3], const float operatorY[3][3]) {
    ::applyEdgeDetection(img, operatorX, operatorY);
}

/**
 * @brief Applies Roberts Cross edge detection on an image.
 *
 * This function implements the Roberts Cross operator for edge detection, utilizing a 2x2 operator.
 * It calculates the gradient magnitude using the Roberts Cross approximation to the derivative, highlighting
 * the edges in the image as a result. This method is particularly effective for high-contrast edges,
 * useful for edge detection in images with low noise.
 *
 * @param img The image on which to apply Roberts Cross edge detection.
 */
void Filter::applyRobertsCrossEdgeDetection(Image& img) {
    ::applyRobertsCrossEdgeDetection(img);
}

// 2D blur functions
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
void Filter::applyBoxBlur(Image& img, int blurSize) {
    ::applyBoxBlur(img, blurSize);
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
void Filter::applyGaussianBlur(Image& img, double sigma, int kernelSize) {
    ::applyGaussianBlur(img, sigma, kernelSize);
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
void Filter::applyMedianBlur(Image& img, int kernelSize) {
    ::applyMedianBlur(img, kernelSize);
}


// Colour correction functions
/**
 * @brief Converts an image to grayscale.
 *
 * This function applies grayscale conversion to the input image, reducing it to shades of gray
 * by averaging the RGB values of each pixel or using a more sophisticated method of luminance calculation.
 *
 * @param img The image object to be converted to grayscale.
 */
void Filter::applyGrayScale(Image& img) {
    ::applyGrayscale(img);
}

/**
 * @brief Adjusts the brightness of an image.
 *
 * Increases or decreases the brightness of an image based on the specified brightness parameter.
 * Positive values increase brightness, while negative values decrease it.
 *
 * @param img The image object whose brightness is to be adjusted.
 * @param brightness The amount to adjust the brightness by.
 */
void Filter::applyBrightnessDullness(Image& img, int brightness) {
    ::applyBrightnessDullness(img, brightness);
}

/**
 * @brief Applies histogram equalization on a grayscale image.
 *
 * This function enhances the contrast of a grayscale image by spreading out the most frequent
 * intensity values, or by equalizing the histogram of the image.
 *
 * @param img The grayscale image to be equalized.
 */
void Filter::applyGrayscaleEqualization(Image& img) {
    ::applyGrayscaleEqualization(img);
}

/**
 * @brief Applies histogram equalization on an image in RGB, HSV, or HSL color space.
 *
 * These functions convert the image to the specified color space (HSV or HSL), perform histogram
 * equalization on the V/L channel (for brightness or lightness), and then convert the image back
 * to RGB color space, enhancing the overall contrast.
 *
 * @param img The image to be equalized in HSV or HSL color space.
 */
void Filter::applyRGB_HSVEqualization(Image& img) {
    ::applyRGB_HSVEqualization(img);
}

/**
 * @brief Applies histogram equalization on an image in RGB, HSV, or HSL color space.
 *
 * These functions convert the image to the specified color space (HSV or HSL), perform histogram
 * equalization on the V/L channel (for brightness or lightness), and then convert the image back
 * to RGB color space, enhancing the overall contrast.
 *
 * @param img The image to be equalized in HSV or HSL color space.
 */
void Filter::applyRGB_HSLEqualization(Image& img) {
    ::applyRGB_HSLEqualization(img);
}

/**
 * @brief Applies a threshold operation to an image.
 *
 * Converts the image to a binary image, where pixels that meet the threshold criteria are set
 * to one value (usually white), and all other pixels are set to another value (usually black).
 *
 * @param img The image object to be thresholded.
 * @param L_or_V_or_G Specifies the channel (Luminance, Value, or Grayscale) to be used for thresholding.
 * @param threshold The threshold value.
 */
void Filter::applyThreshold(Image &img, char L_or_V_or_G, float threshold) {
    ::applyThreshold(img, L_or_V_or_G, threshold);
}

/**
 * @brief Adds salt-and-pepper noise to an image.
 *
 * Randomly changes a percentage of pixels in the image to black (pepper) or white (salt),
 * simulating a common type of noise seen in digital images.
 *
 * @param img The image object to add noise to.
 * @param percentage The percentage of the image pixels that will be affected by noise.
 */
void Filter::applySaltPepperNoise(Image &img, int percentage) {
    ::applySaltPepperNoise(img, percentage);
}

// 3D blur functions
/**
 * @brief Applies a 3D Gaussian blur to volumetric data.
 *
 * This function uses a Gaussian kernel to smooth 3D data, effectively reducing noise and
 * details in volumetric images. The blur intensity is controlled by the kernel size and the
 * standard deviation (sigma) of the Gaussian distribution.
 *
 * @param volume The 3D volume data to be blurred.
 * @param size The size of the Gaussian kernel (cubic).
 * @param sigma The standard deviation of the Gaussian distribution.
 */
void Filter::apply3DGaussianBlur(Volume &volume, int size, double sigma) {
    std::vector<std::vector<std::vector<double>>> kernel = ::generate3DGaussianKernel(size, sigma);
    ::apply3DGaussianBlur(volume, kernel);
}

/**
 * @brief Applies a 3D median filter to volumetric data.
 *
 * Filters the volume data by replacing each voxel with the median value from a cubic neighborhood
 * defined by the kernel size. This method is effective in reducing noise while preserving edges
 * in the volumetric data.
 *
 * @param volume The 3D volume data to be filtered.
 * @param size The size of the cubic kernel used for filtering.
 */
void Filter::apply3DMedianFilter(Volume &volume, int size) {
    ::apply3DMedianFilter(volume, size);
}


