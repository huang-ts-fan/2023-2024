// Group Name: Depth First Search
// Group Members:
// - Alex Njeumi(Acse-ann23)
// - Yixiao Jing(acse-yj823)
// - Andrei Danila(edsml-acd23)
// - Fan Huang(acse-fh223)
// - Shrreya Behll(edsml-sb3323)
// - Wenxin Zhang(acse-wz2723)
#include "UserInterface.h"
#include "Filter.h"
#include "Image.h"
#include "Projection.h"
#include "Volume.h"
#include "Slice.h"

#include <iostream>
#include <string>

/**
 * @brief Entry point for the image processing interface.
 *
 * Prompts the user to choose between 2D and 3D data processing, directing them to the appropriate
 * interface based on their choice.
 */
void UserInterface::imageProcessing() {
    std::cout << "Welcome to the Depth-First-Search image processing software!" << std::endl;
    std::cout << "What kind of data would you like to process?" << std::endl;
    std::cout << "1. Two Dimensional (2D)" << std::endl;
    std::cout << "2. Three Dimensional (3D)" << std::endl;
    std::cout << "Your choice: ";
    int choice;
    while (true) {
        std::cin >> choice;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cerr << "Invalid input. Please enter an integer.\n";
            continue;
        }
        if (choice == 1) {
            twoD();
            break;
        } else if (choice == 2) {
            threeD();
            break;
        } else {
            std::cerr << "Invalid choice. Try again.\n";
        }
    }
}

/**
 * @brief Interface for processing 2D images.
 *
 * Offers the user a choice of filters to apply to a 2D image, including colour correction, image blur,
 * and edge detection. It then loads an image based on user input, applies the selected filter, and saves
 * the output.
 */
void UserInterface::twoD() {
    std::unique_ptr<Image> img = loadImageFromUserInput();
    std::unique_ptr<Image> grayImage = std::make_unique<Image>(Image::convertToGrayscale(*img));
    std::cout << "What kind of filter do you want to apply?" << std::endl;
    std::cout << "1. Colour correction" << std::endl;
    std::cout << "2. Image blur" << std::endl;
    std::cout << "3. Edge detection" << std::endl;
    int choice2D;
    std::cout << "Your choice: ";
    while(true) {
        std::cin >> choice2D;
        if(std::cin.fail() || choice2D < 1 || choice2D > 3) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cerr << "Invalid input. Please select a valid option: ";
        } else {
            break;
        }
    }
    switch (choice2D) {
        case 1:
            applyColorCorrection(img);
            break;
        case 2:
            applyImageBlur(img);
            break;
        case 3:
            applyEdgeDetection(grayImage);
            break;
        default:
            std::cout << "Invalid choice. Please rerun program to try again." << std::endl;
    }
}

/**
 * @brief Applies edge detection to a grayscale image.
 *
 * Prompts the user to select a specific type of edge detection algorithm, applies the chosen algorithm
 * to the image, and saves the output.
 */
void UserInterface::applyEdgeDetection(std::unique_ptr<Image>& grayImage) {
    std::cout << "What kind of edge detection would you like to apply?" << std::endl;
    std::cout << "1. Sobel" << std::endl;
    std::cout << "2. Prewitt" << std::endl;
    std::cout << "3. Scharr" << std::endl;
    std::cout << "4. Roberts" << std::endl;
    int choiceEdge;
    std::cout << "Your choice: ";
    while(true) {
        std::cin >> choiceEdge;
        if(std::cin.fail() || choiceEdge < 1 || choiceEdge > 4) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cerr << "Invalid input. Please select a valid option: ";
        } else {
            break;
        }
    }
    switch (choiceEdge) {
        case 1: {
            float sobelX[3][3] = {{-1, 0, 1},
                                  {-2, 0, 2},
                                  {-1, 0, 1}};
            float sobelY[3][3] = {{-1, -2, -1},
                                  {0,  0,  0},
                                  {1,  2,  1}};
            applySmoothing(grayImage);
            Filter::applyEdgeDetection(*grayImage, sobelX, sobelY);
            break;
        }
        case 2: {
            float prewittX[3][3] = {{-1, 0, 1},
                                    {-1, 0, 1},
                                    {-1, 0, 1}};
            float prewittY[3][3] = {{-1, -1, -1},
                                    {0,  0,  0},
                                    {1,  1,  1}};
            applySmoothing(grayImage);
            Filter::applyEdgeDetection(*grayImage, prewittX, prewittY);
            break;
        }
        case 3: {
            float scharrX[3][3] = {{-3,  0, 3},
                                   {-10, 0, 10},
                                   {-3,  0, 3}};
            float scharrY[3][3] = {{-3, -10, -3},
                                   {0,  0,   0},
                                   {3,  10,  3}};
            applySmoothing(grayImage);
            Filter::applyEdgeDetection(*grayImage, scharrX, scharrY);
            break;
        }
        case 4: {
            applySmoothing(grayImage);
            Filter::applyRobertsCrossEdgeDetection(*grayImage);
            break;
        }
    }
    saveOutput(grayImage);
};

