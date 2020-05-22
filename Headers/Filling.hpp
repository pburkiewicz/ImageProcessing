//
// Created by student on 20.05.2020.
//

#ifndef IMAGEPROCESSING_FILLING_HPP
#define IMAGEPROCESSING_FILLING_HPP

#include "ImageProcessor.hpp"
#include "Complement.hpp"

class Filling : public ImageProcessor{


public:
    static Image& compute(Image& image){
//        Image mask(image, "mask");
        Complement::compute(image);

        Kernel k = KernelGenerator::generate(1);
        Image::storage_container& im = getData(image);

        Kernel temp = KernelGenerator::generate(sqrt(im.size()), "full");
        Image marker(temp.data, 1, (size_t)sqrt(im.size()),  (size_t)sqrt(im.size()), "marker");

        Image::storage_container& mask = getData(image);
        Image::storage_container markerCopy;
        Image::storage_container& mark = getData(marker);
        do{
            markerCopy = getData(marker);
            Dilation::compute(marker, k);
            for(auto i = 0 ; i < mask.size(); ++i){
                 mark[i] &= mask[i];
            }
        }while(mark != markerCopy);
        Complement::compute(marker);
        image = marker;

        return image;
    }
};


#endif //IMAGEPROCESSING_FILLING_HPP
