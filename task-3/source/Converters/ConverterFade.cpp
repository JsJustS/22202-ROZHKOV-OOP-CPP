//
// Created by Just on 09.12.2023.
//
#include "../../header/Converters/ConverterFade.h"

ConverterFade::ConverterFade(unsigned int secondStart, unsigned int secondEnd, int k, bool isIn) {
    this->startSampleId = secondStart * SAMPLES_PER_SECOND;
    this->lastSampleId = secondEnd * SAMPLES_PER_SECOND;
    this->currentSampleId = -1;
    this->modifier = 0;
    this->delta = 1.0 / (this->lastSampleId - this->startSampleId);
    this->coef = (k < 0) ? 1.0/(-1*k):k;
    this->isIn = isIn;
}

Sample ConverterFade::modify(int size, Sample *samples) {
    this->currentSampleId++;
    if (this->startSampleId <= this->currentSampleId && this->currentSampleId <= this->lastSampleId) {

        this->modifier += this->delta;
        return Sample().saveAsInt((int16_t)(samples[0].getAsInt() * easeFunc(this->modifier)));
    }
    return Sample().saveAsInt(samples[0].getAsInt());
}

double ConverterFade::easeFunc(double x) {
    return (this->isIn) ? pow(x, this->coef): 1.0 -pow(x, this->coef);
}
