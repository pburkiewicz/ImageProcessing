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
        Image::storage_container& data = getData(image);
        display(points);
        lookUpTable lut = createLookUpTable(image);
        linearNormalization(lut,0, 255);
        for(auto& i : data){
            i = lut[i];
        }
        if(!points.empty()) {
            linearNormalization(lut, 0, points.begin()->second);
            for (auto pointIt = points.begin(); pointIt != points.end(); ++pointIt) {
                linearNormalization(lut, pointIt->second, (++pointIt)->second);
            }
            linearNormalization(lut,  points.end()->second, 255);
        }
        for(auto& i : data){
            i = lut[i];
        }
        return image;
    }



private:
    static lookUpTable createLookUpTable(Image& image){
        Image::storage_container data = getData(image);
        lookUpTable lut;
        for(auto& i : data){
            lut.insert(std::pair(i,i));
        }
        return lut;
    }


    static lookUpTable& linearNormalization(lookUpTable& lut, uchar const start, uchar const end){
        auto min = lut.lower_bound(start);
        auto max = (--lut.upper_bound(end));
        uchar minVal = min->first;
        uchar maxVal = max->first;

//        uchar min = std::min_element(lut.begin(), lut.end())->first;
//        uchar max = std::max_element(lut.begin(), lut.end())->first;
        for(auto i = lut.find(minVal); i != lut.find(maxVal) ; ++i){
            i->second = (end-start) * (i->first-minVal)/(maxVal-minVal)+start;
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
