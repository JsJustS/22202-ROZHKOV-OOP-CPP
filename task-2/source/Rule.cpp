//
// Created by Just on 19.11.2023.
//
#include <iostream>
#include "../header/Rule.h"

Rule::Rule() {
    this->setSize = 0;
    this->set = nullptr;
}

Rule::~Rule() {
    std::cout << "Deleting " + toString() << std::endl;
    delete [] this->set;
}

bool Rule::isApplicable(char numberOfCells) const{
    for (char i = 0; i < this->setSize; i++) {
        if (this->set[i] == numberOfCells) return true;
    }
    return false;
}

void Rule::add(char numberOfCells) {
    // if number is already in the ruleset, skip useless duplication
    if (isApplicable(numberOfCells)) return;

    if (this->set == nullptr) {
        this->set = new char[1];
    } else {
        char* newSet = new char[this->setSize+1];
        std::memcpy(newSet, this->set, sizeof(char) * this->setSize);
        delete [] this->set;
        this->set = newSet;
    }

    this->set[this->setSize] = numberOfCells;

    this->setSize++;
}

void Rule::remove(char numberOfCells) {
    // if number is not in the ruleset, do not even try to remove it
    if (!isApplicable(numberOfCells)) return;

    if (this->setSize == 1) {
        clear();
        return;
    }

    char index = 0;
    for (char i = 0; i < this->setSize; i++) {
        if (this->set[i] == numberOfCells) {
            index = i;
            break;
        }
    }

    char* newSet = new char[this->setSize-1];
    if (index != 0) {
        std::memcpy(newSet, this->set, sizeof(char) * index);
    }
    if (index != this->setSize-1) {
        std::memcpy(newSet + index, this->set + index + 1, sizeof(char) * (this->setSize - index -1));
    }
    delete [] this->set;
    this->set = newSet;

    this->setSize--;
}

void Rule::clear() {
    this->setSize = 0;
    delete [] this->set;
    this->set = nullptr;
}

std::string Rule::toString() const{
    std::string str = "Rule{";
    for (char i = 0; i < this->setSize - 1; i++) {
        str += std::to_string(this->set[i]) + ", ";
    }
    if (this->setSize - 1 >= 0) {
        str += std::to_string(this->set[this->setSize - 1]);
    }
    return str += "}";
}

bool Rule::isEmpty() const {
    return this->setSize == 0;
}
