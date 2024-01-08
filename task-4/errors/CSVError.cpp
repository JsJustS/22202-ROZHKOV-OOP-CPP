//
// Created by Just on 16.12.2023.
//

#include "CSVError.h"

#include <utility>

CSVError::CSVError() : message("General exception while parsing CSV file.") {}

CSVError::CSVError(std::string message) : message(std::move(message)) {}

const char *CSVError::what() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_NOTHROW {
    return this->message.c_str();
}

int CSVError::code() const {
    return 1;
}

CSVError::CSVError(unsigned int line, std::string message)
: message("Line " + std::to_string(line) +  ": " + std::move(message)) {}

CSVError::CSVError(unsigned int line, unsigned int col, std::string message)
: message("Line " + std::to_string(line) + ", Column " + std::to_string(col) + ": " + std::move(message)) {}
