#include <iostream>
#include <string>
#include <cstdlib>
#include <random>
#include <fstream>
#include <vector> 

#include <unistd.h>
#include <cassert>

#include "../../src/image.h"
#include "../../src/filter.h"
#include "test_image_blur.h"


int height = 500;
int width = 500;
int channels = 3;
std::string x = "../tests/2D";
Image random_img (x + "/test_images/random_image.png");
Image colour_img (x + "/test_images/color_image.png"); 
Image spotted500_img (x + "/test_images/spotted500.png"); 
Image dark_img (x + "/test_images/dark_image.png");
Image light_img (x + "/test_images/light_image.png"); 
Image box_img (x + "/test_images/box_image.png"); 

void TestImageBlur::runAllTests(){
    testBoxBlur(5);
    testMedianBlur(5);
    testGaussianBlur(5);
}

void TestImageBlur::testBoxBlur( int blur_size){ // test with box.png
    Image img = box_img;
    int temp_total = 0;
    Filter::applyBoxBlur(img, blur_size); 
    std::vector<std::vector<std::vector<unsigned char> > > data = img.getData();
    

    for (int h = 99; h < 400; h++){ 
        for (int c = 0; c < channels; c++ ){
            assert(data[h][99][c] != 255 || data[h][99][c] != 0);
        }
    }
    for (int h = 99; h < 400; h++){ 
        for (int c = 0; c < channels; c++ ){
            assert(data[h][401][c] != 255 || data[h][401][c] != 0);
        }
    }
    for (int w = 99; w < 400; w++){ 
        for (int c = 0; c < channels; c++ ){
            assert(data[99][w][c] != 255 || data[99][w][c] != 0);
        }
    }
    for (int w = 99; w < 400; w++){ 
        for (int c = 0; c < channels; c++ ){
            assert(data[401][w][c] != 255 || data[401][w][c] != 0);
        }
    }

}

void TestImageBlur::testMedianBlur( int blur_size){ // image with spots every 10 pixels use blur size less than 10
    Image img = spotted500_img;
    Filter::applyMedianBlur(img, blur_size); 
    std::vector<std::vector<std::vector<unsigned char> > > data = img.getData();
    

    for (int h = 0; h < height; h++){
        for (int w = 0; w < width; w++){ 
            for (int c = 0; c < channels; c++){    
                assert(data[h][w][c] == 255);
            }
        }
    }
}

void TestImageBlur::testGaussianBlur( int blur_size){ // image with spots every 10 pixels
    Image img = spotted500_img;
    Filter::applyGaussianBlur(img,1,  blur_size); 
    std::vector<std::vector<std::vector<unsigned char> > > data = img.getData();
    

    for (int h = 1; h < height; h++){
        for (int w = 1; w < width; w++){ 
            for (int c = 0; c < channels; c++){ 

                assert(data[h][w][c] != 0);
                if (h % 10 == 0 && w % 10 == 0){
                    assert(data[h-1][w][c] != 255);
                    assert(data[h+1][w][c] != 255);
                    assert(data[h-1][w-1][c] != 255);
                    assert(data[h-1][w+1][c] != 255);
                    assert(data[h][w-1][c] != 255);
                    assert(data[h][w+1][c] != 255);
                    assert(data[h+1][w+1][c] != 255);
                    assert(data[h+1][w-1][c] != 255);
                }
            }
        }
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
    std::cout << "Loading images..." << std::endl;
    


    std::cout << "Running tests..." << std::endl;
    TestImageBlur::runAllTests();
    std::cout << "success";
    return 0;
}