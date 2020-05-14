#include "ImageProcessor.hpp"
#include "Opening.hpp"
#include <opencv2/highgui.hpp>
#include <string>
#include <iostream>


using namespace std::string_literals;

int main() {
    auto const path = "/home/student/Desktop/circles.png"s;
    auto im = Image::factory(std::move(path)).value_or(Image());
//    im.display();

    auto out(im);
    Opening opening(1);
    opening.compute(out);
    out.display();
    cv::waitKey();
    return 0;
}