//
// Created by Just on 09.12.2023.
//

#ifndef INC_22202_ROZHKOV_OOP_CPP_TASK_3_CONVERTERMUTEFABRIC_H
#define INC_22202_ROZHKOV_OOP_CPP_TASK_3_CONVERTERMUTEFABRIC_H

#include "ConverterFabric.h"
#include "ConverterMute.h"

class ConverterMuteFabric : public ConverterFabric {
private:
    unsigned int secondStart;
    unsigned int secondEnd;
public:
    ConverterMuteFabric(unsigned int s, unsigned int e);
    Converter* getConverter() override;
    std::string getHelp() override;
};
#endif //INC_22202_ROZHKOV_OOP_CPP_TASK_3_CONVERTERMUTEFABRIC_H
