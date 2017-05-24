#include "Image.h"
#include <sstream>

using namespace MRXADA002;

int main(int argc, char** argv) {
    std::string flag = std::string(argv[1]);

    if (flag=="-a") {                               //add operation

        Image image1;
        Image image2;
        image1.load("shrek_rectangular.pgm");                             //load 2 files into image objects
        image2.load("shrek_rectangular.pgm");
        Image output(image1 + image2);                 //perform operation

        std::string outputName = std::string(argv[2]);
        std::string outputString = "output/"+ outputName +".pgm";
        output.save(outputString, "Addition");
    }

    else if (flag=="-s") {                          //subtract operation

        Image image1;
        Image image2;
        image1.load("shrek_rectangular.pgm");                             //load 2 files into image objects
        image2.load("donkey_mask.pgm");
        Image output(image1 - image2);                 //perform operation

        std::string outputName = std::string(argv[2]);
        std::string outputString = "output/"+ outputName +".pgm";
        output.save(outputString, "Subtraction");
    }
    return 0;
}
