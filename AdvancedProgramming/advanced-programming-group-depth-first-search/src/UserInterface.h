// Group Name: Depth First Search
// Group Members:
// - Alex Njeumi(Acse-ann23)
// - Yixiao Jing(acse-yj823)
// - Andrei Danila(edsml-acd23)
// - Fan Huang(acse-fh223)
// - Shrreya Behll(edsml-sb3323)
// - Wenxin Zhang(acse-wz2723)
#ifndef USER_INTERFACE_H
#define USER_INTERFACE_H

#include "Image.h"
#include "Volume.h"

/**
 * @class UserInterface
 * @brief Facilitates user interactions for image and volume processing tasks.
 *
 * This class provides a command-line interface for applying a range of image processing techniques to 2D images
 * and 3D volumes. It abstracts the complexities of the underlying operations, presenting the user with a set of
 * clear options for loading, processing, and saving images and volumes. The class is structured around static
 * methods, reflecting its role as a utility rather than an entity to be instantiated.
 *
 * ## Key Functionalities:
 * - Image processing: Allows the user to apply edge detection, blurring, color correction, and smoothing to 2D images.
 * - Volume processing: Enables the user to apply projections, slicing, and blurring to 3D volumetric data.
 * - Loading and saving: Provides mechanisms for loading images and volumes from user-specified paths and saving the processed outputs.
 *
 * The user interface is designed to be extensible, with the potential to add more processing functions as needed.
 */
class UserInterface {
public:
    static void imageProcessing();

private:
    // 2D functions
    static void twoD();
    static void applyEdgeDetection(std::unique_ptr<Image> &grayImage);
    static void applyImageBlur(std::unique_ptr<Image> &Image);
    static void applyColorCorrection(std::unique_ptr<Image> &Image);
    static std::unique_ptr<Image> loadImageFromUserInput();
    static void saveOutput(std::unique_ptr<Image> &img);
    static void applySmoothing(std::unique_ptr<Image> &image);

    // 3D functions
    static void threeD();
    static void applyProjection(std::unique_ptr<Volume> &volume);
    static void applySlice(std::unique_ptr<Volume> &volume);
    static void applyVolumeBlur(std::unique_ptr<Volume> &volume);
    static std::unique_ptr<Volume> loadVolumeFilter();
    static std::unique_ptr<Volume> loadVolumeSlice();
};

#endif
