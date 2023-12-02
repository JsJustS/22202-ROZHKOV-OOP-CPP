//
// Created by Just on 18.11.2023.
//
#include "../header/Field.h"

void Field::load(std::vector<std::pair<int, int>> coords) {
    if (this->cells == nullptr) {
        this->cells = new bool[this->width * this->height];

        for (int i = 0; i < this->width; i++) {
            for (int j = 0; j < this->height; j++) {
                setCell(i, j, false);
            }
        }
    }

    for (std::pair<int, int> pair : coords) {
        setCell(pair.first, pair.second, true);
    }
}

void Field::setCell(int x, int y, bool isAlive) {
    int cellX = x % this->width;
    if (cellX < 0) {
        cellX += this->width;
    }
    int cellY = y % this->height;
    if (cellY < 0) {
        cellY += this->height;
    }
    this->cells[cellY*this->width + cellX] = isAlive;
}

bool Field::getCell(int x, int y) {
    int cellX = x % this->width;
    if (cellX < 0) {
        cellX += this->width;
    }
    int cellY = y % this->height;
    if (cellY < 0) {
        cellY += this->height;
    }
    return this->cells[cellY*this->width + cellX];
}

Field::~Field() {
    delete [] this->cells;
}

Field::Field() {
    this->width = 0;
    this->height = 0;
    this->cells = nullptr;
}

Field::Field(int w, int h) {
    this->width = w;
    this->height = h;
    this->cells = new bool[w*h];

    for (int i = 0; i < w; i++) {
        for (int j = 0; j < h; j++) {
            setCell(i, j, false);
        }
    }
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

char Field::countAliveNeighbours(int x, int y) {
    char count = 0;
    for (char dx = -1; dx < 2; dx++) {
        for (char dy = -1; dy < 2; dy++) {
            if ((dx != 0 || dy != 0) && this->getCell(x + dx, y + dy)) {
                count++;
            }
        }
    }
    return count;
}

Field &Field::operator= (const Field &other) {
    if (this == &other) return *this;

    if (this->width * this->height != other.width * other.height) {
        this->width = other.width;
        this->height = other.height;
        delete [] this->cells;
        this->cells = new bool[this->width*this->height];
    }
    std::copy(other.cells, other.cells + other.width*other.height, this->cells);
    return *this;
}
