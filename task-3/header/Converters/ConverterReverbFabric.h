//
// Created by Just on 09.12.2023.
//

#ifndef INC_22202_ROZHKOV_OOP_CPP_TASK_3_CONVERTERREVERBFABRIC_H
#define INC_22202_ROZHKOV_OOP_CPP_TASK_3_CONVERTERREVERBFABRIC_H

#include "ConverterFabric.h"
#include "ConverterReverb.h"

class ConverterReverbFabric : public ConverterFabric {
private:
    unsigned int echoCount;
public:
    explicit ConverterReverbFabric(unsigned int c);
    Converter* getConverter() override;
};
#endif //INC_22202_ROZHKOV_OOP_CPP_TASK_3_CONVERTERREVERBFABRIC_H
