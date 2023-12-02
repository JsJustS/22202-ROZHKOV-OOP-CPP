//
// Created by Just on 02.12.2023.
//
#include <fstream>
#include "../header/WAVWrapper.h"

WAVWrapper::~WAVWrapper() {
    delete [] this->header;
    delete [] this->raw;
}

void WAVWrapper::readHeader(std::ifstream& stream) {
    this->header = new union HEADER_DATA;
    char *c = new char;
    for (int i = 0; i < HEADER_SIZE && stream.peek() != EOF; i++) {
        stream.read(c, 1);
        if (c == nullptr) {
            break;
        }
        this->header->data[i] = *c;
    }
    delete c;
}

WAVWrapper::WAVWrapper() {
    this->header = nullptr;
    this->offset = 0;
    this->raw = nullptr;
}