/**
 * @brief Applies blurring to an image.
 *
 * Allows the user to select a type of blur to apply to the image, executes the selected blur operation,
 * and saves the result.
 */
void UserInterface::applyImageBlur(std::unique_ptr<Image>& img) {
    std::cout << "What kind of image blur would you like to apply?" << std::endl;
    std::cout << "1. Median blur" << std::endl;
    std::cout << "2. Box blur" << std::endl;
    std::cout << "3. Gaussian blur" << std::endl;
    int choiceBlur;
    std::cout << "Your choice: ";
    while(true) {
        std::cin >> choiceBlur;
        if(std::cin.fail() || choiceBlur < 1 || choiceBlur > 3) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cerr << "Invalid input. Please select a valid option: ";
        } else {
            break;
        }
    }
    switch(choiceBlur) {
        case 1: {
            Filter::applyMedianBlur(*img, 5);
            break;
        }
        case 2: {
            Filter::applyBoxBlur(*img, 4);
            break;
        }
        case 3: {
            Filter::applyGaussianBlur(*img, 2.0, 3);
            break;
        }
    }
    saveOutput(img);
}

/**
 * @brief Applies color correction to an image.
 *
 * Offers various color correction options to the user, applies the selected correction to the image,
 * and saves the modified image.
 */
void UserInterface::applyColorCorrection(std::unique_ptr<Image>& img) {
    std::cout << "What kind of colour correction would you like to apply?" << std::endl;
    std::cout << "1. Grayscale" << std::endl;
    std::cout << "2. Brightness/Dullness" << std::endl;
    std::cout << "3. Grayscale Equalization" << std::endl;
    std::cout << "4. RGB to HSV Equalization" << std::endl;
    std::cout << "5. RGB to HSL Equalization" << std::endl;
    std::cout << "6. Threshold" << std::endl;
    std::cout << "7. SaltPepperNoise" << std::endl;
    int choiceColour;
    std::cout << "Your choice: ";
    while(true) {
        std::cin >> choiceColour;
        if(std::cin.fail() || choiceColour < 1 || choiceColour > 7) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cerr << "Invalid input. Please select a valid option: ";
        } else {
            break;
        }
    }
    switch(choiceColour){
        case 1:
            Filter::applyGrayScale(*img);
            break;
        case 2:
            int brightness;
            std::cout << "Please choose brightness/dullness value: ";
            std::cin >> brightness;
            Filter::applyBrightnessDullness(*img, brightness);
            break;
        case 3:
            Filter::applyGrayscaleEqualization(*img);
            break;
        case 4:
            Filter::applyRGB_HSVEqualization(*img);
            break;
        case 5:
            Filter::applyRGB_HSLEqualization(*img);
            break;
        case 6:
            float threshold;
            char L_or_V_or_G;
            std::cout << "Please choose channel to threshold (L, V or G): ";
            std::cin >> L_or_V_or_G;
            std::cout << "Please choose threshold value: ";
            std::cin >> threshold;
            Filter::applyThreshold(*img, L_or_V_or_G, threshold);
            break;
        case 7:
            int percentage;
            std::cout << "Please choose percentage of salt and pepper noise: ";
            std::cin >> percentage;
            Filter::applySaltPepperNoise(*img, percentage);
            break;
    }
    saveOutput(img);
}

