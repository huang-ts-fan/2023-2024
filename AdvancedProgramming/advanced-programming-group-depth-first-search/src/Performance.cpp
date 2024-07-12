// Group Name: Depth First Search
// Group Members:
// - Alex Njeumi(Acse-ann23)
// - Yixiao Jing(acse-yj823)
// - Andrei Danila(edsml-acd23)
// - Fan Huang(acse-fh223)
// - Shrreya Behll(edsml-sb3323)
// - Wenxin Zhang(acse-wz2723)
#include "Performance.h"
#include <iostream>
#include "2D/colour_correction/colour_correction.h"
#include "Image.h"
#include <chrono>
#include "2D/edge_detection/edge_detection.h"
#include "2D/image_blur/image_blur.h"
#include "Projection.h"
#include <filesystem>
#include "string"
#include <vector>
#include "Filter.h"
#include "Projection.h"
#include "Volume.h"


namespace fs = std::__fs::filesystem;

// Default constructor for the Performance class
Performance::Performance() {}

// Destructor for the Performance class
Performance::~Performance() {}

/**
 * @brief Measures the performance of grayscale transformation on a set of images.
 * @param images A vector of Image objects on which the grayscale transformation is applied.
 */
void Performance::measureGrayscalePerformance(const std::vector<Image>& images) {
    for (const auto& img : images) {
        auto start = std::chrono::high_resolution_clock::now();

        Image tempImg = img; // Create a temporary copy to work on
        applyGrayscale(tempImg); // Apply the grayscale transformation

        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> duration = end - start;

        std::cout << "Image Size: " << img.getWidth() << "x" << img.getHeight()
                  << " - Time taken: " << duration.count() << " ms\n";
    }
}

/**
 * @brief Measures the performance of applying salt and pepper noise on a set of images.
 * @param images A vector of Image objects on which the noise is applied.
 * @param percentage The percentage of noise to be applied.
 */
void Performance::measureSaltPepperNoisePerformance(const std::vector<Image>& images, int percentage) {
    std::cout << "Measuring Salt and Pepper Noise Performance\n";
    for (const auto& img : images) {
        Image tempImg = img; // Create a copy of the image to apply noise

        auto start = std::chrono::high_resolution_clock::now();

        // Replace the call to a hypothetical global function with the actual implementation
        // If applySaltPepperNoise is not a member of Image, you'll need to adjust this accordingly
        applySaltPepperNoise(tempImg, percentage); // This line assumes applySaltPepperNoise can be directly called

        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> duration = end - start;

        std::cout << "Image Size: " << img.getWidth() << "x" << img.getHeight()
                  << ", Noise: " << percentage << "% - Time taken: " << duration.count() << " ms\n";
    }
}

/**
 * @brief Measures the performance of Roberts Cross Edge Detection on a set of images.
 * @param images A vector of Image objects on which the edge detection is applied.
 */
void Performance::measureRobertsCrossEdgeDetectionPerformance(const std::vector<Image>& images) {
    std::cout << "Measuring Roberts Cross Edge Detection Performance\n";
    for (const auto& img : images) {
        Image tempImg = img; // Create a copy of the image to apply edge detection

        auto start = std::chrono::high_resolution_clock::now();

        // Replace this with a call to the actual implementation
        applyRobertsCrossEdgeDetection(tempImg);

        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> duration = end - start;

        std::cout << "Image Size: " << img.getWidth() << "x" << img.getHeight()
                  << " - Time taken: " << duration.count() << " ms\n";
    }
}

/**
 * @brief Measures the performance of box blur on a set of images.
 * @param images A vector of Image objects on which the blur is applied.
 * @param blurSize The size of the blur to be applied.
 */
void Performance::measureBoxBlurPerformance(const std::vector<Image>& images, int blurSize) {
    std::cout << "Measuring Box Blur Performance\n";
    for (const auto& img : images) {
        Image tempImg = img; // Create a copy to work on without modifying the original

        auto start = std::chrono::high_resolution_clock::now();

        // Apply box blur
        applyBoxBlur(tempImg, blurSize);

        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> duration = end - start;

        std::cout << "Image Size: " << img.getWidth() << "x" << img.getHeight()
                  << ", Blur Size: " << blurSize
                  << " - Time taken: " << duration.count() << " ms\n";
    }
}

