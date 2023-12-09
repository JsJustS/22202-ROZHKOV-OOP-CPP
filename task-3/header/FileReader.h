//
// Created by Just on 08.12.2023.
//

#ifndef INC_22202_ROZHKOV_OOP_CPP_TASK_3_FILEREADER_H
#define INC_22202_ROZHKOV_OOP_CPP_TASK_3_FILEREADER_H
#include <string>
#include <iostream>
#include <fstream>

/**
 * Reads files, config as example
 * */
class FileReader {
private:
    std::string filename;
    std::ifstream f;
public:
    ~FileReader();
    explicit FileReader(std::string fname): filename(std::move(fname)) {
    }

    void open();

    std::string next();

    bool hasNext();

    void close();

    void reset();

    bool isOpen();

    bool isOk();
};
#endif //INC_22202_ROZHKOV_OOP_CPP_TASK_3_FILEREADER_H
