//
// Created by Just on 19.09.2023.
//

#include "FileReader.h"

int main() {
    //std::cout << "# start" << std::endl;
    FileReader fileReader("test.txt");
    //std::cout << "# create instance" << std::endl;
    fileReader.open();
    //std::cout << "# open file" << std::endl;

    while (fileReader.hasNext()) {
        //std::cout << "# checked next" << std::endl;
        std::cout << fileReader.next() << std::endl;
    }
    //std::cout << "# again" << std::endl;
    fileReader.reset();
    while (fileReader.hasNext()) {
        std::cout << fileReader.next() << std::endl;
    }
    //std::cout << "# stop" << std::endl;
    fileReader.close();
    return 0;
}