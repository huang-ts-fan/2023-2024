cmake_minimum_required(VERSION 3.10)
project(HelloWorld)

find_package(OpenMP REQUIRED)

add_executable(hello_world hello_world.cpp)

if(OpenMP_CXX_FOUND)
    target_link_libraries(hello_world PUBLIC OpenMP::OpenMP_CXX)
endif()
