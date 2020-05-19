//
// Created by student on 13.05.2020.
//

#ifndef IMAGEPROCESSING_OPENING_HPP
#define IMAGEPROCESSING_OPENING_HPP

#include "ImageProcessor.hpp"
#include "KernelGenerator.hpp"
#include "Erosion.hpp"
#include "Dilation.hpp"
#include <iostream>
#warning remove include iostream

class Opening : public ImageProcessor {
public:
    Opening(size_t radius) : ImageProcessor(radius) {}
    Opening(Kernel const& kernel_) : ImageProcessor(kernel_) {}
    Opening(Kernel&& kernel_) : ImageProcessor(std::move(kernel_)) {}

    Image& compute(Image& i) const noexcept { return compute(i, kernel);}

    static Image& compute(Image& i, Kernel const& k) noexcept {
        KernelGenerator::display(k);
        std::cout << "computing Opening of image\n";
        return Dilation::compute(Erosion::compute(i, k), k);
    }

};


#endif //IMAGEPROCESSING_OPENING_HPP
