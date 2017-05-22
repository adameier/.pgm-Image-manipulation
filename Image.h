
namespace MRXADA002 {
    class Image {
    private:
        friend class iterator;

        int width, height;
        std::unique_ptr<unsigned char[]> data;

    public:
        class iterator {
        private:
            unsigned char *ptr;

            iterator(unsigned char *p); //constructor, used by image class

        public:

            iterator(const iterator &rhs); //iterator copy constructor

            iterator & operator=(const iterator &rhs); //copy assignment operator

            iterator & operator++(void); //prefix increment

            iterator & operator--(void); //prefix decrement

            unsigned char & operator*(void); //dereference operator


        }

        iterator begin(void); //get start iterator of Image

        iterator end(void); //get end iterator of Image
    }
}
