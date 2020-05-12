//
// Created by student on 13.05.2020.
//

#include <opencv2/highgui.hpp>
#include <filesystem>
#include <string>
using namespace cv;
#ifndef IMAGEPROCESSING_IMAGE_H
#define IMAGEPROCESSING_IMAGE_H

class Image {
    Mat image;
    std::filesystem::path input;
    std::filesystem::path output;

    Image(std::filesystem::path input) : input(input), output(input){
        image = imread(input.u8string());
    }
    Image(std::filesystem::path input,  std::filesystem::path output): input(input), output(output){
        image = imread(input.u8string());
    }
    ~Image(){
        image.deallocate();
    }
};


#endif //IMAGEPROCESSING_IMAGE_H