/**
 * @brief Loads an image based on user input.
 *
 * Prompts the user to enter the path to an image file, attempts to load the image, and returns a pointer
 * to the loaded image object.
 *
 * @return A unique_ptr to an Image object containing the loaded image.
 */
std::unique_ptr<Image> UserInterface::loadImageFromUserInput() {
    std::string filename;
    std::unique_ptr<Image> img = nullptr;
    std::cout << "Please enter path to image: ";
    while (true) {
        std::cin >> filename;
        img = std::make_unique<Image>(filename);
        if (img->getWidth() == 0 || img->getHeight() == 0) {
            std::cerr << "Failed to load image. Please enter a new image name: ";
        } else {
            std::cout << "Image loaded successfully." << std::endl;
            break;
        }
    }
    return img;
}

/**
 * @brief Saves a processed image to a user-specified path.
 *
 * Asks the user for a file path and attempts to save the processed image to this location.
 */
void UserInterface::saveOutput(std::unique_ptr<Image>& image){
    while(true) {
        std::cout << "Please enter path to save your output - do not include quotation marks: ";
        std::string outputPath;
        std::cin >> outputPath;
        bool saveSuccessful = image->saveImage(outputPath);

        if(saveSuccessful) {
            std::cout << "Image saved successfully." << std::endl;
            break;
        } else {
            std::cerr << "Failed to save image. Please try a different path." << std::endl;
        }
    }
}

/**
 * @brief Optionally applies smoothing to an image.
 *
 * Asks the user if they would like to apply smoothing to their image before proceeding with other
 * operations, and if so, applies the selected type of smoothing.
 */
