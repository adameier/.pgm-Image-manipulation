#define CATCH_CONFIG_MAIN
#include "Image.h"
#include "catch.hpp"

using namespace MRXADA002;

int cols = 5, rows = 5;

std::vector<int> originalImage{145, 140, 135, 130, 125,
                               140, 135, 130, 125, 120,
                               135, 130, 125, 120, 115,
                               130, 125, 120, 115, 110,
                               125, 120, 115, 110, 105};

//use threshold of 125 on originalImage
std::vector<int> t1{255, 255, 255, 255,   0,
                    255, 255, 255,   0,   0,
                    255, 255,   0,   0,   0,
                    255,   0,   0,   0,   0,
                      0,   0,   0,   0,   0};

//invert originalImage
std::vector<int> i1{110, 115, 120, 125, 130,
                    115, 120, 125, 130, 135,
                    120, 125, 130, 135, 140,
                    125, 130, 135, 140, 145,
                    130, 135, 140, 145, 150};

//mask originalImage with t1
std::vector<int> m1{145, 140, 135, 130,   0,
                    140, 135, 130,   0,   0,
                    135, 130,   0,   0,   0,
                    130,   0,   0,   0,   0,
                      0,   0,   0,   0,   0};

//add originalImage and m1
std::vector<int> a1{255, 255, 255, 255, 125,
                    255, 255, 255, 125, 120,
                    255, 255, 125, 120, 115,
                    255, 125, 120, 115, 110,
                    125, 120, 115, 110, 105};

//subtract i1 from originalImage
std::vector<int> s1{ 35,  25,  15,   5,   0,
                     25,  15,   5,   0,   0,
                     15,   5,   0,   0,   0,
                      5,   0,   0,   0,   0,
                      0,   0,   0,   0,   0};

TEST_CASE("EQUALITY OPERATOR FOR IMAGE") {
    std::cout << "Testing equality operator for Image." << '\n';
    Image image1(cols, rows, originalImage);
    Image image2(cols, rows, originalImage);
    REQUIRE(image1==image2);
}
