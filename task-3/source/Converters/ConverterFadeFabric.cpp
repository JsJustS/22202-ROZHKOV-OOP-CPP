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

std::string ConverterFadeFabric::getHelp() {
    std::string help{};
    help += "[fadein]:\n";
    help += "Makes the sound begin with silence and increases it to the full volume gradually.\n";
    help += "\tfirst operand - start second;\n";
    help += "\tsecond operand - end second;\n";
    help += "\tthird operand - coefficient for fading function;\n";
    help += "[fadeout]:\n";
    help += "Makes the sound begin with the full volume and decreases it to the silence gradually.\n";
    help += "\tfirst operand - start second;\n";
    help += "\tsecond operand - end second;\n";
    help += "\tthird operand - coefficient for fading function;\n";
    return help;
}
