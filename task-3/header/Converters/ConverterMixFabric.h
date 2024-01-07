//
// Created by Just on 09.12.2023.
//

#ifndef INC_22202_ROZHKOV_OOP_CPP_TASK_3_CONVERTERMIXFABRIC_H
#define INC_22202_ROZHKOV_OOP_CPP_TASK_3_CONVERTERMIXFABRIC_H

#include "ConverterFabric.h"
#include "ConverterMix.h"

class ConverterMixFabric : public ConverterFabric {
private:
    unsigned int secondStart;
    unsigned int secondEnd;
    unsigned int sideStreamId;
public:
    ConverterMixFabric(unsigned int id, unsigned int s, unsigned int e);
    Converter* getConverter() override;
    std::string getHelp() override;
};
#endif //INC_22202_ROZHKOV_OOP_CPP_TASK_3_CONVERTERMIXFABRIC_H
