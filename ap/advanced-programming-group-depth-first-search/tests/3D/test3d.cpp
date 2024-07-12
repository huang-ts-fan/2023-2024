#include <iostream>
#include <string>
#include <cstdlib>
#include <random>
#include <fstream>
#include <vector> 

#include <unistd.h>

#include <random>
#include <limits.h>
#include <stddef.h>
#include <cmath>

#include "../../src/image.h"

#include "../../src/filter.h"
#include "../../src/Projection.h"
#include "../../src/Volume.h"

int height = 500;
int width = 500;
int channels = 3; 



// /Users/alexnjeumi/Desktop/advanced-programming-group-depth-first-search/tests/3D/3d_help_img/3d_avg
std::string filename_box = "advanced-programming-group-depth-first-search/tests/3D/3d_help_img/box3d";
std::string filename_avg = "advanced-programming-group-depth-first-search/tests/3D/3d_help_img/3d_avg";
std::string filename_max = "advanced-programming-group-depth-first-search/tests/3D/3d_help_img/3d_max";

void test_generateMinIPn(){
    // use box 3d
    Volume volume;
    if (!volume.loadFromDirectory_filter(filename_box, 0, 50)) {
        std::cerr << "Failed to load volume data from directory." << std::endl;
    }
    std::vector<unsigned char*> filteredVolumeData = volume.convertToCharPointers();

    std::vector<unsigned char> data = Projection::generateMinIP(filename_box,width,height,50,filteredVolumeData);

    for (int h = 101; h < 400; h++){
        for (int w = 101; w < 400; w++){
                assert(data[h * width + w] == 0);
        }
    }

}

void test_generateAIP(){
    Volume volume;
    if (!volume.loadFromDirectory_filter(filename_avg, 0, 50)) {
        std::cerr << "Failed to load volume data from directory." << std::endl;
    }
    std::vector<unsigned char*> filteredVolumeData = volume.convertToCharPointers();

    std::vector<unsigned char> data = Projection::generateAIP(filename_avg,width,height,50,filteredVolumeData);

    for (int h = 0; h < height; h++){
        for (int w = 0; w < width; w++){
                assert(data[h * width + w] == 150);
        }
    }
}

void test_generateMIP(){
    Volume volume;
    if (!volume.loadFromDirectory_filter(filename_max, 0, 50)) {
        std::cerr << "Failed to load volume data from directory." << std::endl;
    }
    std::vector<unsigned char*> filteredVolumeData = volume.convertToCharPointers();

    std::vector<unsigned char> data = Projection::generateMIP(filename_max,width,height,50,filteredVolumeData);

    for (int h = 101; h < 400; h++){
        for (int w = 101; w < 400; w++){
                assert(data[h * width + w] == 255);
        }
    }
}


int main(){
    // Volume volume;
    //  if (!volume.loadFromDirectory_filter("tests/3D/3d_help_img", 0, 0)) {
    //  std::cerr << "Failed to load volume data." << std::endl;
    //  return 1;
    // }

    // std::vector<unsigned char*> filteredVolumeData = volume.convertToCharPointers();

    // Projection::generateMIP("../Output/3D/fracture/mip-nofilter.png", volume.getWidth(), volume.getHeight(), volume.getDepth(), filteredVolumeData);
    test_generateAIP();
    std::cout << "success" << std::endl;
    test_generateMinIPn();
    std::cout << "success" << std::endl;
    test_generateMIP();
    std::cout << "success" << std::endl;


}