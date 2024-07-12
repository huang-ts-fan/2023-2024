// Group Name: Depth First Search
// Group Members:
// - Alex Njeumi(Acse-ann23)
// - Yixiao Jing(acse-yj823)
// - Andrei Danila(edsml-acd23)
// - Fan Huang(acse-fh223)
// - Shrreya Behll(edsml-sb3323)
// - Wenxin Zhang(acse-wz2723)
#ifndef FILTER_H
#define FILTER_H

#include "2D/edge_detection/edge_detection.h"
#include "2D/image_blur/image_blur.h"
#include "2D/colour_correction/colour_correction.h"
#include "3D/threeD_image_blur.h"

/**
 * @class Filter
 * @brief A collection of static methods for applying various image processing techniques.
 *
 * The Filter class offers a suite of static methods for performing operations related to color correction,
 * blurring, and edge detection on both 2D images and 3D volume data. This class acts as a centralized
 * framework to facilitate easy application of complex image processing techniques. It is designed to be
 * modular and easily extensible for integrating additional image processing functions in the future.
 *
 * ## Features:
 * - Colour Correction: Includes methods for grayscale conversion, brightness adjustment, histogram equalization
 *   in various color spaces, and application of thresholding techniques.
 * - 2D Blur Functions: Provides box blur, Gaussian blur, and median blur functionalities to apply on 2D images,
 *   useful for noise reduction and image smoothing.
 * - Edge Detection: Implements edge detection algorithms using operator templates such as Sobel, Prewitt, and
 *   Roberts Cross, essential for feature detection and image analysis.
 * - 3D Blur Functions: Extends blurring techniques to 3D volumetric data, accommodating applications in
 *   medical imaging and scientific visualization.
 *
 * Each method is static, allowing direct invocation on the `Filter` class without needing an instance, simplifying
 * the application of multiple filters on the same image or volume data.
 */
class Filter {
public:
    // Colour correction functions
    static void applyGrayScale(Image& img);
    static void applyBrightnessDullness(Image& img, int brightness);
    static void applyGrayscaleEqualization(Image& img);
    static void applyRGB_HSVEqualization(Image& img);
    static void applyRGB_HSLEqualization(Image& img);
    static void applyThreshold(Image& img, char L_or_V_or_G, float threshold);
    static void applySaltPepperNoise(Image& img, int percentage);

    // 2D Blur functions
    static void applyBoxBlur(Image& img, int blurSize);
    static void applyGaussianBlur(Image& img, double sigma, int kernelSize);
    static void applyMedianBlur(Image& img, int kernelSize);

    // Edge detection functions
    static void applyEdgeDetection(Image& img, const float operatorX[3][3], const float operatorY[3][3]);
    static void applyRobertsCrossEdgeDetection(Image& img);

    // 3D Blur functions
    static void apply3DGaussianBlur(Volume &volume, int size, double sigma = 2.0);
    static void apply3DMedianFilter(Volume &volume, int size);
};

#endif // FILTER_H
