//
// Created by Just on 09.12.2023.
//
#include "../../header/Converters/ConverterMix.h"

ConverterMix::ConverterMix(unsigned int sideStreamId, unsigned int secondStart, unsigned int secondEnd) {
    this->sideStreamId = sideStreamId;
    this->startSampleId = secondStart * SAMPLES_PER_SECOND;
    this->lastSampleId = secondEnd * SAMPLES_PER_SECOND;
    this->currentSampleId = -1;
}

std::string ConverterMix::getHelp() {
    //todo: help
    return std::string();
}

Sample ConverterMix::modify(int size, Sample *samples) {
    this->currentSampleId++;
    if (this->currentSampleId < this->startSampleId || this->lastSampleId < this->currentSampleId) {
        return Sample(2).saveAsInt(samples[0].getAsInt());
    }

    //todo: throw error
    if (this->sideStreamId > size) {return Sample(2).saveAsInt(samples[0].getAsInt());}

    if (!samples[this->sideStreamId - 1].isLoaded()) {
        return Sample(2).saveAsInt(samples[0].getAsInt());
    }

    int16_t res = samples[0].getAsInt() + samples[this->sideStreamId - 1].getAsInt();
    return Sample(2).saveAsInt(res);
}

