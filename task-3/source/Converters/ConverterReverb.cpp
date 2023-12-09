//
// Created by Just on 09.12.2023.
//
#include "../../header/Converters/ConverterReverb.h"

ConverterReverb::ConverterReverb(unsigned int echoCount) {
    this->echoCount = echoCount;
    this->delaySize = 0;
    this->delayedSamples = new int[echoCount];
}

Sample ConverterReverb::modify(int size, Sample *samples) {
    int beforeModify = samples[0].getAsInt();
    Sample resSample(2);
    resSample.saveAsInt(samples[0].getAsInt());
    for (int i = 0; i < this->delaySize; ++i) {
        int16_t res = (resSample.getAsInt() + this->delayedSamples[i]);
        resSample.saveAsInt(res);
    }

    if (delaySize < this->echoCount) {
        this->delayedSamples[delaySize] = beforeModify;
        this->delaySize++;
    } else {
        memcpy(this->delayedSamples + 1, this->delayedSamples, this->echoCount-1);
        this->delayedSamples[0] = beforeModify;
    }
    return resSample;
}

ConverterReverb::~ConverterReverb() {
    delete [] this->delayedSamples;
}

std::string ConverterReverb::getHelp() {
    //todo: help
    return std::string();
}

