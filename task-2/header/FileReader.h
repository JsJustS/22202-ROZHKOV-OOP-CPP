//
// Created by Just on 18.11.2023.
//

#ifndef TASK_2_FILEREADER_H
#define TASK_2_FILEREADER_H

#include <utility>
#include <string>
#include <iostream>
#include <fstream>

/**
 * Reads game files
 * */
class FileReader {
private:
    std::string filename;
    std::ifstream f;
public:
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
#endif //TASK_2_FILEREADER_H
