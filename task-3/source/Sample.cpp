//
// Created by Just on 02.12.2023.
//

#include <cstring>
#include "../header/Sample.h"

Sample::~Sample() {
    delete [] this->data;
}

Sample::Sample() {
    this->size = 2;
    this->data = new Byte[2];
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

Sample::Byte &Sample::operator[](int i) {
    return this->data[i];
}

Sample& Sample::saveAsInt(int16_t value) {
    std::memcpy(this->data, &value, sizeof(int16_t));
    //this->data = static_cast<char*>(static_cast<void*>(&(value)));
    return *this;
}

int16_t Sample::getAsInt() {
    int16_t value;
    std::memcpy(&value, this->data, sizeof(int16_t));
    return value;
}

Sample::Sample(const Sample &otherSample) {
    this->size = otherSample.size;
    this->data = new Byte[this->size];
    for (int i = 0; i < this->size; ++i) {
        this->data[i] = otherSample.data[i];
    }
}
