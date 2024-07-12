// Group Name: Depth First Search
// Group Members:
// - Alex Njeumi(Acse-ann23)
// - Yixiao Jing(acse-yj823)
// - Andrei Danila(edsml-acd23)
// - Fan Huang(acse-fh223)
// - Shrreya Behll(edsml-sb3323)
// - Wenxin Zhang(acse-wz2723)
#ifndef COLOUR_CORRECTION_H
#define COLOUR_CORRECTION_H

#include <vector>
#include "../../Image.h"

// Declaration of HSVPixel structure for HSV color space representation
struct HSVPixel {
    float h, s, v;
};

// Declaration of HSLPixel structure for HSL color space representation
struct HSLPixel {
    float h, s, l;
};

// Function declarations
void applyGrayscale(Image& img);
void applyBrightnessDullness(Image& img, int brightness);
void applyGrayscaleEqualization(Image& img);
void applyRGB_HSVEqualization(Image& img);
void applyRGB_HSLEqualization(Image& img);
void applySaltPepperNoise(Image& img, int percentage);
void applyThreshold(Image& img, char L_or_V_or_G, float threshold);

#endif // COLOUR_CORRECTION_H
