//
// Created by student on 13.05.2020.
//

#ifndef IMAGEPROCESSING_IMAGE_H
#define IMAGEPROCESSING_IMAGE_H

#include <opencv2/highgui.hpp>
#include <string>
#include <utility>
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

    Image(storage_container& data_, size_t channels_, size_t width_, size_t height_, std::string &&name_)
            : data(data_), channels(channels_), width(width_), height(height_), name(name_) { ; }

    Image(size_t channels_, size_t width_, size_t height_, std::string &&name_)
            : channels(channels_), width(width_), height(height_), name(name_) { ; }

    Image(Image i, std::string const &name_) : Image(std::move(i)) { name = name_; }

    Image(size_t width_, size_t height_, std::string&& name_, std::string&& type = "border") {
        channels = 1;
        width = width_;
        height = height_;
        name = name_;
        if (type == "border") {
            createBorderImage(*this);
        }
    }

    static std::optional<Image> factory(std::string const &filename, std::string const &name = {}) noexcept {
        auto mat = cv::imread(filename, CV_LOAD_IMAGE_UNCHANGED);
        if (mat.data != nullptr) {
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
            cv::imshow(name, tmp.reshape(channels, height));
        }
    }

    void save() const {
        cv::Mat tmp(data, true);
        cv::Mat tmp1 = tmp.reshape(channels, height);

        cv::imwrite( "../"+name+".png", tmp1 );
    }

    [[nodiscard]] auto getChannels() const { return channels; }

    [[nodiscard]] auto getWidth() const { return width; }

    [[nodiscard]] auto getHeight() const { return height; }

    [[nodiscard]] auto getName() const { return name; }

    Image &operator&=(Image const &image) {
        for (auto i = 0; i < image.data.size(); ++i) {
            data[i] &= image.data[i];
        }
        return *this;
    }

    bool operator==(Image const &image) {
        if (channels == image.getChannels() && width == image.getWidth() && height == image.getHeight()) {
            return data == image.data;
        }
        return false;
    }

    bool operator!=(Image const &image) {
        return !(*this == image);
    }

private:
    Image(std::vector<uchar>&& data_, size_t channels_, size_t width_, size_t height_, std::string const &name_)
            : data(std::move(data_)), channels(channels_), width(width_), height(height_), name(name_) {}

    void createBorderImage(Image& image) {
        size_t width = image.getWidth();
        size_t height = image.getHeight();
        image.data.assign(width * height, 0);
        for (auto i = 0; i < height; ++i) {
            for (auto j = 0; j < width; ++j) {
                if (i == 0 || i == height - 1 || j == 0 || j == width - 1) {
                    image.data[i * width + j] = 255;
                }
            }
        }
    }
};


#endif //IMAGEPROCESSING_IMAGE_H
