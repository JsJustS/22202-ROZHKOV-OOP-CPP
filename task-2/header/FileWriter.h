//
// Created by Just on 18.11.2023.
//

#ifndef INC_22202_ROZHKOV_OOP_CPP_FILEWRITER_H
#define INC_22202_ROZHKOV_OOP_CPP_FILEWRITER_H

#include <string>
#include <fstream>
#include <iostream>

/**
 * Dumps game states to the specified file
 * */
class FileWriter {
private:
    std::string filename;
    std::ofstream f;
public:
    explicit FileWriter(std::string fname): filename(std::move(fname)) {
    }

    ~FileWriter();

    void open();

    void write(const std::string& text);

    void writeLine(const std::string& text, bool isEnd=false);

    void close();

    void reset();

    bool isOpen();
};
#endif //INC_22202_ROZHKOV_OOP_CPP_FILEWRITER_H