/**
 * @brief Measures the performance of Maximum Intensity Projection (MIP) on a set of volume slices.
 * @param width The width of the volume.
 * @param height The height of the volume.
 * @param baseSlice A 2D vector representing the base slice of the volume.
 * @param outputFilenamePrefix The prefix of the output file name.
 */
static void measureMIPPerformance(int width, int height, const std::vector<std::vector<unsigned char>>& baseSlice, const std::string& outputFilenamePrefix) {
    // Depths to test, for example: 10, 20, 40, 80, 160
    std::vector<int> depths = {10, 20, 40, 80, 160};

    for (int depth : depths) {
        // Simulate volume slices based on depth
        std::vector<unsigned char*> slices;
        for (int z = 0; z < depth; ++z) {
            // This example assumes each slice is a flattened array of pixels in the volume
            // Real implementation might differ based on how your data is structured
            slices.push_back(new unsigned char[width * height]);
            // Fill slice data. In a real scenario, you'd copy data from an actual slice
            std::fill_n(slices.back(), width * height, z); // Simple example: fill with z to simulate variation
        }

        // Measure MIP generation performance
        auto startTime = std::chrono::high_resolution_clock::now();

        std::string filename = outputFilenamePrefix + "_depth_" + std::to_string(depth) + ".png";
        Projection::generateMIP(filename, width, height, depth, slices);

        auto endTime = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> elapsed = endTime - startTime;

        std::cout << "Depth: " << depth << ", Time: " << elapsed.count() << " ms\n";

        // Cleanup allocated memory for slices
        for (auto* slice : slices) {
            delete[] slice;
        }
    }
}

/**
 * @brief Measures the performance of Average Intensity Projection (AIP) on a set of volume slices.
 * @param width The width of the volume.
 * @param height The height of the volume.
 * @param baseSlice A 2D vector representing the base slice of the volume.
 * @param outputFilenamePrefix The prefix of the output file name.
 */
static void measureAIPPerformance(int width, int height, const std::vector<std::vector<unsigned char>>& baseSlice, const std::string& outputFilenamePrefix) {
    // Depths to test, for example: 10, 20, 40, 80, 160
    std::vector<int> depths = {10, 20, 40, 80, 160};

    for (int depth : depths) {
        // Simulate volume slices based on depth
        std::vector<unsigned char*> slices;
        for (int z = 0; z < depth; ++z) {
            // This example assumes each slice is a flattened array of pixels in the volume
            slices.push_back(new unsigned char[width * height]);
            // Fill slice data. In a real scenario, you'd copy data from an actual slice
            std::fill_n(slices.back(), width * height, z); // Simple example: fill with z to simulate variation
        }

        // Measure AIP generation performance
        auto startTime = std::chrono::high_resolution_clock::now();

        std::string filename = outputFilenamePrefix + "_depth_" + std::to_string(depth) + ".png";
        Projection::generateAIP(filename, width, height, depth, slices);

        auto endTime = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> elapsed = endTime - startTime;

        std::cout << "Depth: " << depth << ", Time for AIP: " << elapsed.count() << " ms\n";

        // Cleanup allocated memory for slices
        for (auto* slice : slices) {
            delete[] slice;
        }
    }
}

/**
 * @brief Measures the performance of Minimum Intensity Projection (MinIP) on a set of volume slices.
 * @param width The width of the volume.
 * @param height The height of the volume.
 * @param baseSlice A 2D vector representing the base slice of the volume.
 * @param outputFilenamePrefix The prefix of the output file name.
 */
