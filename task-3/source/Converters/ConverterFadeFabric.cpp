//
// Created by Just on 09.12.2023.
//
#include "../../header/Converters/ConverterFadeFabric.h"

ConverterFadeFabric::ConverterFadeFabric(unsigned int s, unsigned int e, int k, bool isIn) {
    this->secondStart = s;
    this->secondEnd = e;
    this->coef = k;
    this->isIn = isIn;
}

Converter *ConverterFadeFabric::getConverter() {
    return new ConverterFade(this->secondStart, this->secondEnd, this->coef, this->isIn);
}
