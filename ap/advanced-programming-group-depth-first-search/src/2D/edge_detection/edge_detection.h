// Group Name: Depth First Search
// Group Members:
// - Alex Njeumi(Acse-ann23)
// - Yixiao Jing(acse-yj823)
// - Andrei Danila(edsml-acd23)
// - Fan Huang(acse-fh223)
// - Shrreya Behll(edsml-sb3323)
// - Wenxin Zhang(acse-wz2723)
#ifndef EDGE_DETECTION_H
#define EDGE_DETECTION_H

#include "../../Image.h"

void applyEdgeDetection(Image& img, const float operatorX[3][3], const float operatorY[3][3]);
void applyRobertsCrossEdgeDetection(Image& img);

#endif // EDGE_DETECTION_H