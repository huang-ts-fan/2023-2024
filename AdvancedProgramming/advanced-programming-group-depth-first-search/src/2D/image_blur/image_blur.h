// Group Name: Depth First Search
// Group Members:
// - Alex Njeumi(Acse-ann23)
// - Yixiao Jing(acse-yj823)
// - Andrei Danila(edsml-acd23)
// - Fan Huang(acse-fh223)
// - Shrreya Behll(edsml-sb3323)
// - Wenxin Zhang(acse-wz2723)
// edge_detection.h
#ifndef IMAGE_BLUR_H
#define IMAGE_BLUR_H

#include "../../Image.h"

void applyBoxBlur(Image& img, int blurSize);
void applyGaussianBlur(Image& img, double sigma, int kernelSize);
void applyMedianBlur(Image& img, int kernelSize);

#endif // EDGE_DETECTION_H