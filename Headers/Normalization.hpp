//
// Created by student on 24.05.2020.
//

#ifndef IMAGEPROCESSING_NORMALIZATION_HPP
#define IMAGEPROCESSING_NORMALIZATION_HPP

#include "ImageProcessor.hpp"

#include <array>
#include <set>
#include <map>

class Normalization : ImageProcessor {
public:
    using pointsContainer =  std::vector<std::pair<uchar, uchar>>;
    using lookUpTable = std::map<uchar, uchar>;
private:
    pointsContainer intensivityPoints{};
public:

    explicit Normalization() = default;

    explicit Normalization(pointsContainer& points) : intensivityPoints(points) { ; }


    Image& compute(Image& image) const noexcept { return compute(image, intensivityPoints); }

    static Image& compute(Image& image, pointsContainer const& points) {
        auto begin = getData(image).begin();
        auto end = getData(image).end();
        for (auto channel = 0; channel < image.getChannels(); ++channel) { // go through all channels
            lookUpTable lut = createLookUpTable(image, channel); // create LookUpTable for channel
            if (!points.empty()) { // if there is no points - use simple normalization
                linearNormalization(lut, std::pair(0, 0), *points.begin());
                for (auto pointIt = points.begin(); pointIt != (points.end() - 1); ++pointIt) {
                    linearNormalization(lut, *pointIt, *(pointIt + 1));
                }
                linearNormalization(lut, *(points.end()-1), std::pair(255, 255));
            } else {
                linearNormalization(lut, std::pair(0, 0), std::pair(255, 255));
            }
            for (auto i = begin + channel; i <= end; i += image.getChannels()) {
                *i = lut[*i]; // make changes for channel
            }
//            for_each(begin + channel, end, [&lut](auto& i){ i = lut[i];});
        }
        return image;
    }


private:
    static lookUpTable createLookUpTable(Image& image, int channel) {
        Image::storage_container data = getData(image);
        auto const end = data.end();
        lookUpTable lut;
        for (auto i =  data.begin() + channel; i <= end; i += image.getChannels()) {
            lut.insert(std::pair(*i, *i));
        }
        return lut;
    }


    static lookUpTable&
    linearNormalization(lookUpTable& lut, std::pair<uchar, uchar> const& start, std::pair<uchar, uchar> const& end) {
        auto min = lut.lower_bound(start.first);
        auto max = lut.upper_bound(end.first);
        if (max != lut.begin()) --max;
        uchar const minVal = min->first;
        uchar const maxVal = max->first;
        if (minVal < maxVal && minVal >= start.first && maxVal <= end.first) {
            auto const norm = static_cast<double>(end.second - start.second) / (maxVal - minVal);
            auto const endFor = (lut.find(maxVal) != lut.end()) ? ++lut.find(maxVal) : lut.find(maxVal);
            auto normalize = [norm, start = start.second, minVal](auto& i) {
                i.second = norm * (i.first - minVal) + start;
            };
            for_each(lut.find(minVal), endFor, normalize);
        }
        return lut;

    }

    static void display(pointsContainer const& points) {
        std::cout << "( in" << "\tout )\n";
        for (auto i : points) {
            std::cout << "( " << (int) i.first << "\t" << (int) i.second << " )\n";
        }
    }


};


#endif //IMAGEPROCESSING_NORMALIZATION_HPP