static void measureMinIPPerformance(int width, int height, const std::vector<std::vector<unsigned char>>& baseSlice, const std::string& outputFilenamePrefix) {
    // Depths to test, for example: 10, 20, 40, 80, 160
    std::vector<int> depths = {10, 20, 40, 80, 160};

    for (int depth : depths) {
        // Simulate volume slices based on depth
        std::vector<unsigned char*> slices;
        for (int z = 0; z < depth; ++z) {
            // This example assumes each slice is a flattened array of pixels in the volume
            slices.push_back(new unsigned char[width * height]);
            // In a real scenario, you'd copy data from an actual slice. Here, fill with z for simplicity
            std::fill_n(slices.back(), width * height, z); // Simple example to simulate variation
        }

        // Measure MinIP generation performance
        auto startTime = std::chrono::high_resolution_clock::now();

        std::string filename = outputFilenamePrefix + "_depth_" + std::to_string(depth) + ".png";
        Projection::generateMinIP(filename, width, height, depth, slices);

        auto endTime = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> elapsed = endTime - startTime;

        std::cout << "Depth: " << depth << ", Time for MinIP: " << elapsed.count() << " ms\n";

        // Cleanup allocated memory for slices
        for (auto* slice : slices) {
            delete[] slice;
        }
    }
}


int main() {
    // Create a vector to hold images of different sizes
    std::vector<Image> images;

    // Assuming Image class has a way to set width and height
    images.emplace_back(640, 480); // An example image of 640x480 pixels
    images.emplace_back(800, 600); // An example image of 800x600 pixels
    images.emplace_back(1024, 768); // An example image of 1024x768 pixels
    images.emplace_back(1920, 1080); // An example image of 1920x1080 pixels
    std::vector<std::vector<unsigned char*>> volumeSlices;
    // Create a Performance object
    Performance perf;

    // Call the measureGrayscalePerformance function with the vector of images
    std::cout << "Grayscale Performance:\n";
    Performance::measureGrayscalePerformance(images);

    // Call the measureSaltPepperNoisePerformance function with the vector of images
    // Let's say we want to measure performance with 10% noise
    std::cout << "\nSalt and Pepper Noise Performance (10% noise):\n";
    Performance::measureSaltPepperNoisePerformance(images, 10);

    std::cout << "\nRoberts Cross Edge Detection Performance:\n";
    Performance::measureRobertsCrossEdgeDetectionPerformance(images);

    int blurSize = 3;
    std::cout << "\nBox Blur Performance:\n";
    Performance::measureBoxBlurPerformance(images, blurSize);

    int width = 256;
    int height = 256;
    std::vector<std::vector<unsigned char>> baseSlice(height, std::vector<unsigned char>(width, 0)); // Example base slice, filled with zeros

    // The filename prefix for generated MIP images. Each file will have a suffix indicating the depth
    std::string outputFilenamePrefix = "MIP_output";

    // Call the performance measurement function
    std::cout << "\nMIP Performance:\n";
    measureMIPPerformance(width, height, baseSlice, outputFilenamePrefix);

    std::cout << "\nAIP Performance:\n";
    measureAIPPerformance(width, height, baseSlice,outputFilenamePrefix);

    std::cout << "\nMinIp Performance:\n";
    measureMinIPPerformance(width, height, baseSlice, outputFilenamePrefix);

    auto start = std::chrono::high_resolution_clock::now(); 

    Volume volume;

    if (!volume.loadFromDirectory_time("../Scans/confuciusornis", 0, 20)) {
        std::cerr << "Failed to load volume data from directory." << std::endl;
        return 1;
    }

    Filter::apply3DMedianFilter(volume, 3);

    std::vector<unsigned char*> filteredVolumeData = volume.convertToCharPointers();
    std::string mipFilename = "../Output/3D/confuciusornis/mip-median-3x3x3-old.png";
    Projection::generateMIP(mipFilename, volume.getWidth(), volume.getHeight(), volume.getDepth(), filteredVolumeData);

    for (auto& ptr : filteredVolumeData) {
        delete[] ptr;
    }

    auto end = std::chrono::high_resolution_clock::now(); 
    std::chrono::duration<double> elapsed = end - start; 

    std::cout << "Elapsed time: " << elapsed.count() << " seconds." << std::endl; 


    return 0;
}


