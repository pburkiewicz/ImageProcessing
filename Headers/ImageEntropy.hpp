//
// Created by student on 18.05.2020.
//

#ifndef IMAGEPROCESSING_IMAGEENTROPY_HPP
#define IMAGEPROCESSING_IMAGEENTROPY_HPP

#include "ImageProcessor.hpp"
#include "Normalization.hpp"
#include "Complement.hpp"
#include <vector>
#include <array>
#include <iostream>
#include <map>
#include <algorithm>

#warning remove include iostream

class ImageEntropy : public ImageProcessor {
public:

//    Image& compute(Image &image) const noexcept { return ImageEntropy::compute(image); }
private:


    struct Entropy{
        void operator()(double p) { entropy += (p*log2(1.0/p)); }
        double entropy{0};
    };

public:
    static Image& compute(Image& in, Image& out, size_t N) noexcept {
        assert(in != out);
        if(in == out || out.getChannels() != 1){
            std::cout << "Image output must be 1 channel image instance and be different than input \n";
            return in;
        }
        std::vector<double> d;
        std::cout << "computing Entropy of image\n";
        Image::storage_container& dataIn = getData(in);
        Image::storage_container& dataOut = getData(out);
        auto const channels = in.getChannels();
        auto const height = in.getHeight();
        auto const width = in.getWidth();
        auto const newWidth = width * channels;
        Image::storage_container entropyData{};
        entropyData.reserve(width*height);
        for (auto row = 0; row < height; ++row) {
            for (auto col = 0; col < newWidth; col += channels) {
                auto const Lx = std::max(0, static_cast<int>(col - N/2 * channels));
                auto const Rx = std::min(newWidth, col +  (N/2+1) * channels);
                auto const Ty = std::max(0, static_cast<int>(row - N/2));
                auto const By = std::min(height, static_cast<size_t>(row + N/2+1));
                std::map<uchar, size_t> hist{};
                size_t size = 0;
                for (auto newRow = Ty; newRow < By; ++newRow) {
                    for (auto newCol = Lx; newCol < Rx; ++newCol) {
                        hist[dataIn[newRow * newWidth + newCol]]++;       // count unique values of pixelsstd::cout << p << "\t";
                        ++size;
                    }
                }
                std::vector<double> probability;
                for (auto& [key, value] : hist) {
                    probability.push_back((1.0*value)/(1.0*size));
                }
                Entropy en = for_each(probability.begin(), probability.end(), Entropy());
                d.push_back(en.entropy);
            }
        }
        auto max = std::max_element(d.begin(), d.end());
        auto min = std::min_element(d.begin(), d.end());
        auto maxmax = std::max(abs(*max.base()), abs(*min.base()));
        for(auto& i : d){
            dataOut.push_back(static_cast<uchar>(i/maxmax*255));
        }
//        Normalization::pointsContainer x{};
//        out = Normalization::compute(out, x);
        return out;
    }

};

#endif //IMAGEPROCESSING_IMAGEENTROPY_HPP
