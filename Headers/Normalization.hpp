//
// Created by student on 24.05.2020.
//

#ifndef IMAGEPROCESSING_NORMALIZATION_HPP
#define IMAGEPROCESSING_NORMALIZATION_HPP

#include "ImageProcessor.hpp"

#include <array>
#include <set>
#include <map>

class Normalization : ImageProcessor{
public:
    using pointsContainer =  std::vector<std::pair<uchar, uchar>>;
    using lookUpTable = std::map<uchar, uchar>;
private:
   pointsContainer intensivityPoints{};
public:

    explicit Normalization() = default;
    explicit Normalization(pointsContainer& points) : intensivityPoints(points){ ; }


    Image& compute(Image &image) const noexcept { return compute(image, intensivityPoints); }

    static Image& compute(Image& image, pointsContainer const& points){
        auto begin = getData(image).begin();
        auto end = getData(image).end();
        for(auto channel = 0 ; channel < image.getChannels() ; ++channel) {
            lookUpTable lut = createLookUpTable(image, begin,end, channel); // create LookUpTable for channel
            if (!points.empty()) { // if there is no points - use simple normalization
                linearNormalization(lut, std::pair(0, 0), points[0]);
                for (auto pointIt = points.begin(); pointIt != (points.end() - 1); ++pointIt) {
                    linearNormalization(lut, *pointIt, *(pointIt + 1));
                }
                linearNormalization(lut, points[points.size() - 1], std::pair(255, 255));
            } else {
                linearNormalization(lut, std::pair(0, 0), std::pair(255, 255));
            }
            for(auto i = begin+channel ; i != end+channel  ; i+=(image.getChannels())){
                *i = lut[*i]; // make changes for channel
            }
        }
        return image;
    }



private:
    static lookUpTable createLookUpTable(Image& image,Image::storage_container::iterator& begin, Image::storage_container::iterator& end, int channel ){
        Image::storage_container data = getData(image);
        lookUpTable lut;
        for(auto i = begin+channel ; i != end+channel  ; i+=(image.getChannels())){
            lut.insert(std::pair(*i, *i));
        }
        return lut;
    }


    static lookUpTable& linearNormalization(lookUpTable& lut, std::pair<uchar, uchar> const& start, std::pair<uchar, uchar> const& end){
        auto min = lut.lower_bound(start.first);
        auto max = (lut.upper_bound(end.first));
        uchar minVal = min->first;
        if( max != lut.begin()) --max;
        uchar maxVal = max->first;
        if(minVal < maxVal && minVal>= start.first && maxVal <= end.first) {
            auto const norm = static_cast<double>(end.second - start.second)/ (maxVal - minVal);
            auto const endFor = ++(lut.find(maxVal));
            for (auto i = lut.find(minVal); i != endFor;  ++i) {
                i->second   = norm * (i->first - minVal)  + start.second;
            }
        }
        return lut;

    }

    static void display(pointsContainer const& points){
        std::cout << "( in" << "\tout )\n";
        for(auto i : points){
            std::cout << "( " << (int)i.first << "\t" << (int)i.second << " )\n";
        }
    }


};


#endif //IMAGEPROCESSING_NORMALIZATION_HPP
