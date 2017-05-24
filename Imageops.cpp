#include "Image.h"
#include <sstream>

using namespace MRXADA002;

int main(int argc, char** argv) {
    std::string flag = std::string(argv[1]);

    if (flag=="-a") {                               //add operation
        std::stringstream ss;
        ss << argv[2] << " " << argv[3] << " " << argv[4]; //parsing args
        std::string imagefile1;
        std::string imagefile2;
        ss >> imagefile1;
        ss >> imagefile2;
        Image image1;
        Image image2;
        image1.load(imagefile1);                             //load 2 files into image objects
        image2.load(imagefile2);
        Image output(image1 + image2);                 //create new Image with performing operation

        std::string outputName;
        ss >> outputName;
        std::string outputString = "output/"+ outputName +".pgm";
        output.save(outputString, "Addition");
    }

    else if (flag=="-s") {                          //subtract operation
        std::stringstream ss;
        ss << argv[2] << " " << argv[3] << " " << argv[4]; //parsing args
        std::string imagefile1;
        std::string imagefile2;
        ss >> imagefile1;
        ss >> imagefile2;
        Image image1;
        Image image2;
        image1.load(imagefile1);                             //load 2 files into image objects
        image2.load(imagefile2);
        Image output(image1 - image2);                 //create new Image with performing operation

        std::string outputName;
        ss >> outputName;
        std::string outputString = "output/"+ outputName +".pgm";
        output.save(outputString, "Subtraction");
    }

    else if (flag=="-i") {                         //inversion operation
        std::stringstream ss;
        ss << argv[2] << " " << argv[3]; //parsing args
        std::string imagefile;
        ss >> imagefile;
        Image image;
        image.load(imagefile);                             //load file into image object
        Image output(!image);                           //create new Image with performing operation

        std::string outputName;
        ss >> outputName;
        std::string outputString = "output/"+ outputName +".pgm";
        output.save(outputString, "Inversion");
    }

    else if (flag=="-l") {                        //mask operation
        std::stringstream ss;
        ss << argv[2] << " " << argv[3] << " " << argv[4]; //parsing args
        std::string imagefile1;
        std::string imagefile2;
        ss >> imagefile1;
        ss >> imagefile2;
        Image image1;
        Image image2;
        image1.load(imagefile1);                             //load 2 files into image objects
        image2.load(imagefile2);
        Image output(image1/image2);                 //create new Image with performing operation

        std::string outputName;
        ss >> outputName;
        std::string outputString = "output/"+ outputName +".pgm";
        output.save(outputString, "Masking");
    }

    else if (flag=="-t") {                       //threshold operation


    }
    return 0;
}
