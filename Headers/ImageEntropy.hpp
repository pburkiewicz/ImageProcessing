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
    static std::array<size_t, 256>&& calculateHistogram(Image& image) {
        std::array<size_t, 256> hist{};
        for (auto& i : getData(image)) {
            hist[static_cast<size_t>(i)]++;
        }
        return std::move(hist);
    }

    static std::map<uchar, size_t>&& calculateLocalHistogram(Image::storage_container im) {
        std::map<uchar, size_t> hist{};
        for (auto& i : im) {
            hist[i]++;
        }
        return std::move(hist);
    }

    struct Entropy{
        void operator()(double p) { entropy += (p*log2(1.0/p)); }
        double entropy{0};
    };

public:
    static Image& compute(Image& in, Image& out) noexcept {
        assert(in != out);
        if(in == out || out.getChannels() != 1){
            std::cout << "Image output must be 1 channel image instance and be different than input \n";
            return in;
        }
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
                auto const Lx = std::max(0, static_cast<int>(col - 1 * channels));
                auto const Rx = std::min(newWidth, col + 2 * channels);
                auto const Ty = std::max(0, static_cast<int>(row - 1));
                auto const By = std::min(height, static_cast<size_t>(row + 2));
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
                dataOut.push_back(static_cast<uchar>(std::lround(en.entropy*10)));
                std::cout << hist.size() << " : \t entropy : "<<  en.entropy*10 << "\t " << (int)static_cast<uchar>(std::round(en.entropy*10)) <<"\n";
            }
        }

        Normalization::pointsContainer x{};
        out = Normalization::compute(out, x);
        return out;
    }

};

#endif //IMAGEPROCESSING_IMAGEENTROPY_HPP
