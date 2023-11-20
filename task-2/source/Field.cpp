//
// Created by Just on 18.11.2023.
//
#include <iostream>
#include "../header/Field.h"

void Field::init(int w, int h, std::vector<std::pair<int, int>> coords) {
    if (this->cells != nullptr) {throw std::runtime_error("Trying to reinitialize");}
    this->width = w;
    this->height = h;
    this->cells = new bool[w*h];

    for (int i = 0; i < w; i++) {
        for (int j = 0; j < h; j++) {
            setCell(i, j, false);
        }
    }

    for (std::pair<int, int> pair : coords) {
        setCell(pair.first, pair.second, true);
    }
}

void Field::setCell(int x, int y, bool isAlive) {
    int cellX = x % this->width;
    int cellY = y % this->height;
    this->cells[cellY*this->height + cellX] = isAlive;
}

bool Field::getCell(int x, int y) {
    int cellX = x % this->width;
    int cellY = y % this->height;
    return this->cells[cellY*this->height + cellX];
}

Field::~Field() {
    delete [] this->cells;
}

Field::Field() {
    this->width = 0;
    this->height = 0;
    this->cells = nullptr;
}

std::string Field::toString() {
    std::string string = "Field{width=" + std::to_string(this->width);
    string += ", height=" + std::to_string(this->height);
    string += ", array={";
    for (int x = 0; x < this->width; x++) {
        string += "[";
        for (int y = 0; y < this->height; y++) {
            string += (getCell(x, y)) ? "⬜" : "⬛";
        }
        string += "]";
    }

    return string += "}}";
}
