#ifndef TESTS_IMAGE_BLUR_H
#define TESTS_IMAGE_BLUR_H

// Include the necessary headers
#include "../../src/image.h"
#include "../../src/filter.h"
#include <string>

class TestImageBlur {
public:
    static void runAllTests();

// private:
    static void testBoxBlur(int blur_size);
    static void testMedianBlur( int blur_size);
    static void testGaussianBlur( int blur_size);
};

#endif // TESTS_EDGE_DETECTION_H