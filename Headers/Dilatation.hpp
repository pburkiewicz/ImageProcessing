//
// Created by student on 13.05.2020.
//

#ifndef IMAGEPROCESSING_DILATATION_HPP
#define IMAGEPROCESSING_DILATATION_HPP

#include "ImageProcessor.hpp"
#include "KernelGenerator.hpp"
#include <iostream>
#warning remove include iostream

class Dilatation : public ImageProcessor {
public:
    Dilatation(size_t radius) : ImageProcessor(radius) {}
    Dilatation(Kernel const& kernel_) : ImageProcessor(kernel_) {}
    Dilatation(Kernel&& kernel_) : ImageProcessor(std::move(kernel_)) {}

    Image& compute(Image& image) const noexcept{ return compute(image, kernel); }

    static Image& compute(Image& image, Kernel const& k) noexcept {
        std::cout << "computing Dilatation of image\n";
        auto const height = image.getHeigth();
        auto const width = image.getWidth();
        if(1 == image.getChannels()){
            for(auto row = 0 ; row < height; ++row){
                for(auto col = 0 ; col < width ; ++col ){
                    for( auto i = 0 ; i < sqrt(k.data.size()); ++i){
                        for(auto j = 0; j <sqrt(k.data.size()) ; ++j ){
                            getData(image)[(row+i)];
                        }
                    }
                }
            }
        }
        return image;
    }
};
#endif //IMAGEPROCESSING_OPENING_HPP
