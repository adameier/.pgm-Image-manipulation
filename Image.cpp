#include "Image.h"


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
Image::iterator Image::begin() const {
    return Image::iterator(data.get());
}
Image::iterator Image::end() const {
    return Image::iterator(data.get()+(width*height));
}

//default constructor
Image::Image() : width(0), height(0) {}

//copy constructor
Image::Image(const Image & rhs) : width(rhs.width), height(rhs.height) {
    data = std::unique_ptr<unsigned char[]>(new unsigned char[width*height]); //using unique ptrs, have to copy from rhs data into lhs data

    Image::iterator beg=this->begin(), end=this->end();
    Image::iterator inStart=rhs.begin(), inEnd=rhs.end();

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
    Image::iterator inStart=rhs.begin(), inEnd=rhs.end();

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

//CONSTRUCTOR FOR TESTING
Image::Image(int cols, int rows, const std::vector<int> & v) : width(cols), height(rows) {
    data = std::unique_ptr<unsigned char[]>(new unsigned char[width*height]);
    int i=0;
    Image::iterator beg=this->begin(), end=this->end();
    while (beg!=end) {    //assign buffer of unsigned chars to data block
        *beg = v[i];
        ++beg; ++i;
    }
}

//== operator used for checking if 2 images hold same data
bool Image::operator==(const Image &rhs) {
    if (this->width!=rhs.width || this->height!=rhs.height)
        return false;

    Image::iterator beg=this->begin(), end=this->end();
    Image::iterator inStart=rhs.begin(), inEnd=rhs.end();

    while (beg!=end) {
        if (*beg != *inStart)
            return false;
        ++beg; ++inStart;
    }
    return true;
}

//IMAGE OPERATORS FOR FUNCTIONS
Image Image::operator+(const Image & rhs) { //add
    Image temp = *this;             //copy lhs Image into new and modify
    Image::iterator beg=temp.begin(), end=temp.end();
    Image::iterator inStart=rhs.begin(), inEnd=rhs.end();

    while (beg!=end) {
        if ((*beg + *inStart)>255)  //clamp value to 255 if above
            *beg = 255;
        else
            *beg = *beg + *inStart; //add lhs and rhs
        ++beg; ++inStart;
    }
    return temp;
}

Image Image::operator-(const Image & rhs) { //subtract
    Image temp = *this;             //copy lhs Image into new and modify
    Image::iterator beg=temp.begin(), end=temp.end();
    Image::iterator inStart=rhs.begin(), inEnd=rhs.end();

    while (beg!=end) {
        if ((*beg - *inStart)<0)  //clamp value to 0 if below
            *beg = 0;
        else
            *beg = *beg - *inStart; //subtract rhs from lhs
        ++beg; ++inStart;
    }
    return temp;
}

Image Image::operator!(void) { //invert
    Image temp = *this;             //copy lhs Image into new and modify
    Image::iterator beg=temp.begin(), end=temp.end();

    while (beg!=end) {
        *beg = 255 - *beg; //set lhs val to 255 - lhs val
        ++beg;
    }
    return temp;
}

Image Image::operator/(const Image & rhs) { //mask
    Image temp = *this;             //copy lhs Image into new and modify
    Image::iterator beg=temp.begin(), end=temp.end();
    Image::iterator inStart=rhs.begin(), inEnd=rhs.end(); //rhs is the mask Image

    while (beg!=end) {
        if (*inStart!=255)
            *beg = 0;
        ++beg; ++inStart;
    }
    return temp;
}

Image Image::operator*(int rhs) { //threshold
    Image temp = *this;             //copy lhs Image into new and modify
    Image::iterator beg=temp.begin(), end=temp.end();

    while (beg!=end) {
        if (*beg > rhs)
            *beg = 255;
        else
            *beg = 0;
        ++beg;
    }
    return temp;
}

void Image::load(std::string filename) {
    const char * cfilename = filename.c_str();
    std::ifstream pgm(cfilename, std::ios::binary);

    std::string line;
    while (std::getline(pgm, line)) {
        if (line!="P5" && line.at(0)!='#') {
            break;
        } //used for discarding "P5" and comment lines
    }
    //line will now have height and width
    std::cout << line << '\n';
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