void UserInterface::applySmoothing(std::unique_ptr<Image>& image){
    std::string choice;
    std::cout << "Would you like to apply smoothing to your image? Enter yes or no: ";
    while(true) {
        std::cin >> choice;
        std::transform(choice.begin(), choice.end(), choice.begin(), ::tolower);

        if(choice == "yes" || choice == "no") {
            break;
        } else {
            std::cerr << "Invalid input. Please enter 'yes' or 'no': ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
    if(choice == "yes"){
        std::cout << "What kind of smoothing would you like to apply?" << std::endl;
        std::cout << "1. Median blur" << std::endl;
        std::cout << "2. Box blur" << std::endl;
        std::cout << "3. Gaussian blur" << std::endl;
        int choiceBlur;
        std::cout << "Your choice: ";
        while(true) {
            std::cin >> choiceBlur;
            if(std::cin.fail() || choiceBlur < 1 || choiceBlur > 3) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cerr << "Invalid input. Please select a valid option: ";
            } else {
                break;
            }
        }
        switch(choiceBlur) {
            case 1: {
                Filter::applyMedianBlur(*image, 5);
                break;
            }
            case 2: {
                Filter::applyBoxBlur(*image, 4);
                break;
            }
            case 3: {
                Filter::applyGaussianBlur(*image, 2.0, 3);
                break;
            }
        }
    }
}

/**
 * @brief Interface for processing 3D volumetric data.
 *
 * Prompts the user to choose a type of operation to apply to 3D data, including projections, slicing,
 * and blurring. It then loads a volume, applies the chosen operation, and optionally saves the output.
 */
void UserInterface::threeD() {
    std::cout << "Please choose an operation to perform (data will be loaded after operation choice): " << std::endl;
    std::cout << "1. Apply Projection" << std::endl;
    std::cout << "2. Apply Slice" << std::endl;
    std::cout << "3. Apply Blur" << std::endl;
    std::cout << "Your choice: ";

    int choice;
    std::cin >> choice;

    while (true) {
        if (std::cin.fail() || (choice != 1 && choice != 2 && choice != 3)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discards the input buffer
            std::cerr << "Invalid choice. Please select 1 for Projection or 2 for Slice: ";
            std::cin >> choice;
        } else {
            break;
        }
    }

    switch (choice) {
        case 1: {
            std::unique_ptr<Volume> volume = loadVolumeFilter();
            applyProjection(volume);
            break;
        }
        case 2: {
            std::unique_ptr<Volume> volume = loadVolumeSlice();
            applySlice(volume);
            break;
        }
        case 3: {
            std::unique_ptr<Volume> volume = loadVolumeFilter();
            applyVolumeBlur(volume);
            std::string outputPath;
            std::cout << "Insert path to save the volume. Needs to be a directory: ";
            std::cin >> outputPath;
            volume->saveVolume(outputPath);
            break;
        }
        default:
            std::cerr << "Invalid choice. Please select a valid option." << std::endl;
            break;
    }
}

/**
 * @brief Applies a projection to volumetric data.
 *
 * Allows the user to choose a type of intensity projection to apply to a volume, applies the selected
 * projection, and saves the result to a specified file.
 */
void UserInterface::applyProjection(std::unique_ptr<Volume>& volume) {
    std::cout << "Which type of projection would you like to apply?" << std::endl;
    std::cout << "1. Maximum Intensity Projection (MIP)" << std::endl;
    std::cout << "2. Minimum Intensity Projection (MinIP)" << std::endl;
    std::cout << "3. Average Intensity Projection (AIP)" << std::endl;
    int choiceProjection;
    std::cout << "Your choice: ";
    while(true) {
        std::cin >> choiceProjection;
        if(std::cin.fail() || choiceProjection < 1 || choiceProjection > 3) {
            std::cin.clear(); // Clears the error flag on cin
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discards the input buffer
            std::cerr << "Invalid input. Please select a valid option: ";
        } else {
            break; // Exit the loop if input is valid
        }
    }
    std::string outputFilename;
    std::cout << "Enter output file name (including path): ";
    std::cin >> outputFilename;
    std::string blurChoice;
    std::cout << "Would you like to apply a blur before projecting (yes/no)? ";
    while(true) {
        std::cin >> blurChoice;
        if (blurChoice == "yes") {
            applyVolumeBlur(volume);
            break;
        }
        else if(blurChoice != "no")
            std::cerr << "Invalid choice. Enter yes or no: ";
    }
    std::vector<unsigned char*> filteredVolumeData = volume->convertToCharPointers();
    switch(choiceProjection) {
        case 1: {
            // Maximum Intensity Projection
            Projection::generateMIP(outputFilename, volume->getWidth(), volume->getHeight(), volume->getDepth(), filteredVolumeData);
            break;
        }
        case 2: {
            // Minimum Intensity Projection
            Projection::generateMinIP(outputFilename, volume->getWidth(), volume->getHeight(), volume->getDepth(), filteredVolumeData);
            break;
        }
        case 3: {
            // Average Intensity Projection
            Projection::generateAIP(outputFilename, volume->getWidth(), volume->getHeight(), volume->getDepth(), filteredVolumeData);
            break;
        }
    }
    std::cout << "Projection applied and saved to: " << outputFilename << std::endl;
}

/**
 * @brief Extracts and saves a slice from volumetric data.
 *
 * Prompts the user for slicing parameters, including the axis and index of the slice, and saves the
 * extracted slice to a specified file.
 */
void UserInterface::applySlice(std::unique_ptr<Volume>& volume) {
    std::string axis;
    int index;
    std::string filename;

    std::cout << "Please enter the axis for the slice (X, Y, or Z): ";
    std::cin >> axis;
    while (axis != "X" && axis != "Y" && axis != "Z") {
        std::cerr << "Invalid axis. Please enter X, Y, or Z: ";
        std::cin >> axis;
    }

    std::cout << "Please enter the index for the slice: ";
    std::cin >> index;
    // Validate index based on the chosen axis
    int maxIndex = (axis == "X") ? volume->getWidth() : (axis == "Y") ? volume->getHeight() : volume->getDepth();
    while (std::cin.fail() || index < 0 || index >= maxIndex) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cerr << "Invalid index. Please enter a non-negative integer less than " << maxIndex << ": ";
        std::cin >> index;
    }

    std::cout << "Please enter the filename to save the slice: ";
    std::cin >> filename;

    //std::vector<unsigned char*> filteredVolumeData = volume->convertToCharPointers();
    Slice slice(nullptr, volume->getWidth(), volume->getHeight()); // Temporarily passing nullptr for data
    slice.saveSlice(axis, index, filename, volume->getDepth(), volume->getSlices());

    std::cout << "Slice saved to " << filename << std::endl;
}

