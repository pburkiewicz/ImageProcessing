//
// Created by student on 13.05.2020.
//

#ifndef IMAGEPROCESSING_IMAGEPROCESSOR_HPP
#define IMAGEPROCESSING_IMAGEPROCESSOR_HPP
#include "Image.hpp"
#include "KernelGenerator.hpp"
#include <iostream>
#warning delete iostream include

class ImageProcessor {
protected:
    Kernel kernel;
public:
    ImageProcessor(size_t radius) : kernel(std::move(KernelGenerator::generate(radius))) {}
    ImageProcessor(Kernel const& kernel_) : kernel(kernel_) {}
    ImageProcessor(Kernel&& kernel_) : kernel(std::move(kernel_)) {}
    ImageProcessor() = default;
    virtual ~ImageProcessor() = default;

protected:
    static auto& getData(Image& i) {return i.data;}
};


#endif //IMAGEPROCESSING_IMAGEPROCESSOR_HPP
