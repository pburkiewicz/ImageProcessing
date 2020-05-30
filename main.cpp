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
//    auto const path1 = "/home/student/Desktop/bag.png"s;
//    auto const path1 = "/home/student/Desktop/szara.jpg"s;
//    auto const path2 = "/home/student/Desktop/czarna.jpg"s;
//    auto const path3 = "/home/student/Desktop/kolorowa.jpg"s;
    auto const path2 = "/home/student/Desktop/dziury.bmp"s;
//    auto const path = "/home/student/Desktop/circles.png"s;
//    auto const path = "/home/student/Pobrane/wzorek.bmp"s;
    auto const path1 = "/home/student/Desktop/pout.tif"s;
//    auto const path = "/home/student/Desktop/AT3_1m4_02.tif"s;
//    auto const path1 = "/home/student/Desktop/blobs.png"s;
//    auto const path1 = "/home/student/Desktop/onion.png"s;
//    auto const path3 = "/home/student/Desktop/kolorki.png"s;
//    auto const path1 = "/home/student/CLionProjects/ImageProcessing/Images/guinea.jpg"s;
    auto im1 = Image::factory(path1, "infile"s).value_or(Image());
    auto im2 = Image::factory(path2, "infile"s).value_or(Image());
//    auto im3 = Image::factory(path3, "infile"s).value_or(Image());
//    auto im4 = Image::factory(path4, "infile"s).value_or(Image());

//
//    Kernel k = KernelGenerator::generate(5);
//    KernelGenerator::display(k);
//
    im1.display();
//    im2.display();
//    im3.display();
//    im4.display();
//
    Image out1(im1, "open1_15"s);
    Image out2(im2, "open2_15"s);
////
    Image out3(im1, "open1_1"s);
    Image out4(im2, "open2_1"s);

//    Image out1(1, im1.getWidth(),im1.getHeight(), "entropy1_9");
//    Image out2(1, im2.getWidth(),im2.getHeight(), "entropy2_9");
//    Image out3(1, im3.getWidth(),im3.getHeight(), "entropy3_9");
//    Image out4(1, im4.getWidth(),im4.getHeight(), "entropy7_3");

//    auto out2 = Image::factory(path2, "entropy").value_or(Image());
//    Image out2(1, im.getWidth(), im.getHeight(),  "entropy");
//    for(int i = 1 ; i < 15 ; ++i){
//        std::cout<< "Promien " << i << "\n";
//        Kernel k = KernelGenerator::generate(i);
//        KernelGenerator::display(k);
//        std::cout<< "\n\n";
//    }
//    Kernel k = KernelGenerator::generate(15);
//    auto se = cv::getStructuringElement(2,cv::Size(31,31),cv::Point(15,15));
//    std::memcpy(k.data.data() ,se.data, se.elemSize()*se.rows*se.cols);
//
//    KernelGenerator::display(k);
//    Erosion::compute(out,k);
//    out.display();
//    Dilation::compute(out, k);
//    out.display();
//    std::cout << "\n";
    Opening opening15(15);
    opening15.compute(out1);
    opening15.compute(out2);
    out1.display();
    out2.display();

    Opening opening1(1);
    opening1.compute(out3);
    opening1.compute(out4);
    out3.display();
    out4.display();

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

//
//    Filling::compute(out1);
//    Filling::compute(out2);



//    Normalization::pointsContainer points;
//    points.push_back(std::make_pair(0.5*255,0.1*255));
//    points.push_back(std::make_pair(0.6*255,0.3*255));
//    points.push_back(std::make_pair(0.75*255,0.5*255));
//    points.push_back(std::make_pair(0.8*255,0.75*255));
//
//    std::sort(points.begin() , points.end());
//    Normalization norm(points);
//    norm.compute(out1);
//    norm.compute(out2);
//    norm.compute(out3);

//    out1.display();
//    out2.display();
//    out3.display();
//


//
//    ImageEntropy::compute(im1, out1,9);
//    ImageEntropy::compute(im2, out2, 9);
//    ImageEntropy::compute(im3, out3, 9);
//    ImageEntropy::compute(im4, out4,3);


//    out1.display();
//    out2.display();
//    out3.display();
//    out4.display();
//
    out1.save();
    out2.save();
    out3.save();
    out4.save();
    cv::waitKey(0);



    return 0;
}