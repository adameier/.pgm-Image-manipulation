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

unsigned char & iterator::operator*(void) {
    return *ptr;
}

//DEFINITIONS for Image
