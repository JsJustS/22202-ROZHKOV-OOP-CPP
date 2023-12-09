//
// Created by Just on 09.12.2023.
//

#ifndef INC_22202_ROZHKOV_OOP_CPP_TASK_3_CONVERTERREVERB_H
#define INC_22202_ROZHKOV_OOP_CPP_TASK_3_CONVERTERREVERB_H

#define SAMPLE_PER_SPSEC 4410

#include "Converter.h"
/**
 * Adds reverb to the sound
 * */
class ConverterReverb : public Converter {
private:
    unsigned int echoCount;
    int* delayedSamples;
    int delaySize;
public:
    ~ConverterReverb() override;
    explicit ConverterReverb(unsigned int echoCount);
    std::string getHelp() override;
    Sample modify(int size, Sample* samples) override;
};
#endif //INC_22202_ROZHKOV_OOP_CPP_TASK_3_CONVERTERREVERB_H
