//
// Created by Just on 09.12.2023.
//

#ifndef INC_22202_ROZHKOV_OOP_CPP_TASK_3_CONVERTERMUTE_H
#define INC_22202_ROZHKOV_OOP_CPP_TASK_3_CONVERTERMUTE_H

#include "Converter.h"

class ConverterMute : public Converter {
private:
    int startSampleId;
    int lastSampleId;
    int currentSampleId;
public:
    ConverterMute(int startSample, int lastSample);
    std::string getHelp() override;
    Sample modify(int size, Sample* samples) override;
};
#endif //INC_22202_ROZHKOV_OOP_CPP_TASK_3_CONVERTERMUTE_H
