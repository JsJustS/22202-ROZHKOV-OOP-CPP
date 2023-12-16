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

Sample ConverterMix::modify(int size, Sample *samples) {
    this->currentSampleId++;
    if (this->currentSampleId < this->startSampleId || this->lastSampleId < this->currentSampleId) {
        return Sample().saveAsInt(samples[0].getAsInt());
    }

    if (this->sideStreamId > size) {throw OutOfRangeStreamIdError(this->sideStreamId, size);}

    if (!samples[this->sideStreamId - 1].isLoaded()) {
        return Sample().saveAsInt(samples[0].getAsInt());
    }

    int16_t res = samples[0].getAsInt() + samples[this->sideStreamId - 1].getAsInt();
    return Sample().saveAsInt(res);
}

