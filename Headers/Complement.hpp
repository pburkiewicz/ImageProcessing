//
// Created by student on 20.05.2020.
//

#ifndef IMAGEPROCESSING_COMPLEMENT_HPP
#define IMAGEPROCESSING_COMPLEMENT_HPP


#include "ImageProcessor.hpp"

class Complement : ImageProcessor {
public:
    static Image& compute(Image& image){
        auto& dataFrom = getData(image);
        for(auto& i : dataFrom ){
             i == 255 ? i = 0 : i=255 ;
        }
        return image;
    }
};


#endif //IMAGEPROCESSING_COMPLEMENT_HPP
