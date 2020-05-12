cmake_minimum_required(VERSION 3.14)
project(ImageProcessing)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

SET(OpenCV_DIR /home/student/OpenCV_installation/installation/OpenCV-master/lib/cmake/opencv4)
add_executable(ImageProcessing main.cpp)