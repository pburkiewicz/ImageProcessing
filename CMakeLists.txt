cmake_minimum_required(VERSION 3.14)
project(ImageProcessing)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

find_package(OpenCV REQUIRED)

message(STATUS "OpenCV library status:")
message(STATUS "    version: ${OpenCV_VERSION}")
message(STATUS "    libraries: ${OpenCV_LIBS}")
message(STATUS "    include path: ${OpenCV_INCLUDE_DIRS}")
include_directories(Headers)
add_executable(ImageProcessing main.cpp Headers/Image.hpp Headers/ImageProcessor.hpp Headers/Opening.hpp Headers/Filling.hpp Headers/Complement.hpp Headers/Normalization.hpp)

target_link_libraries(ImageProcessing ${OpenCV_LIBS})
