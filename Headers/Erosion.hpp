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
        auto& data = getData(image);
        auto const sqrtKernel = static_cast<size_t>(sqrt(k.data.size()));
        size_t const midKernel = k.data.size()/2;
        auto mid = midKernel % sqrtKernel;
        auto dataCopy = data;
//        for(auto& i: dataCopy) i = 0;
        if(1 == image.getChannels()){
            for(auto row = mid ; row < height-mid; ++row){
                for(auto col = mid ; col < width-mid; ++col ){
                    if(k.data[midKernel] == data[row*width+col] ) {
                        int aaaaa = 0;
                        for (auto i = 0; i < sqrtKernel+1; ++i) {
                            for (auto j = 0; j < sqrtKernel+1; ++j) {
                                aaaaa= (i +row) * width  + col + j;
                                if(k.data[i*sqrtKernel + j] == 255 && k.data[i*sqrtKernel + j]  != data[(i +row) * width + col + j] ){
                                    dataCopy[row*width+col] = 0;
                                }
                            }
                        }
                    }
                }
            }
            std::memcpy(data.data(), dataCopy.data(), data.size());
        }
        return image;
    }
};


#endif //IMAGEPROCESSING_OPENING_HPP
