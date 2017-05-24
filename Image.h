#ifndef IMAGE_H
#define IMAGE_H

#include <memory>
#include <string>

namespace MRXADA002 {
    class Image {
    private:
        friend class iterator;

        int width, height;
        std::unique_ptr<unsigned char[]> data;

    public:

        class iterator {
        private:
            friend class Image;
            unsigned char *ptr;

            iterator(unsigned char *p); //constructor, used ONLY by image class

        public:

            iterator(const iterator &rhs); //iterator copy constructor

            iterator & operator=(const iterator &rhs); //copy assignment operator

            iterator & operator++(void); //prefix increment

            iterator & operator--(void); //prefix decrement

            unsigned char & operator*(void); //dereference operator

            bool operator==(const iterator &rhs);

            bool operator!=(const iterator &rhs);


        };
        iterator begin(void); //get start iterator of Image
        iterator end(void); //get end iterator of Image

        Image();
        Image(const Image & rhs);
        Image(Image && rhs);
        Image & operator=(const Image & rhs);
        Image & operator=(Image && rhs);
        ~Image();

        void load(std::string filename);
        void save(std::string filename, std::string comment);



    };
}
#endif
