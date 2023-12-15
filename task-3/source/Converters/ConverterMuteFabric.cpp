//
// Created by Just on 09.12.2023.
//
#include "../../header/Converters/ConverterMuteFabric.h"

Converter *ConverterMuteFabric::getConverter() {
    return new ConverterMute(this->secondStart, this->secondEnd);
}

ConverterMuteFabric::ConverterMuteFabric(unsigned int s, unsigned int e) {
    this->secondStart = s;
    this->secondEnd = e;
}

std::string ConverterMuteFabric::getHelp() {
    //todo: help
    return std::string();
}

