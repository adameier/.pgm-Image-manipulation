#include "Image.h"
#include <fstream>
#include <istream>
#include <sstream>

using namespace MRXADA002;

//DEFINITIONS FOR iterator

Image::iterator::iterator(unsigned char *p) : ptr(p) {} //constructor used by Image

Image::iterator::iterator(const iterator & rhs) : ptr(rhs.ptr) {} //copy constructor

Image::iterator & Image::iterator::operator=(const iterator & rhs) { //copy assignment operator
    ptr = rhs.ptr;
    return *this;
}

Image::iterator & Image::iterator::operator++(void) { //increment pointer
    ptr +=1;
    return *this;
}

Image::iterator & Image::iterator::operator--(void) { //decrement pointer
    ptr -=1;
    return *this;
}

unsigned char & Image::iterator::operator*(void) { //dereference iterator
    return *ptr;
}

bool Image::iterator::operator==(const iterator & rhs) {
    if (ptr==rhs.ptr)
        return true;
    else
        return false;
}

bool Image::iterator::operator!=(const iterator & rhs) {
    if (operator==(rhs))
        return false;
    else
        return true;
}


//DEFINITIONS for Image

//get iterators for beginning and end of data
Image::iterator Image::begin() {
    return Image::iterator(data.get());
}
Image::iterator Image::end() {
    return Image::iterator(data.get()+(width*height));
}

//default constructor
Image::Image() : width(0), height(0) {}

//copy constructor
Image::Image(const Image & rhs) : width(rhs.width), height(rhs.height) {
    data = std::unique_ptr<unsigned char[]>(new unsigned char[width*height]); //using unique ptrs, have to copy from rhs data into lhs data

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

    data.reset(new unsigned char[width*height]); //using unique ptrs, have to copy from rhs data into lhs data

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
    std::getline(pgm, line);
    while (true) {
        if (line!="P5" || line.at(0)!='#') //used for discarding "P5" and comment lines
            break;
        std::getline(pgm, line);
    }
    //line will now have height and width
    std::stringstream ss; //used to get height and width from line
    ss.str(line);
    ss >> height >> width >> std::ws;
    std::getline(pgm, line); //discard next line "255"
    pgm >> std::ws;   //extract all whitespace until data block

    data = std::unique_ptr<unsigned char[]>(new unsigned char[width*height]);

    pgm.read((char*)data.get(), width*height);

    pgm.close();

}

void Image::save(std::string filename, std::string comment) {
    const char * cfilename = filename.c_str();
    std::ofstream pgm(cfilename, std::ios::binary);

    pgm << "P5" << '\n';
    pgm << "# " << comment << '\n';
    pgm << height << " " << width << '\n';
    pgm << 255 << '\n';
    pgm.write((char*)data.get(), width*height);
    pgm.close();

}
