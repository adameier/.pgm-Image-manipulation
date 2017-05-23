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
