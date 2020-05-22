#include "ImageProcessor.hpp"
#include "Opening.hpp"
#include <opencv2/highgui.hpp>
#include <string>
#include <iostream>
#include <ImageEntropy.hpp>
#include <Complement.hpp>
#include <Filling.hpp>


using namespace std::string_literals;

int main() {
//    auto const path = "/home/student/Pobrane/nowe.bmp"s;
    auto const path = "/home/student/Desktop/circles.png"s;
//    auto const path = "/home/student/Pobrane/wzorek.bmp"s;
    auto im = Image::factory(std::move(path), "infile"s).value_or(Image());
    im.display();
//    cv::Mat mat =  cv::imread(path, 0);
//    cv::erode(mat,mat,cv::getStructuringElement(2,cv::Size(3,3),cv::Point(1,1)));
//    cv::dilate(mat,mat,cv::getStructuringElement(2,cv::Size(3,3),cv::Point(1,1)));
//    cv::resize(mat, mat, cv::Size(), 10, 10);


    Image out(im, "outfile"s );
//    Opening opening(1);
//    opening.compute(out);
//    out.display();

    Filling::compute(out);
    out.display();
//    cv::imshow("correct opening", mat);

    cv::waitKey(0);
    return 0;
}