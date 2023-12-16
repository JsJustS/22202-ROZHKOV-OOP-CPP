//
// Created by Just on 15.12.2023.
//

#ifndef INC_22202_ROZHKOV_OOP_CPP_TASK_3_OUTOFRANGESTREAMIDERROR_H
#define INC_22202_ROZHKOV_OOP_CPP_TASK_3_OUTOFRANGESTREAMIDERROR_H

#include <string>
#include "SoundProcessingError.h"

class OutOfRangeStreamIdError : virtual public SoundProcessingError {
private:
    char* message;
public:
    explicit OutOfRangeStreamIdError(unsigned int id, unsigned int maximum) {
        std::string string = std::to_string(id);
        string += " id is bigger than maximum (";
        string += std::to_string(maximum) + ")";
        this->message = new char[string.size()];
        std::copy(string.begin(), string.end(), this->message);
    }
    
    ~OutOfRangeStreamIdError() override {
        delete [] this->message;
    }

    const char* what() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_NOTHROW override {
        return this->message;
    }
};
#endif //INC_22202_ROZHKOV_OOP_CPP_TASK_3_OUTOFRANGESTREAMIDERROR_H
