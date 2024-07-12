#ifndef TESTS_COLOUR_CORRECTION_H
#define TESTS_COLOUR_CORRECTION_H

// Include the necessary headers
#include "../../src/image.h"
#include "../../src/filter.h"
#include <string>

class TestsColourCorrection {
public:
    static void runAllTests();

// private:
    static void testSaltPepperNoise(int percent );
    static void testThresholdGeneral( char L_or_V_or_G, int value);
    // static void testThresholdLight( char L_or_V_or_G, int value);
    // static void testThresholdDark( char L_or_V_or_G, int value);
    static void testAdjustBrightness(int brightness);
    static void testConvertToGrayscale();
    // static void testHistogramEqualization();
};

#endif // TESTS_EDGE_DETECTION_H