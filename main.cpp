#include "ImageProcessor.hpp"
#include "Opening.hpp"
#include <opencv2/highgui.hpp>
#include <string>
#include <iostream>
#include <ImageEntropy.hpp>
#include <Complement.hpp>
#include <Filling.hpp>
#include <Normalization.hpp>


using namespace std::string_literals;

int main() {
//    auto const path2 = "/home/student/Pobrane/nowe.bmp"s;
//    auto const path = "/home/student/Pobrane/simpleColor.png"s;
//    auto const path = "/home/student/Desktop/saturn.png"s;
//    auto const path = "/home/student/Desktop/bag.png"s;
//    auto const path = "/home/student/Desktop/circles.png"s;
//    auto const path = "/home/student/Pobrane/wzorek.bmp"s;
//    auto const path = "/home/student/Desktop/pout.tif"s;
    auto const path = "/home/student/Desktop/onion.png"s;
//    auto const path = "/home/student/Desktop/kolorki.png"s;
//    auto const path = "/home/student/CLionProjects/ImageProcessing/Images/guinea.jpg"s;
    auto im = Image::factory(path, "infile"s).value_or(Image());
    im.display();
//    cv::Mat mat =  cv::imread(path, 0);
//    cv::erode(mat,mat,cv::getStructuringElement(2,cv::Size(3,3),cv::Point(1,1)));
//    cv::dilate(mat,mat,cv::getStructuringElement(2,cv::Size(3,3),cv::Point(1,1)));
//    cv::resize(mat, mat, cv::Size(), 10, 10);

    Image in(im, "In"s );
//    auto out2 = Image::factory(path2, "entropy").value_or(Image());
    Image out(im, "outfile"s );

    Image out2(1, im.getWidth(), im.getHeight(),  "entropy");



//    Opening opening(1);
//    opening.compute(out);
//    out.display();

//    Filling::compute(out);
//    out.display();
//    cv::imshow("correct opening", mat);
//


//    Normalization::pointsContainer points;
//    points.push_back(std::make_pair(0.4*255,0));
//    points.push_back(std::make_pair(0.7*255,255));
//    points.push_back(std::make_pair(120,200));
//    points.push_back(std::make_pair(250,180));

//    std::sort(points.begin() , points.end());
//    Normalization norm(points);
//    norm.compute(out);
//    out.display();
//
    ImageEntropy ie;
    ie.compute(in, out2);
    out2.display();
    cv::waitKey(0);
    return 0;
}