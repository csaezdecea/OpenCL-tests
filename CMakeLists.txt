cmake_minimum_required(VERSION 3.10)
project(OpenCLTest)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Find OpenCL package
find_package(OpenCL REQUIRED)

# Include OpenCL headers
include_directories(${OpenCL_INCLUDE_DIRS})

# Add executable for your OpenCL program
add_executable(Check_Gpu check_gpu.cpp)
add_executable(vec_add vector_addition.cpp)

# Link the OpenCL library to your executable
target_link_libraries(Check_Gpu ${OpenCL_LIBRARIES})
target_link_libraries(vec_add ${OpenCL_LIBRARIES})