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
        std::cout << "computing Filling\n";
        Complement::compute(image);
        Kernel k = KernelGenerator::generate(1);
        Image marker(image.getWidth(), image.getHeight(), image.getName(), "border");
        Image markerCopy(marker, "markerCopy");
        do{
            markerCopy = marker;
            Dilation::computeBin(marker, k);
            marker &= image;
        }while(marker != markerCopy);

        Complement::compute(marker);

        image = marker;

        return image;
    }
};


#endif //IMAGEPROCESSING_FILLING_HPP
