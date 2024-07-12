cmake_minimum_required(VERSION 3.10)
project(AssignmentProjects)

# Find C++ compiler
enable_language(CXX)

# Find and enable OpenMP support
find_package(OpenMP REQUIRED)
if(OPENMP_FOUND)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
endif()

# Set the C++ standard
set(CMAKE_CXX_STANDARD 11)

# Add build rule for "HelloWorld" from source files in "assignment-1"
file(GLOB_RECURSE SOURCES_HELLOWORLD "assignment-1/*.cpp" "assignment-1/*.h")
add_executable(HelloWorld ${SOURCES_HELLOWORLD})
target_link_libraries(HelloWorld ${MATH_LIBRARY})

# Add build rule for "area" from source files in "assignment-2"
file(GLOB_RECURSE SOURCES_AREA "assignment-2/*.cpp" "assignment-2/*.h")
add_executable(area ${SOURCES_AREA})
target_link_libraries(area ${MATH_LIBRARY})

# Add build rule for "md" from source files in "assignment-3"
file(GLOB_RECURSE SOURCES_MD "assignment-3/*.cpp" "assignment-3/*.h")
add_executable(md ${SOURCES_MD})
target_link_libraries(md ${MATH_LIBRARY})

