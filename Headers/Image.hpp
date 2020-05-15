//
// Created by student on 13.05.2020.
//

#ifndef IMAGEPROCESSING_IMAGE_H
#define IMAGEPROCESSING_IMAGE_H
#include <opencv2/highgui.hpp>
#include <string>
#include <vector>
#include <optional>
#include <iostream>
#include <opencv2/imgproc.hpp>

class Image {
    friend class ImageProcessor; // Friendship and forward declaration

public:
    using storage_container = std::vector<uchar>;
protected:
    storage_container data{};
    size_t channels{0};
    size_t width{0};
    size_t height{0};
    std::string name{};
public:
    constexpr Image() noexcept = default;

    Image(Image const& i, std::string const& name_) : Image(i) {name = name_;}

    static std::optional<Image> factory(std::string const& filename, std::string const& name = {}) noexcept {
        auto mat = cv::imread(filename, CV_LOAD_IMAGE_ANYDEPTH );
        if(mat.data != nullptr) {
            storage_container data(mat.datastart, mat.dataend);
            auto channels = mat.channels(); // ?
            auto width = mat.cols;
            auto height = mat.rows;
            return Image(std::move(data), channels, width, height, name);
        }
        return {};
    }

    void display() const noexcept {
        cv::Mat tmp(data, true);
        if (tmp.data != nullptr) {
            static int i = 0 ;
            auto tmp1 = tmp.reshape(0, height);
            cv::Mat dst;
            cv::resize(tmp1, dst, cv::Size(), 2, 2); // upscale 2x

            cv::imshow(name, dst);
        }
    }

    auto getChannels() const noexcept {return channels;}
    auto getWidth() const noexcept {return width;}
    auto getHeigth() const noexcept {return height;}

private:
    Image(std::vector<uchar>&& data_, size_t channels_, size_t width_, size_t height_, std::string const& name_)
                : data(std::move(data_)), channels(channels_), width(width_), height(height_), name(name_) {}
};




#endif //IMAGEPROCESSING_IMAGE_H
