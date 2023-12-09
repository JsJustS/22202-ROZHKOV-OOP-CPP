//
// Created by Just on 09.12.2023.
//
#include "../../header/Converters/ConverterReverbFabric.h"

ConverterReverbFabric::ConverterReverbFabric(unsigned int c) {
    this->echoCount = c;
}

Converter *ConverterReverbFabric::getConverter() {
    return new ConverterReverb(this->echoCount);
}

