// Group Name: Depth First Search
// Group Members:
// - Alex Njeumi(Acse-ann23)
// - Yixiao Jing(acse-yj823)
// - Andrei Danila(edsml-acd23)
// - Fan Huang(acse-fh223)
// - Shrreya Behll(edsml-sb3323)
// - Wenxin Zhang(acse-wz2723)
#ifndef threeD_IMAGE_BLUR_H
#define threeD_IMAGE_BLUR_H

#include <vector>
#include "../Volume.h"

std::vector<std::vector<std::vector<double>>> generate3DGaussianKernel(int size, double sigma);
void apply3DGaussianBlur(Volume &volume, const std::vector<std::vector<std::vector<double>>>& kernel);
void apply3DMedianFilter(Volume &volume, int kernelSize);

#endif
