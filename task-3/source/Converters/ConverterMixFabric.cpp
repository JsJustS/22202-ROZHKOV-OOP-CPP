//
// Created by Just on 09.12.2023.
//
#include "../../header/Converters/ConverterMixFabric.h"

ConverterMixFabric::ConverterMixFabric(unsigned int id, unsigned int s, unsigned int e) {
    this->sideStreamId = id;
    this->secondStart = s;
    this->secondEnd = e;
}

Converter *ConverterMixFabric::getConverter() {
    return new ConverterMix(this->sideStreamId, this->secondStart, this->secondEnd);
}

std::string ConverterMixFabric::getHelp() {
    //todo: help
    return std::string();
}

