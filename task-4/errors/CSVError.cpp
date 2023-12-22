//
// Created by Just on 16.12.2023.
//

#include "CSVError.h"

#include <utility>

CSVError::CSVError() : message("General exception while parsing CSV file.") {
    this->_code = ERRCODE::GENERAL;
}

CSVError::CSVError(std::string message) : message(std::move(message)) {
    this->_code = ERRCODE::GENERAL;
}

const char *CSVError::what() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_NOTHROW {
    return this->message.c_str();
}

int CSVError::code() const {
    return this->_code;
}
