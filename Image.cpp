#include "Image.h"
#include <fstream>
#include <istream>
#include <sstream>

using namespace MRXADA002;

//DEFINITIONS FOR iterator

iterator::iterator(unsigned char *p) : ptr(p) {} //constructor used by Image

iterator::iterator(const iterator & rhs) : ptr(rhs.ptr) {} //copy constructor

iterator & iterator::operator=(const iterator & rhs) { //copy assignment operator
    ptr(rhs.ptr);
    return *this;
}

iterator & iterator::operator++(void) { //increment pointer
    ptr +=1;
    return *this;
}

iterator & iterator::operator--(void) { //decrement pointer
    ptr -=1;
    return *this;
}

unsigned char & iterator::operator*(void) { //dereference iterator
    return *ptr;
}


//DEFINITIONS for Image

//get iterators for beginning and end of data
iterator Image::begin() {
    return iterator(data.get());
}
iterator Image::end() {
    return iterator(data.get()+(width*height));
}

//default constructor
Image::Image() : width(0), height(0) {}

//copy constructor
Image::Image(const Image & rhs) : width(rhs.width), height(rhs.height) {
    data = std::make_unique<unsigned char[]>(width*height); //using unique ptrs, have to copy from rhs data into lhs data

    Image::iterator beg=this->begin(), end=this->end();
    Image::iterator inBeg=this->begin(), inStart=this->end();

    while (beg!=end) {
        *beg = *inStart;
        ++beg; ++inStart;
    }
}

//move constructor, can just move rhs.data into lhs data
Image::Image(Image && rhs) : width(rhs.width), height(rhs.height), data(std::move(rhs.data)) {}

//copy assignment operator
Image & Image::operator=(const Image & rhs) {
    width = rhs.width;
    height = rhs.height;

    data = std::make_unique<unsigned char[]>(width*height); //using unique ptrs, have to copy from rhs data into lhs data

    Image::iterator beg=this->begin(), end=this->end();
    Image::iterator inBeg=this->begin(), inStart=this->end();

    while (beg!=end) {
        *beg = *inStart;
        ++beg; ++inStart;
    }
    return *this;
}

//move assignment operator
Image & Image::operator=(Image && rhs) {
    width = rhs.width;
    height = rhs.height;
    data = std::move(rhs.data);
    return *this;
}

Image::~Image() = default;

void Image::load(std::string filename) {
    const char * cfilename = filename.c_str();
    std::ifstream pgm(cfilename, std::ios::binary);

    std::string line;
    std::getLine(pgm, line);
    while (true) {
        if (line!="P5" || line.at(0)!='#') //used for discarding "P5" and comment lines
            break;
        std::getLine(pgm, line);
    }
    //line will now have height and width
    std::stringstream ss; //used to get height and width from line
    ss.str(line);
    ss >> height >> width >> std::ws;
    std::getLine(pgm, line); //discard next line "255"
    pgm >> std::ws;   //extract all whitespace until data block

    data = std::make_unique<unsigned char[]>(width*height);

    pgm.read(data.get(), width*height);

    pgm.close();

}

void Image::save(std::string filename) {
    const char * cfilename = filename.c_str();
    std::ofstream pgm(cfilename, std::ios::binary);
}
