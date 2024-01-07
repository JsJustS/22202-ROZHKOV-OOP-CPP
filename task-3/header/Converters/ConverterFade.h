//
// Created by Just on 09.12.2023.
//

#ifndef INC_22202_ROZHKOV_OOP_CPP_TASK_3_CONVERTERFADE_H
#define INC_22202_ROZHKOV_OOP_CPP_TASK_3_CONVERTERFADE_H

#define SAMPLE_PER_SPSEC 4410

#include "Converter.h"
#include <cmath>

/**
 * Adds fading to the sound (in or out)
 * */
class ConverterFade : public Converter {
private:
    unsigned int startSampleId;
    unsigned int lastSampleId;
    unsigned int currentSampleId;
    double modifier;
    double delta;
    double coef;
    bool isIn;
    double easeFunc(double x);
public:
    explicit ConverterFade(unsigned int secondStart, unsigned int secondEnd, int k, bool isIn);
    Sample modify(int size, Sample* samples) noexcept(false) override;
};
#endif //INC_22202_ROZHKOV_OOP_CPP_TASK_3_CONVERTERFADE_H
