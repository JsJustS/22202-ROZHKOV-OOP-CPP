//
// Created by Just on 08.12.2023.
//

#ifndef INC_22202_ROZHKOV_OOP_CPP_TASK_3_CONVERTERFABRIC_H
#define INC_22202_ROZHKOV_OOP_CPP_TASK_3_CONVERTERFABRIC_H

#include "Converter.h"

class ConverterFabric {
public:
    virtual Converter* getConverter() = 0;
    virtual std::string getHelp() = 0;
};
#endif //INC_22202_ROZHKOV_OOP_CPP_TASK_3_CONVERTERFABRIC_H
