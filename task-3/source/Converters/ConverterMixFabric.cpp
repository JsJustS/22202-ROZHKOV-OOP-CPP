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
    std::string help{};
    help += "[mix]:\n";
    help += "Mixes original input file with provided second stream\n";
    help += "\tfirst operand - $id of the secondary input stream (starts from 1);\n";
    help += "\tsecond operand - start second;\n";
    help += "\tthird operand - end second;\n";
    return help;
}

