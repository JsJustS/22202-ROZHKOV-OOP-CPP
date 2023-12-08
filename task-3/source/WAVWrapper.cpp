//
// Created by Just on 02.12.2023.
//
#include "../header/WAVWrapper.h"

WAVWrapper::WAVWrapper() {
    this->headerData = nullptr;
    this->WAVInputFileName = "";
    this->WAVInputFileStream = nullptr;
    this->WAVOutputFileName = "";
    this->WAVOutputFileStream = nullptr;
    this->currentSample = nullptr;
}

WAVWrapper::WAVWrapper(const std::string& fileName, MODE mode) {
    this->headerData = nullptr;
    this->WAVOutputFileStream = nullptr;
    this->WAVInputFileStream = nullptr;
    this->currentSample = nullptr;
    switch (mode) {
        case INPUT: {
            this->WAVOutputFileName = "";
            this->WAVInputFileName = fileName;
            break;
        }
        case OUTPUT: {
            this->WAVInputFileName = "";
            this->WAVOutputFileName = fileName;
            break;
        }
    }
    this->open(mode);
}

WAVWrapper::~WAVWrapper() {
    delete [] this->headerData;

    if (this->WAVInputFileStream != nullptr && this->WAVInputFileStream->is_open()) {
        this->WAVInputFileStream->close();
    }
    delete this->WAVInputFileStream;

    if (this->WAVOutputFileStream != nullptr && this->WAVOutputFileStream->is_open()) {
        this->WAVOutputFileStream->close();
    }
    delete this->WAVOutputFileStream;
    delete this->currentSample;
}

void WAVWrapper::open(WAVWrapper::MODE mode) {
    switch (mode) {
        case INPUT: {
            this->WAVInputFileStream = new std::ifstream(this->WAVInputFileName, std::ios::binary);
            break;
        }
        case OUTPUT: {
            this->WAVOutputFileStream = new std::ofstream(this->WAVOutputFileName, std::ios::binary);
            break;
        }
    }
}

void WAVWrapper::open(const std::string &fileName, WAVWrapper::MODE mode) {
    switch (mode) {
        case INPUT: {
            this->WAVInputFileName = fileName;
            break;
        }
        case OUTPUT: {
            this->WAVOutputFileName = fileName;
            break;
        }
    }

    this->open(mode);
}

bool WAVWrapper::isOpen(WAVWrapper::MODE mode) {
    switch (mode) {
        case INPUT: return this->WAVInputFileStream->is_open();
        case OUTPUT: return this->WAVOutputFileStream->is_open();
    }
}

void WAVWrapper::close() {
    this->close(WAVWrapper::MODE::INPUT);
    this->close(WAVWrapper::MODE::OUTPUT);
}

void WAVWrapper::close(WAVWrapper::MODE mode) {
    switch (mode) {
        case INPUT: {
            if (this->WAVInputFileStream->is_open()) {
                this->WAVInputFileStream->close();
            }
            delete this->WAVInputFileStream;
            this->WAVInputFileStream = nullptr;
            break;
        }
        case OUTPUT: {
            if (this->WAVOutputFileStream->is_open()) {
                this->WAVOutputFileStream->close();
            }
            delete this->WAVOutputFileStream;
            this->WAVOutputFileStream = nullptr;
            break;
        }
    }
}

void WAVWrapper::readHeader() {
    this->headerData = new union HEADER_DATA;
    for (int i = 0; i < HEADER_SIZE && this->WAVInputFileStream->peek() != EOF; i++) {
        this->WAVInputFileStream->read( reinterpret_cast<char*>(&this->headerData->data[i]), 1);
    }

    if (this->WAVInputFileStream->peek() == EOF) {
        throw std::runtime_error("WAV Header is not sufficient.");
    }
}

void WAVWrapper::writeHeader() {
    for (Byte byte : this->headerData->data) {
        WAVWrapper::writeByte(*this->WAVOutputFileStream, byte);
    }
}

Sample WAVWrapper::readSample() {
    if (this->currentSample == nullptr) {
        this->currentSample = new Sample(this->headerData->header.BlockAlign);
    }

    this->currentSample->read(*this->WAVInputFileStream);
    // todo: reading by WAVWrapper class, not Sample class
    // this->currentSample->operator[](i) = data[i];
    return *this->currentSample;
}

void WAVWrapper::loadSample(const Sample &sample) {
    if (this->currentSample == nullptr) {
        this->currentSample = new Sample(sample.getSize());
    }

    this->currentSample->operator=(sample);
}

void WAVWrapper::writeSample() {
    if (this->currentSample == nullptr) {
        //todo: throw error that sample is not set
        return;
    }
    // todo: writing by WAVWrapper class, not Sample class
    this->currentSample->write(*this->WAVOutputFileStream);
}

int WAVWrapper::getSampleCount() const {
    // size of header without few sections = 38
    return (this->headerData->header.ChunkSize - 38) / this->headerData->header.BlockAlign;
}

void WAVWrapper::writeByte(std::ofstream &stream, Byte byte) {
    stream.write(reinterpret_cast<const char*>(&byte), 1);
}

bool WAVWrapper::isEOF() {
    return this->WAVInputFileStream == nullptr || !this->WAVInputFileStream->is_open() || this->WAVInputFileStream->eof();
}

WAVWrapper::HEADER_DATA WAVWrapper::getHeader() const {
    return *this->headerData;
}

void WAVWrapper::setHeader(WAVWrapper::HEADER_DATA data) {
    if (this->headerData == nullptr) {
        this->headerData = new union HEADER_DATA;
    }
    this->headerData->header = data.header;
}
