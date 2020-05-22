//
// Created by student on 13.05.2020.
//

#ifndef IMAGEPROCESSING_KERNELGENERATOR_HPP
#define IMAGEPROCESSING_KERNELGENERATOR_HPP

#include <vector>
#include <iostream>
#warning remove include iostream


struct Kernel {
    std::vector<uchar> data{};
    size_t radius{0};
};

class KernelGenerator {
    public:

    static Kernel generate(Image::storage_container& data, size_t size){
        Kernel k{ data, size};
        return k;
    }

    static Kernel generate(intmax_t r, std::string&& type = "circle") noexcept {
        Kernel tmp;
        if(std::numeric_limits<decltype(r)>::max() / r >= r) {
            if( type == "circle") {
                tmp.radius = r;
                tmp.data.reserve((2 * r + 1) * (2 * r + 1));
                for (auto y = -r; y <= r; ++y) {
                    for (auto x = -r; x <= r; ++x) {
                        tmp.data.push_back(((x * x) + (y * y) <= (r * r)) ? 255 : 0);
                    }
                }
            }else{
                tmp.radius = r;
                tmp.data.assign(r*r, 0);
                for(auto i = 0 ; i < r ; ++i){
                    for(auto j = 0 ; j < r ; ++j){
                        if(i == 0 || i == r-1 || j == 0 || j == r-1){
                            tmp.data[i*r+j] = 255;
                        }
                    }
                }

            }
        }
        return tmp;
    }

//    static Kernel generate(size_t r) noexcept {
//        Kernel kernel;
//        kernel.radius=r;
//        for(auto x = 0 ; x < 2 * r + 1; ++x){
//            for(auto y = 0 ; y < 2 * r + 1; ++y){
//                    kernel.data.push_back(((x - r) * (x - r) + (y - r) * (y - r) <= (r)*(r)) ? 255 : 0);
//            }
//        }
//        return kernel;
//    }


    static void display(Kernel const& k) {
        int x = 0;
        for( auto i : k.data){
            std::cout << (int)i <<  "\t";
            if( !(++x % (2*k.radius+1) )) std::cout << "\n";
        }
    }

};


#endif