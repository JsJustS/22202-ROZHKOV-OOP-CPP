//
// Created by Just on 16.12.2023.
//

#ifndef INC_22202_ROZHKOV_OOP_CPP_TASK_3_FILEERROR_H
#define INC_22202_ROZHKOV_OOP_CPP_TASK_3_FILEERROR_H

#include <algorithm>
#include <string>
#include "SoundProcessingError.h"

class FileError : virtual public SoundProcessingError {
private:
    char* message;
public:
    explicit FileError(const std::string& message) {
        this->message = new char[message.size()];
        std::copy(message.begin(), message.end(), this->message);
    }

    ~FileError() override {
        delete [] this->message;
    }

    const char* what() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_NOTHROW override {
        return this->message;
    }
};
#endif //INC_22202_ROZHKOV_OOP_CPP_TASK_3_FILEERROR_H
