//
// Created by Just on 18.11.2023.
//

#include "../header/FileReader.h"

void FileReader::open() {
    f.open(filename);
}

bool FileReader::hasNext() {
    return f.peek() != EOF;
}

std::string FileReader::next() {
    std::string line;
    std::getline(f, line);
    return line;
}

void FileReader::close() {
    f.close();
}

void FileReader::reset() {
    f.clear();
    f.seekg(0);
}

bool FileReader::isOpen() {
    return f.is_open();
}

bool FileReader::isOk() {
    return !f.bad() && !f.fail();
}
