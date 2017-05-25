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


TEST_CASE("ITERATORS") {
    Image image(cols, rows, originalImage);
    std::cout << "Testing iterator.begin() and * operator." << '\n';
    Image::iterator beg = image.begin();
    REQUIRE(*beg==145);
    std::cout << "Testing iterator ++ operator." << '\n';
    ++beg;
    REQUIRE(*beg==140);
    std::cout << "Testing iterator.end() and -- operator." << '\n';
    Image::iterator end = image.end();
    --end;
    REQUIRE(*end==105);
    std::cout << "Testing iterator copy constructor." << '\n';
    Image::iterator endcopy(end);
    REQUIRE(*endcopy==105);
    std::cout << "Testing iterator copy assignment operator." << '\n';
    Image::iterator endcopy2 = end;
    REQUIRE(*endcopy2==105);
}

TEST_CASE("EQUALITY OPERATOR FOR IMAGE") {
    std::cout << "Testing equality operator for Image." << '\n';
    Image image1(cols, rows, originalImage);
    Image image2(cols, rows, originalImage);
    REQUIRE(image1==image2);
}

TEST_CASE("IMAGE MOVE SEMANTICS") {
    std::cout << "Testing Image move assignment operator." << '\n';
    Image image1(cols, rows, originalImage);
    Image image2(cols, rows, originalImage);
    Image image3 = std::move(image2);
    REQUIRE(image1==image3);
    std::cout << "Testing Image move constructor." << '\n';
    Image image4(std::move(image3));
    REQUIRE(image1==image4);
}

TEST_CASE("IMAGE COPY SEMANTICS") {
    std::cout << "Testing Image copy assignment operator." << '\n';
    Image image1(cols, rows, originalImage);
    Image image2 = image1;
    REQUIRE(image1==image2);
    std::cout << "Testing Image copy constructor." << '\n';
    Image image3(image1);
    REQUIRE(image1==image3);
}

TEST_CASE("THRESHOLD, MASK, ADD") {
    std::cout << "Testing threshold operation on Image." << '\n';
    Image image1(cols, rows, originalImage);
    Image image2 = image1*125; //create mask using threshold, should give t1 values
    Image image3(cols, rows, t1);
    REQUIRE(image2==image3);
    std::cout << "Testing mask operation on Image." << '\n';
    Image image4 = image1/image3; //mask originalImage with mask created with threshold, should give m1 values
    Image image5(cols, rows, m1);
    REQUIRE(image4==image5);
    std::cout << "Testing addition operation on Image." << '\n';
    Image image6 = image1 + image5; //add masked image to originalImage, should give a1 values
    Image image7(cols, rows, a1);
    REQUIRE(image6==image7);
}

TEST_CASE("INVERT, SUBTRACT") {
    std::cout << "Testing inversion operation on Image." << '\n';
    Image image1(cols, rows, originalImage);
    Image image2 = !image1;       //invert originalImage, should give i1 values
    Image image3(cols, rows, i1);
    REQUIRE(image2==image3);
    std::cout << "Testing subtraction operation on Image." << '\n';
    Image image4 = image1 - image3;
    Image image5(cols, rows, s1);
    REQUIRE(image4==image5);
}

TEST_CASE("LOAD, SAVE") {
    std::cout << "-loading image..." << '\n';
    Image image1;
    image1.load("Lenna_standard.pgm");
    std::cout << "-saving image..." << '\n';
    image1.save("output/saved.pgm", "saved");
    std::cout << "-loading saved image..." << '\n';
    Image image2;
    image2.load("output/saved.pgm");
    std::cout << "Testing if loaded images are the same." << '\n';
    REQUIRE(image1==image2);
}
