#include "ImageProcessor.hpp"
#include "Opening.hpp"
#include <opencv2/highgui.hpp>
#include <string>
#include <iostream>


using namespace std::string_literals;

int main() {
//    auto const path = "/home/student/Pobrane/nowe.bmp"s;
    auto const path = "/home/student/Desktop/circles.png"s;
    auto im = Image::factory(std::move(path), "infile"s).value_or(Image());
//    im.display();
    cv::Mat mat =  cv::imread(path, 0);
    cv::erode(mat,mat,cv::getStructuringElement(2,cv::Size(3,3),cv::Point(1,1)));
    cv::resize(mat, mat, cv::Size(), 2, 2);
    cv::imshow("name", mat);
    im.display();
    Image out(im, "outfile"s );
//    out.display();
    Erosion opening(1);
    opening.compute(out);
    out.display();
    cv::waitKey(0);
    return 0;
}