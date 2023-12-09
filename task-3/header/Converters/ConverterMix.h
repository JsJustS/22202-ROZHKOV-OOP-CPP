//
// Created by Just on 09.12.2023.
//

#ifndef INC_22202_ROZHKOV_OOP_CPP_TASK_3_CONVERTERMIX_H
#define INC_22202_ROZHKOV_OOP_CPP_TASK_3_CONVERTERMIX_H

#include "Converter.h"

class ConverterMix : public Converter {
private:
    unsigned int startSampleId;
    unsigned int lastSampleId;
    unsigned int currentSampleId;
    unsigned int sideStreamId;
public:
    ConverterMix(unsigned int sideStreamId, unsigned int secondStart, unsigned int secondEnd);
    std::string getHelp() override;
    Sample modify(int size, Sample* samples) override;
};
#endif //INC_22202_ROZHKOV_OOP_CPP_TASK_3_CONVERTERMIX_H