/**
 * @brief Applies blurring to volumetric data.
 *
 * Offers the user a choice of blur types to apply to a volume, executes the selected blur operation,
 * and optionally saves the blurred volume to a specified directory.
 */
void UserInterface::applyVolumeBlur(std::unique_ptr<Volume> &volume) {
    std::cout << "Which type of blur would you like to apply?" << std::endl;
    std::cout << "1. Median Blur" << std::endl;
    std::cout << "2. Gaussian blur" << std::endl;
    int choiceBlur;
    std::cout << "Your choice: ";
    while(true) {
        std::cin >> choiceBlur;
        if(std::cin.fail() || choiceBlur < 1 || choiceBlur > 2) {
            std::cin.clear(); // Clears the error flag on cin
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discards the input buffer
            std::cerr << "Invalid input. Please select a valid option: ";
        } else {
            break; // Exit the loop if input is valid
        }
    }
    int kernel_size;
    std::cout << "Enter kernel size: ";
    std::cin >> kernel_size;
    switch(choiceBlur) {
        case 1: {
            Filter::apply3DMedianFilter(*volume, kernel_size);
            break;
        }
        case 2: {
            Filter::apply3DGaussianBlur(*volume, kernel_size);
            break;
        }
    }
}

/**
 * @brief Loads volumetric data from a directory.
 *
 * These functions prompt the user for a directory path and parameters for loading volume data, then
 * load the volume accordingly. `loadVolumeFilter` additionally implies some form of filtering may be
 * applied during loading, whereas `loadVolumeSlice` suggests slicing operations might be the focus.
 *
 * @return A unique_ptr to a Volume object containing the loaded volumetric data.
 */
std::unique_ptr<Volume> UserInterface::loadVolumeFilter() {
    std::string directoryPath;
    std::unique_ptr<Volume> volume = nullptr;
    int startNum, numImages;

    std::cout << "Please enter path to volume directory: ";
    std::cin >> directoryPath;

    std::cout << "Enter start number for images: ";
    std::cin >> startNum;
    while(std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input for start number. Please enter a numeric value: ";
        std::cin >> startNum;
    }

    std::cout << "Enter number of images: ";
    std::cin >> numImages;
    while(std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input for number of images. Please enter a numeric value: ";
        std::cin >> numImages;
    }

    while (true) {
        volume = std::make_unique<Volume>();
        if (!volume->loadFromDirectory_filter(directoryPath, startNum, numImages)) {
            std::cerr << "Failed to load volume. Please enter a new directory path: ";
            std::cin >> directoryPath;
        } else {
            std::cout << "Volume loaded successfully." << std::endl;
            break;
        }
    }
    return volume;
}

/**
 * @brief Loads volumetric data from a directory.
 *
 * These functions prompt the user for a directory path and parameters for loading volume data, then
 * load the volume accordingly. `loadVolumeFilter` additionally implies some form of filtering may be
 * applied during loading, whereas `loadVolumeSlice` suggests slicing operations might be the focus.
 *
 * @return A unique_ptr to a Volume object containing the loaded volumetric data.
 */
std::unique_ptr<Volume> UserInterface::loadVolumeSlice() {
    std::string directoryPath;
    std::unique_ptr<Volume> volume = nullptr;
    int startNum, numImages;

    std::cout << "Please enter path to volume directory: ";
    std::cin >> directoryPath;

    std::cout << "Enter start number for images: ";
    std::cin >> startNum;
    while(std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input for start number. Please enter a numeric value: ";
        std::cin >> startNum;
    }

    std::cout << "Enter number of images: ";
    std::cin >> numImages;
    while(std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input for number of images. Please enter a numeric value: ";
        std::cin >> numImages;
    }

    while (true) {
        volume = std::make_unique<Volume>();
        if (!volume->loadFromDirectory(directoryPath, startNum, numImages)) {
            std::cerr << "Failed to load volume. Please enter a new directory path: ";
            std::cin >> directoryPath;
        } else {
            std::cout << "Volume loaded successfully." << std::endl;
            break;
        }
    }
    return volume;
}