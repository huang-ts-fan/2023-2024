#ifndef TESTS_EDGE_DETECTION_H
#define TESTS_EDGE_DETECTION_H

// Include the necessary headers

#include "../../src/image.h"
#include "../../src/filter.h"
#include <string>

class TestsEdgeDetection {
public:
    static void runAllTests();

// private:
    static void testApplySobelEdgeDetection();
    static void testApplyPrewittEdgeDetection();
    static void testApplyScharrEdgeDetection();
    static void testApplyRobertsCrossEdgeDetection();
};

#endif // TESTS_EDGE_DETECTION_H
