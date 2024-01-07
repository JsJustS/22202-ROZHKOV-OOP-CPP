//
// Created by Just on 15.12.2023.
//

#ifndef INC_22202_ROZHKOV_OOP_CPP_TASK_3_SOUNDPROCESSINGERROR_H
#define INC_22202_ROZHKOV_OOP_CPP_TASK_3_SOUNDPROCESSINGERROR_H

#include <exception>

class SoundProcessingError : virtual public std::exception {
public:
    const char* what() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_NOTHROW override {
        return "Error occurred while processing sound.";
    }
};
#endif //INC_22202_ROZHKOV_OOP_CPP_TASK_3_SOUNDPROCESSINGERROR_H
