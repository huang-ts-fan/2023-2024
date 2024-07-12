#include <iostream>
#include <string>
#include <vector> 
#include <unistd.h>
#include <cassert>

#include "../../src/image.h"
#include "../../src/filter.h"
#include "test_edge_detection.h"

int height = 500;
int width = 500;
int channels = 3;
std::string x = "../tests/2D";
Image random_img (x + "/test_images/random_image.png");
Image colour_img (x + "/test_images/color_image.png"); 
Image spotted_img (x + "/test_images/spotted500.png"); 
Image dark_img (x + "/test_images/dark_image.png");
Image light_img (x + "/test_images/light_image.png"); 
Image box_img (x + "/test_images/box_image.png"); 

void TestsEdgeDetection::runAllTests(){
    std::cout << "running sobel" << std::endl;
    testApplySobelEdgeDetection();
    std::cout << "running prewitt" << std::endl;
    testApplyPrewittEdgeDetection();
    std::cout << "running scharr" << std::endl;
    testApplyScharrEdgeDetection();
    std::cout << "running robert" << std::endl;
    testApplyRobertsCrossEdgeDetection();
}

// perhaps single dot and apply filter ? then check neghbouring courners
void TestsEdgeDetection::testApplySobelEdgeDetection(){ // image with spots every 10 pixels
    Image img = spotted_img;
    float sobelX[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    float sobelY[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};
    Image::convertToGrayscale(img);
    Filter::applyEdgeDetection(img, sobelX, sobelY); 
    std::vector<std::vector<std::vector<unsigned char> > > data = img.getData();
    
    int c = 0;
    for (int h = 1; h < height; h++){
        for (int w = 1; w < width; w++){ 
                if (h % 10 == 0 && w % 10 == 0){ // check the corners

                    assert(data[h][w][c] == 0);
                    assert(data[h-1][w][c] == 255); // side
                    assert(data[h+1][w][c] == 255);
                    assert(data[h-1][w-1][c] == 255); //corner
                    assert(data[h-1][w+1][c] == 255); //corner
                    assert(data[h][w-1][c] == 255); // side
                    assert(data[h][w+1][c] == 255);
                    assert(data[h+1][w+1][c] == 255); //corner
                    assert(data[h+1][w-1][c] == 255); //corner


                    assert(data[h-2][w][c] == 0);
                    assert(data[h+2][w][c] == 0);
                    assert(data[h-2][w-2][c] == 0);
                    assert(data[h-2][w+2][c] == 0);
                    assert(data[h][w-2][c] == 0);
                    assert(data[h][w+2][c] == 0);
                    assert(data[h+2][w+2][c] == 0);
                    assert(data[h+2][w-2][c] == 0);

                }

        }
    }
}


void TestsEdgeDetection::testApplyPrewittEdgeDetection(){ // use spotted image, it check for bottom and right side of pixel being coloured 
    Image img = spotted_img;
    float prewittX[3][3] = {{-1, 0, 1}, {-1, 0, 1}, {-1, 0, 1}};
    float prewittY[3][3] = {{-1, -1, -1}, {0, 0, 0}, {1, 1, 1}};
    Image::convertToGrayscale(img);
    Filter::applyEdgeDetection(img, prewittX, prewittY);
    std::vector<std::vector<std::vector<unsigned char> > > data = img.getData();
    
    int c = 0;
    for (int h = 1; h < height; h++){
        for (int w = 1; w < width; w++){ 
  
                if ((h % 10 == 0 && w % 10 == 0)){ // check the corners
                    assert(data[h][w][c] == 0);
                    assert(data[h-1][w+1][c] == 255);
                    assert(data[h][w+1][c] == 255);
                    assert(data[h][w+1][c] == 255);
                    assert(data[h+1][w+1][c] == 255); // special value
                    assert(data[h+1][w][c] == 255);
                    assert(data[h+1][w-1][c] == 255);

                }
        }
    }
}

void TestsEdgeDetection::testApplyScharrEdgeDetection(){ // use spotted image, it check for bottom and right side of pixel being coloured 
    Image img = spotted_img;
    float scharrX[3][3] = {{-3, 0, 3}, {-10, 0, 10}, {-3, 0, 3}};
    float scharrY[3][3] = {{-3, -10, -3}, {0, 0, 0}, {3, 10, 3}};

    Image::convertToGrayscale(img);
    Filter::applyEdgeDetection(img, scharrX, scharrY);
    std::vector<std::vector<std::vector<unsigned char> > > data = img.getData();
    int c = 0;

    for (int h = 1; h < height; h++){
        for (int w = 1; w < width; w++){ 
                if (h % 10 == 0 && w % 10 == 0){ // check the corners

                    assert(data[h][w][c] == 0);

                    assert(data[h-1][w+1][c] == 255);
                    assert(data[h][w+1][c] == 255);
                    assert(data[h+1][w+1][c] == 255); // special value
                    assert(data[h+1][w][c] == 255);
                    assert(data[h+1][w-1][c] == 255);
                    assert(data[h][w-1][c] == 255);
                    assert(data[h-1][w][c] == 255);
                    assert(data[h-1][w-1][c] == 255);

                }
        }
    }
}

void TestsEdgeDetection::testApplyRobertsCrossEdgeDetection(){ // use box image,  check for top side and lateral sides
    Image img = box_img;
    // std::cout << "working";
    Image::convertToGrayscale(img);
    Filter::applyRobertsCrossEdgeDetection(img);
    std::vector<std::vector<std::vector<unsigned char> > > data = img.getData();
    
    int c = 0;
    for (int w = 100; w < 401; w++){
            assert (data[99][w][c] == 255); // checks horizontal line 
    }
    for (int h = 101; h < 401; h++){
            assert (data[h][99][c] == 255); // check for the vertical lines 
            assert (data[h][400][c] == 255);
    }
}

int main() {
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        std::cout << "Current working directory: " << cwd << std::endl;
    } else {
        std::cerr << "Error getting current working directory" << std::endl;
        return 1;
    }

    // Test image loading
    // std::cout << "Loading images..." << std::endl;
    // Image random_img(x + "/test_images/random_image.png");
    // Image colour_img(x + "/test_images/color_image.png"); 
    // Image spotted_img(x + "/test_images/spotted500.png"); 
    // Image dark_img(x + "/test_images/dark_image.png");
    // Image light_img(x + "/test_images/light_image.png"); 
    // Image box_img(x + "/test_images/box_image.png"); 

    // Check if images are loaded successfully
    if (random_img.getData().empty() || colour_img.getData().empty() || 
        spotted_img.getData().empty() || dark_img.getData().empty() || 
        light_img.getData().empty() || box_img.getData().empty()) {
        std::cerr << "Error loading images" << std::endl;
        return 1;
    }

    std::cout << "Running tests..." << std::endl;
    TestsEdgeDetection::runAllTests();
    std::cout << "success";
    return 0;
}
