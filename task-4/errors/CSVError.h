//
// Created by Just on 16.12.2023.
//

#ifndef INC_22202_ROZHKOV_OOP_CPP_TASK_4_CSVERROR_H
#define INC_22202_ROZHKOV_OOP_CPP_TASK_4_CSVERROR_H

#include <string>

class CSVError : virtual public std::exception {
private:
    const std::string message;

public:
    CSVError();
    explicit CSVError(std::string message);
    explicit CSVError(unsigned int line, std::string message);
    explicit CSVError(unsigned int line, unsigned int col, std::string message);

    const char* what() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_NOTHROW override;
    int code() const;
};

#endif //INC_22202_ROZHKOV_OOP_CPP_TASK_4_CSVERROR_H
