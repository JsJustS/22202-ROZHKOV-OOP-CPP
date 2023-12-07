//
// Created by Just on 02.12.2023.
//

#ifndef TASK_3_WAVWRAPPER_H
#define TASK_3_WAVWRAPPER_H

#include <string>
#include <cstdint>
#include <fstream>
#include "Sample.h"

#define HEADER_SIZE 44
class WAVWrapper {
    typedef unsigned char Byte;
private:

    // wrapper data

    struct HEADER {
        char ChunkID[4];
        uint32_t ChunkSize;
        uint32_t Format;
        char SubChunk1_ID[4];
        uint32_t SubChunk1_SIZE;
        uint16_t AudioFormat;
        uint16_t NumChannels;
        uint32_t SampleRate;
        uint32_t ByteRate;
        uint16_t BlockAlign;
        uint16_t BitsPerSample;
        char SubChunk2_ID[4];
        uint32_t SubChunk2_SIZE;
    };

    union HEADER_DATA {
        Byte data[HEADER_SIZE];
        struct HEADER header;
    };

    HEADER_DATA* headerData;

    // actual cpp stuff

    std::string WAVInputFileName;
    std::ifstream* WAVInputFileStream;
    std::string WAVOutputFileName;
    std::ofstream* WAVOutputFileStream;

    Sample* currentSample;

    static void writeByte(std::ofstream& stream, Byte value);
public:
    enum MODE {
        INPUT,
        OUTPUT
    };

    WAVWrapper(const WAVWrapper& copy) = delete;

    WAVWrapper();
    explicit WAVWrapper(const std::string& fileName, MODE mode = INPUT);
    ~WAVWrapper();

    void open(MODE mode = INPUT);
    void open(const std::string& fileName, MODE mode = INPUT);
    bool isOpen(MODE mode = INPUT);
    bool isEOF();
    void close();
    void close(MODE mode);

    void readHeader();
    void writeHeader();

    int getSampleCount() const;

    Sample readSample();
    void loadSample(const Sample& sample);
    void writeSample();
};
#endif //TASK_3_WAVWRAPPER_H
