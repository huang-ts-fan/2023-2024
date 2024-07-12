cmake_minimum_required(VERSION 3.9)
project(advanced_programming_group_depth_first_search)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -flto")

include_directories(src, tests)

add_executable(advanced_programming_group_depth_first_search
        src/main.cpp
        src/Image.h
        src/Image.cpp
        src/Projection.cpp
        src/Projection.h
        src/Slice.cpp
        src/Slice.h
        src/Volume.cpp
        src/Volume.h
        src/stb_image.h
        src/stb_image_write.h
        src/3D/threeD_image_blur.h
        src/3D/threeD_image_blur.cpp
        src/filter.cpp
        src/filter.h
        src/UserInterface.cpp
        src/UserInterface.h
        src/2D/image_blur/image_blur.cpp
        src/2D/image_blur/image_blur.h
        src/2D/edge_detection/edge_detection.cpp
        src/2D/edge_detection/edge_detection.h
        src/2D/colour_correction/colour_correction.cpp
        src/2D/colour_correction/colour_correction.h)

add_executable(test_blur
        src/Image.h
        src/Image.cpp
        src/Projection.cpp
        src/Projection.h
        src/Slice.cpp
        src/Slice.h
        src/Volume.cpp
        src/Volume.h
        src/stb_image.h
        src/stb_image_write.h
        src/3D/threeD_image_blur.h
        src/3D/threeD_image_blur.cpp
        src/filter.cpp
        src/filter.h
        src/UserInterface.cpp
        src/UserInterface.h
        src/2D/image_blur/image_blur.cpp
        src/2D/image_blur/image_blur.h
        src/2D/edge_detection/edge_detection.cpp
        src/2D/edge_detection/edge_detection.h
        src/2D/colour_correction/colour_correction.cpp
        src/2D/colour_correction/colour_correction.h
        tests/2D/test_image_blur.cpp)

add_executable(test_edge
        src/Image.h
        src/Image.cpp
        src/Projection.cpp
        src/Projection.h
        src/Slice.cpp
        src/Slice.h
        src/Volume.cpp
        src/Volume.h
        src/stb_image.h
        src/stb_image_write.h
        src/3D/threeD_image_blur.h
        src/3D/threeD_image_blur.cpp
        src/filter.cpp
        src/filter.h
        src/UserInterface.cpp
        src/UserInterface.h
        src/2D/image_blur/image_blur.cpp
        src/2D/image_blur/image_blur.h
        src/2D/edge_detection/edge_detection.cpp
        src/2D/edge_detection/edge_detection.h
        src/2D/colour_correction/colour_correction.cpp
        src/2D/colour_correction/colour_correction.h
        tests/2D/test_edge_detection.cpp)

add_executable(test_correction
        src/Image.h
        src/Image.cpp
        src/Projection.cpp
        src/Projection.h
        src/Slice.cpp
        src/Slice.h
        src/Volume.cpp
        src/Volume.h
        src/stb_image.h
        src/stb_image_write.h
        src/3D/threeD_image_blur.h
        src/3D/threeD_image_blur.cpp
        src/filter.cpp
        src/filter.h
        src/UserInterface.cpp
        src/UserInterface.h
        src/2D/image_blur/image_blur.cpp
        src/2D/image_blur/image_blur.h
        src/2D/edge_detection/edge_detection.cpp
        src/2D/edge_detection/edge_detection.h
        src/2D/colour_correction/colour_correction.cpp
        src/2D/colour_correction/colour_correction.h
        tests/2D/test_colour_correction.cpp)

set_property(TARGET advanced_programming_group_depth_first_search PROPERTY INTERPROCEDURAL_OPTIMIZATION TRUE)