//
// Created by Just on 02.12.2023.
//

#include "../header/Sample.h"

Sample::~Sample() {
    delete [] this->data;
}

Sample::Sample(uint16_t size) {
    this->size = size;
    this->data = new Byte[size];
}

void Sample::read(std::ifstream& stream) {
    stream.read(this->data, this->size);
}

void Sample::write(std::ofstream &stream) {
    stream.write(this->data, this->size);
}

void Sample::writeByte(std::ofstream &stream, Sample::Byte byte) {
    stream.write(reinterpret_cast<const char*>(&byte), 1);
}

uint16_t Sample::getSize() const {
    return this->size;
}

Sample &Sample::operator=(const Sample &otherSample) {
    if (this == &otherSample) {
        return *this;
    }

    this->size = otherSample.size;
    delete [] this->data;
    this->data = new Byte[this->size];
    for (int i = 0; i < this->size; ++i) {
        this->data[i] = otherSample.data[i];
    }

    return *this;
}

