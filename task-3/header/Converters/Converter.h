//
// Created by Just on 02.12.2023.
//

#ifndef TASK_3_CONVERTER_H
#define TASK_3_CONVERTER_H
/**
 * Abstract interface for Converters.
 * */

#include "../Sample.h"

#define SAMPLES_PER_SECOND 44100

class Converter {
public:
    virtual ~Converter()= default;
    virtual Sample modify(int size, Sample* samples) noexcept(false) = 0;
};
#endif //TASK_3_CONVERTER_H
