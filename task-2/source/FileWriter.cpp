//
// Created by Just on 18.11.2023.
//
#include "../header/FileWriter.h"

void FileWriter::open() {
    this->f = std::ofstream(this->filename);
}

void FileWriter::write(const std::string &text) {
    this->f << text;
}

void FileWriter::writeLine(const std::string &text, bool isEnd) {
    this->f << text;
    if (!isEnd) {
        this->f << std::endl;
    }
}

void FileWriter::close() {
    this->f.close();
}

bool FileWriter::isOpen() {
    return this->f.is_open();
}

void FileWriter::reset() {
    this->f.seekp(0, std::ios_base::beg);
}

FileWriter::~FileWriter() {
    if (this->isOpen()) {
        this->close();
    }
}
