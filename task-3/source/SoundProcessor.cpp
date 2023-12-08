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
     int inputCount = this->inputFileNames.size();
    std::vector<ConverterFabric> converterFabrics = this->getFabricsByConfig();
    std::vector<Converter*> converters{};
    converters.reserve(converterFabrics.size());
    for (auto&& converterFabric : converterFabrics) {
        converters.emplace_back(converterFabric.getConverter());
    }

    // open all wav files
    WAVWrapper* wrappers = new WAVWrapper[this->inputFileNames.size()];
    for (int i = 0; i < this->inputFileNames.size(); ++i) {
        wrappers[i].open(this->inputFileNames[i], WAVWrapper::MODE::INPUT);
    }
    WAVWrapper outputWAV(this->outputFileName, WAVWrapper::MODE::OUTPUT);

    // start process
    if (SoundProcessor::areInputsOpen(this->inputFileNames.size(), wrappers) &&  outputWAV.isOpen(WAVWrapper::MODE::OUTPUT)) {
        // headers
         for (int i = 0; i < this->inputFileNames.size(); ++i) {
             wrappers[i].readHeader();
         }
         outputWAV.setHeader(wrappers[0].getHeader());
         outputWAV.writeHeader();

        // modify samples
        Sample* samples = new Sample[inputCount];
        while (!wrappers[0].isEOF()) {

            for (int i = 0; i < inputCount; ++i) {
                samples[i] = wrappers[0].readSample();
            }

            for (auto&& converter : converters) {
                samples[0] = converter->modify(inputCount, samples);
            }

            outputWAV.loadSample(samples[0]);
            outputWAV.writeSample();
        }
        delete [] samples;
    }

    // close all files
    delete [] wrappers;
    outputWAV.close(WAVWrapper::MODE::OUTPUT);

    // free converter memory
    for (auto&& converter : converters) {
        delete converter;
    }
}

bool SoundProcessor::areInputsOpen(int size, WAVWrapper* wrappers) {
    bool flag = true;
    for (int i = 0; i < size; ++i) {
        if (!wrappers[i].isOpen(WAVWrapper::MODE::INPUT)) {
            flag = false;
            break;
        }
    }
    return flag;
}

std::vector<ConverterFabric> SoundProcessor::getFabricsByConfig() {
    return this->config->getFabrics();
}

void SoundProcessor::loadConfig(const std::string &fileName) {
    FileReader reader(fileName);
    for (std::string line; reader.hasNext(); line = reader.next()) {
        std::vector<std::string> args = LineParser::parse(line);
        this->config->appendConverterFabric(args);
    }
}

void SoundProcessor::setOutputFileName(const std::string &fileName) {
    this->outputFileName = fileName;
}

void SoundProcessor::setInputFileNames(const std::vector<std::string> &fileNames) {
    this->inputFileNames = fileNames;
}

void SoundProcessor::printOutHelp(std::ostream &out) {
    // todo: print out helper for every converter
    out << "Help me please" << std::endl;
}
