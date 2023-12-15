//
// Created by Just on 09.12.2023.
//

#include "../../header/Converters/ConverterMute.h"

ConverterMute::ConverterMute(unsigned int secondStart, unsigned int secondEnd) {
    this->startSampleId = secondStart * SAMPLES_PER_SECOND;
    this->lastSampleId = secondEnd * SAMPLES_PER_SECOND;
    this->currentSampleId = -1;
}

Sample ConverterMute::modify(int size, Sample *samples) {
    this->currentSampleId++;
    if (this->startSampleId <= this->currentSampleId && this->currentSampleId <= this->lastSampleId) {
        return Sample(2).saveAsInt(0);
    }
    return Sample(2).saveAsInt(samples[0].getAsInt());
}

