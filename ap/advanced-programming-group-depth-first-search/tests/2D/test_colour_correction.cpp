#include <iostream>
#include <string>
#include <cstdlib>
#include <random>
#include <fstream>
#include <vector> 

#include <unistd.h>
#include <cassert>

#include <random>
#include <limits.h>
#include <stddef.h>
#include <cmath>

#include "../src/Image.h"
#include "../src/Filter.h"
#include "test_colour_correction.h"

int height = 500;
int width = 500;
int channels = 3;
std::string y = "../tests/2D/";
Image colour_img (y + "test_images/color_image.png"); 
Image spotted50_img (y + "test_images/spotted50.png");  
Image dark_img (y + "test_images/dark_image.png");
Image random_img (y + "test_images/random_image.png");
Image spotted500_img (y + "test_images/spotted500.png");
Image light_img (y + "test_images/light_image.png");
Image box_img (y + "test_images/box_image.png");


void TestsColourCorrection::runAllTests(){
    testSaltPepperNoise(20);
    testThresholdGeneral('L', 128);
    // testThresholdLight(128);
    // testThresholdDark(128);
    testAdjustBrightness(30);
    testConvertToGrayscale();

}

void TestsColourCorrection::testSaltPepperNoise( int percent ){ // test with 5,10,15,20 percent
    Image img = dark_img;
    int temp_total = 0;
    Filter::applySaltPepperNoise(img,percent);
    std::vector<std::vector<std::vector<unsigned char> > > data = img.getData();
    int counter = 0;
    std::cout << data.size() << std::endl;
    for (int h = 0; h < height; h++){
        
        for (int w = 0; w < width; w++){
            
            temp_total = 0;
            for (int c = 0; c < channels ; c++){
                temp_total += data[h][w][c]; 
            }
            if (temp_total == 0 ||  temp_total == 765){
                counter += 1;
            }
            std::cout << counter << std::endl;
        }
    }
    float check = counter/(width*height);
    std::cout << counter*100 << std::endl;
    std::cout << (width*height)* percent << std::endl;
    std::cout << check << std::endl;
    assert(counter*100.0 < percent*(width*height));
    assert(counter*100.0 > (percent-7)*(width*height) );
}

void TestsColourCorrection::testThresholdGeneral( char L_or_V_or_G, int value){ // for spotted50 
    int temp_total = 0;
    int counter1 = 0;
    int height = 50;
    int width = 50;
    Image img = colour_img;
    Filter::applyThreshold(img, L_or_V_or_G, value); // for black 
    std::vector<std::vector<std::vector<unsigned char> > > data = img.getData();
    
    std::cout << height << std::endl;
        for (int h = 0; h < height; h++){
            for (int w = 0; w < width; w++){
                temp_total = 0;
                for (int c = 0; c < channels ; c++){

                    temp_total += data[h][w][c]; 
                }
                if (temp_total == 0 ||  temp_total == 765){
                    counter1 += 1;
                }
            }
        }
    assert(counter1 == width*height);

}


void TestsColourCorrection::testAdjustBrightness(int brightness){ // increase brightness of dark image
    Image img = dark_img;
    std::vector<std::vector<std::vector<unsigned char> > > data_original = img.getData();
    
    Filter::applyBrightnessDullness(img, brightness);
    std::vector<std::vector<std::vector<unsigned char> > > data = img.getData();
 
    int total_brightness = 0;
        for (int h = 0; h < height; h++){
            for (int w = 0; w < width; w++){
                for (int c = 0; c < channels ; c++){
                    total_brightness += data[h][w][c] - data_original[h][w][c];  
                }
        }
    }
           
    assert(total_brightness/ (width*height*channels) == brightness);
}

void TestsColourCorrection::testConvertToGrayscale(){ // use any image 
    Image img = colour_img;
    Filter::applyGrayScale(img);
    std::vector<std::vector<std::vector<unsigned char> > >  data = img.getData();
    
    int height = 50;
    int width = 50;
        for (int h = 0; h < height; h++){
            for (int w = 0; w < width; w++){
                int d = data[h][w][0];
                int e = data[h][w][1];
                int f = data[h][w][2];
                assert(data[h][w][0] == data[h][w][1] && data[h][w][1] == data[h][w][2]);
        }
        }

}


// histogram equalization test 



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
    // Image random_img(x + "/test_images/random_image.png");
    // Image colour_img(x + "/test_images/color_image.png"); 
    // Image spotted_img(x + "/test_images/spotted500.png"); 
    // Image dark_img(x + "/test_images/dark_image.png");
    // Image light_img(x + "/test_images/light_image.png"); 
    // Image box_img(x + "/test_images/box_image.png"); 
    Image random_img (y + "test_images/random_image.png");
    Image colour_img (y + "test_images/color_image.png"); 
    Image spotted500_img (y + "test_images/spotted500.png"); 
    Image spotted50_img (y + "test_images/spotted50.png"); 
    Image dark_img (y + "test_images/dark_image.png");
    Image light_img (y + "test_images/light_image.png"); 
    Image box_img (y + "test_images/box_image.png"); 

    // Check if images are loaded successfully
    if (random_img.getData().empty() || colour_img.getData().empty() || 
        spotted50_img.getData().empty() || dark_img.getData().empty() || 
        light_img.getData().empty() || box_img.getData().empty()) {
        std::cerr << "Error loading images" << std::endl;
        return 1;
    }

    std::cout << "Running tests..." << std::endl;
    TestsColourCorrection::testConvertToGrayscale();
    std::cout << "success";
    return 0;
}

