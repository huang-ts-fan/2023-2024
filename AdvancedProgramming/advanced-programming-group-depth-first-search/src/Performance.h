// Group Name: Depth First Search
// Group Members:
// - Alex Njeumi(Acse-ann23)
// - Yixiao Jing(acse-yj823)
// - Andrei Danila(edsml-acd23)
// - Fan Huang(acse-fh223)
// - Shrreya Behll(edsml-sb3323)
// - Wenxin Zhang(acse-wz2723)
#ifndef PERFORMANCE_H
#define PERFORMANCE_H
#include "Image.h"
#include <chrono>
#include <vector>
#include "2D/colour_correction/colour_correction.h"

class Performance {
public:
    // Constructor
    Performance();

    // Destructor
    ~Performance();

    // Method to measure the performance of applyGrayscale function
    static void measureGrayscalePerformance(const std::vector<Image> &images);
    static void measureSaltPepperNoisePerformance(const std::vector<Image>& images, int percentage);
    static void measureRobertsCrossEdgeDetectionPerformance(const std::vector<Image>& images);
    static void measureBoxBlurPerformance(const std::vector<Image>& images, int blurSize);
    static void measureMIPPerformance(int width, int height, const std::vector<std::vector<unsigned char>>& baseSlice, const std::string& outputFilenamePrefix);
    static void measureMinIPPerformance(int width, int height, const std::vector<std::vector<unsigned char>>& baseSlice, const std::string& outputFilenamePrefix);
    static void measureAIPPerformance(int width, int height, const std::vector<std::vector<unsigned char>>& baseSlice, const std::string& outputFilenamePrefix);
    bool loadFromDirectory_time(const std::string& directoryPath, int startIndex, int finalIndex);
};

#endif // PERFORMANCE_H