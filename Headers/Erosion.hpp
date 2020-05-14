//
// Created by student on 13.05.2020.
//

#ifndef IMAGEPROCESSING_EROSION_HPP
#define IMAGEPROCESSING_EROSION_HPP

#include "ImageProcessor.hpp"
#include "KernelGenerator.hpp"
#include <iostream>
#warning remove include iostream

class Erosion : public ImageProcessor {
public:
    Erosion(size_t radius) : ImageProcessor(radius) {}
    Erosion(Kernel const& kernel_) : ImageProcessor(kernel_) {}
    Erosion(Kernel&& kernel_) : ImageProcessor(std::move(kernel_)) {}

    Image& compute(Image& image) const noexcept { return compute(image, kernel); }

    static Image& compute(Image& image, Kernel const& k) noexcept {
        std::cout << "computing Erosion of image\n";
        auto const height = image.getHeigth();
        auto const width = image.getWidth();
        auto data = getData(image);
        int x = static_cast<int>(sqrt(k.data.size()));
        if(1 == image.getChannels()){
            for(auto row = 0 ; row < height-x; ++row){
                for(auto col = 0 ; col < width-x ; ++col ){
                    for( auto i = 0 ; i < x; ++i){
                        for(auto j = 0; j < x ; ++j ){
                            std::cout << data[(row+i)*data.size()+col+i*x+j];
                        }
                    }
                }
            }
        }
        return image;
    }
};


#endif //IMAGEPROCESSING_OPENING_HPP
