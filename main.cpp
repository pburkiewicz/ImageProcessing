#include <iostream>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <string>
using namespace cv;
int main() {
    std::string filename;
    std::cout << "Add file name\n";
    //std::cin >> filename;
    Mat x = imread("/home/student/Desktop/circles.png");
    std::cout << x.type()<< " " << x.channels();

    imshow("image", x);
    waitKey();
    return 0;
}