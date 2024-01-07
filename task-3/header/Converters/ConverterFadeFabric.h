//
// Created by Just on 09.12.2023.
//

#ifndef INC_22202_ROZHKOV_OOP_CPP_TASK_3_CONVERTERFADEFABRIC_H
#define INC_22202_ROZHKOV_OOP_CPP_TASK_3_CONVERTERFADEFABRIC_H

#include "ConverterFabric.h"
#include "ConverterFade.h"

class ConverterFadeFabric : public ConverterFabric {
private:
    unsigned int secondStart;
    unsigned int secondEnd;
    int coef;
    bool isIn;
public:
    explicit ConverterFadeFabric(unsigned int s, unsigned int e, int k, bool isIn);
    Converter* getConverter() override;
    std::string getHelp() override;
};
#endif //INC_22202_ROZHKOV_OOP_CPP_TASK_3_CONVERTERFADEFABRIC_H
