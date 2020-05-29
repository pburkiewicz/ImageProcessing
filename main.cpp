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
    auto const path = "/home/student/Desktop/AT3_1m4_02.tif"s;
//    auto const path = "/home/student/Desktop/onion.png"s;
//    auto const path = "/home/student/Desktop/kolorki.png"s;
//    auto const path = "/home/student/CLionProjects/ImageProcessing/Images/guinea.jpg"s;
    auto im = Image::factory(path, "infile"s).value_or(Image());
    im.display();
    cv::Mat mat = cv::imread(path, 0);
    cv::Mat mat2;
    cv::Mat mat3;

//    cv::erode(mat,mat2,cv::getStructuringElement(2,cv::Size(31,31),cv::Point(15,15)));
//    cv::dilate(mat2, mat3, cv::getStructuringElement(2, cv::Size(31, 31), cv::Point(15, 15)));
//    cv::dilate(mat,mat3,cv::getStructuringElement(2,cv::Size(20,20),cv::Point(10,10)));
//    cv::imshow("oryginal", mat3);
//    Image in(im, "In"s );


//    auto out2 = Image::factory(path2, "entropy").value_or(Image());
    Image out(im, "opening"s);
    Image out3(im, "dilation"s);
    Image out4(im, "erosiondilation"s);
//    Image out2(1, im.getWidth(), im.getHeight(),  "entropy");
//    for(int i = 1 ; i < 15 ; ++i){
//        std::cout<< "Promien " << i << "\n";
//        Kernel k = KernelGenerator::generate(i);
//        KernelGenerator::display(k);
//        std::cout<< "\n\n";
//    }
    Kernel k = KernelGenerator::generate(15);
//    auto se = cv::getStructuringElement(2,cv::Size(31,31),cv::Point(15,15));
//    std::memcpy(k.data.data() ,se.data, se.elemSize()*se.rows*se.cols);
//
//    KernelGenerator::display(k);
//    Erosion::compute(out,k);
//    out.display();
//    Dilation::compute(out, k);
//    out.display();
//    std::cout << "\n";
    Opening opening(15);
    opening.compute(out);
    out.display();
//
//    Erosion e(15);
//    e.compute(out);
//
//    Dilation d(15);
//    d.compute(out);
//    out.display();
////
//    Erosion e2(10);
//    e2.compute(out4);
//    Dilation d2(10);
//    d2.compute(out4);
//    out4.display();


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
//    ImageEntropy ie;
//    ie.compute(in, out2);
//    out2.display();
    cv::waitKey(0);
    return 0;
}