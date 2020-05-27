//
// Created by student on 13.05.2020.
//

#ifndef IMAGEPROCESSING_DILATION_HPP
#define IMAGEPROCESSING_DILATION_HPP

#include "ImageProcessor.hpp"
#include "KernelGenerator.hpp"
#include <iostream>
#warning remove include iostream

class Dilation : public ImageProcessor {
public:
    explicit Dilation(size_t radius) : ImageProcessor(radius) {}
    explicit Dilation(Kernel const& kernel_) : ImageProcessor(kernel_) {}
    explicit Dilation(Kernel&& kernel_) : ImageProcessor(std::move(kernel_)) {}

    Image& compute(Image& image) const noexcept{ return compute(image, kernel); }

    static Image& compute(Image& image, Kernel const& k) noexcept {
        std::cout << "computing Dilation of image\n";
        auto const height = image.getHeight();
        auto const width = image.getWidth();
        auto& data = getData(image);
        auto const sqrtKernel = static_cast<size_t>(sqrt(k.data.size()));
        size_t const midKernel = k.data.size()/2;
        auto mid = midKernel % sqrtKernel;
        auto dataCopy = data;
        int const sK2 = static_cast<int>(sqrtKernel / 2);

        if (1 == image.getChannels()) {
            for (auto row = 0; row < height; ++row) {
                for (auto col = 0; col < width; ++col) {
                        for (int i = -sK2; i <= sK2 && k.data[midKernel] != data[row * width + col]; ++i) {
                            int const ind = height - row - i;
                            if ((row - (-i) >= 0) && ind > 0) {
                                for (int j = -sK2; j <= sK2; ++j) {
                                    int const ind2 = width - col - j;
                                    if (col - (-j) >= 0 && ind2 > 0) {
                                        if (k.data[(i + sK2) * sqrtKernel + j + sK2] == 255 &&
                                            k.data[(i + sK2) * sqrtKernel + j + sK2] ==
                                            data[(i + row) * width + col + j]) {
                                            dataCopy[row * width + col] = 255;
                                          break;
                                        }
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
