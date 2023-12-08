//
// Created by Just on 02.12.2023.
//

#ifndef TASK_3_CONVERTER_H
#define TASK_3_CONVERTER_H
/**
 * Abstract interface for Converters.
 * */

#include "Sample.h"

class Converter {
public:
    virtual ~Converter()= default;
    virtual std::string getHelp() = 0;
    virtual Sample modify(int size, Sample* samples) = 0;
};
#endif //TASK_3_CONVERTER_H
