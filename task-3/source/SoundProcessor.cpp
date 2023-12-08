//
// Created by Just on 08.12.2023.
//
#include "../header/SoundProcessor.h"

SoundProcessor::SoundProcessor() {
    this->config = new ConfigManager();
}

SoundProcessor::~SoundProcessor() {
    delete config;
}

void SoundProcessor::process() {
    /**
     * 1. Open all wave files
     * 2. Read sample from everyone
     * 3. Apply Converter
     * 4. Save result
     * */
    std::vector<ConverterFabric> converterFabrics = this->getFabricsByConfig();
    std::vector<Converter*> converters{};
    converters.reserve(converterFabrics.size());
    for (auto&& converterFabric : converterFabrics) {
        converters.emplace_back(converterFabric.getConverter());
    }

    // open all wav files
    std::vector<WAVWrapper> wrappers{};
    wrappers.reserve(this->inputFileNames.size());
    for (auto&& inputFileName : this->inputFileNames) {
        wrappers.emplace_back(inputFileName, WAVWrapper::MODE::INPUT);
    }
    WAVWrapper outputWAV(this->outputFileName, WAVWrapper::MODE::OUTPUT);

    // start process
    if (SoundProcessor::areInputsOpen(wrappers) && outputWAV.isOpen(WAVWrapper::MODE::OUTPUT)) {
        // headers
        for (auto&& wrapper : wrappers) {
            wrapper.readHeader();
        }
        outputWAV.setHeader(wrappers[0].getHeader());
        outputWAV.writeHeader();

        // modify samples
        std::vector<Sample> samples{};
        samples.reserve(wrappers.size());
        while (!wrappers[0].isEOF()) {
            for (auto&& wrapper : wrappers) {
                samples.emplace_back(wrapper.readSample());
            }

            for (auto&& converter : converters) {
                samples[0] = converter->modify(samples);
            }

            outputWAV.loadSample(samples[0]);
            outputWAV.writeSample();
            samples.clear();
        }
    }

    // close all files
    for (auto&& wrapper : wrappers) {
        wrapper.close();
    }
    outputWAV.close();

    // free converter memory
    for (auto&& converter : converters) {
        delete converter;
    }
}

bool SoundProcessor::areInputsOpen(std::vector<WAVWrapper> wrappers) {
    bool flag = true;
    for (auto&& wrapper : wrappers) {
        if (!wrapper.isOpen()) {
            flag = false;
            break;
        }
    }
    return flag;
}

std::vector<ConverterFabric> SoundProcessor::getFabricsByConfig() {
    //todo: get fabrics by config
    this->config;
    return std::vector<ConverterFabric>();
}

void SoundProcessor::loadConfig(const std::string &fileName) {
    //todo: load config from file
}

void SoundProcessor::setOutputFileName(const std::string &fileName) {
    this->outputFileName = fileName;
}

void SoundProcessor::setInputFileNames(const std::vector<std::string> &fileNames) {
    this->inputFileNames = fileNames;
}

void SoundProcessor::printOutHelp(std::ostream &out) {

}
