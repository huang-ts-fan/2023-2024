// Group Name: Depth First Search
// Group Members:
// - Alex Njeumi(Acse-ann23)
// - Yixiao Jing(acse-yj823)
// - Andrei Danila(edsml-acd23)
// - Fan Huang(acse-fh223)
// - Shrreya Behll(edsml-sb3323)
// - Wenxin Zhang(acse-wz2723)
#include <string>
#include <iostream>
#include <cmath>
#include <vector>

#include "edge_detection.h"

// implement four edge detection algorithms: Sobel, Prewitt, Scharr, and Roberts Cross

/**
 * @brief Applies edge detection on an image using specified X and Y operator templates.
 *
 * This function uses two 3x3 operator templates to detect edges in the image by calculating
 * the gradient magnitude for each pixel. The result is a grayscale image where edges are highlighted.
 *
 * @param img The image on which to apply edge detection.
 * @param operatorX The 3x3 matrix representing the X direction operator.
 * @param operatorY The 3x3 matrix representing the Y direction operator.
 */
 void applyEdgeDetection(Image& img, const float operatorX[3][3], const float operatorY[3][3]) {
    const auto& data = img.getData();
    int width = img.getWidth();
    int height = img.getHeight();
    std::vector<std::vector<std::vector<unsigned char> > > edgeData(height, std::vector<std::vector<unsigned char> >(width, std::vector<unsigned char>(1, 0)));

    for (int y = 1; y < height - 1; ++y) {
        for (int x = 1; x < width - 1; ++x) {
            float pixelX = 0.0f;
            float pixelY = 0.0f;
            for (int dy = -1; dy <= 1; ++dy) {
                for (int dx = -1; dx <= 1; ++dx) {
                    unsigned char pixelVal = data[y + dy][x + dx][0]; // Assuming grayscale
                    pixelX += pixelVal * operatorX[dy + 1][dx + 1];
                    pixelY += pixelVal * operatorY[dy + 1][dx + 1];
                }
            }
            unsigned char edgeVal = static_cast<unsigned char>(std::min(std::sqrt(pixelX * pixelX + pixelY * pixelY), 255.0f));
            edgeData[y][x][0] = edgeVal;
        }
    }

    img.setData(edgeData);
}

/**
 * @brief Applies Roberts Cross edge detection on an image.
 *
 * This function implements the Roberts Cross operator for edge detection, utilizing a 2x2 operator.
 * It calculates the gradient magnitude using the Roberts Cross approximation to the derivative, highlighting
 * the edges in the image as a result. This method is particularly effective for high-contrast edges.
 *
 * @param img The image on which to apply Roberts Cross edge detection.
 */
void applyRobertsCrossEdgeDetection(Image& img) {
    const auto& data = img.getData();
    int width = img.getWidth();
    int height = img.getHeight();
    std::vector<std::vector<std::vector<unsigned char> > > edgeData(height, std::vector<std::vector<unsigned char> >(width, std::vector<unsigned char>(1, 0)));

    // Roberts’ Cross 
    int gx[2][2] = {{1, 0}, {0, -1}};
    int gy[2][2] = {{0, 1}, {-1, 0}};

    for (int y = 0; y < height - 1; ++y) {
        for (int x = 0; x < width - 1; ++x) {
            float pixelX = 0.0f;
            float pixelY = 0.0f;

            // apply the 2x2 operator
            for (int dy = 0; dy < 2; ++dy) {
                for (int dx = 0; dx < 2; ++dx) {
                    unsigned char pixelVal = data[y + dy][x + dx][0]; 
                    pixelX += pixelVal * gx[dy][dx];
                    pixelY += pixelVal * gy[dy][dx];
                }
            }

            // calculate the gradient magnitude
            unsigned char edgeVal = static_cast<unsigned char>(std::min(std::sqrt(pixelX * pixelX + pixelY * pixelY), 255.0f));
            edgeData[y][x][0] = edgeVal;
        }
    }

    img.setData(edgeData); // update the image data
}