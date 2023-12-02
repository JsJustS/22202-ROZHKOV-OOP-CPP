//
// Created by Just on 02.12.2023.
//

#ifndef TASK_3_WAVWRAPPER_H
#define TASK_3_WAVWRAPPER_H

#include <string>
#include <cstdint>

#define HEADER_SIZE 44

class WAVWrapper {
    typedef unsigned char byte;
private:
    union byte4 {
        uint32_t value;
        byte bytes[4];
    };
    union byte2 {
        uint16_t value;
        byte bytes[2];
    };

    struct HEADER {
        char ChunkID[4];
        union byte4 ChunkSize;
        union byte4 Format;
        char SubChunk1_ID[4];
        union byte4 SubChunk1_SIZE;
        union byte2 AudioFormat;
        union byte2 NumChannels;
        union byte4 SampleRate;
        union byte4 ByteRate;
        union byte2 BlockAlign;
        union byte2 BitsPerSample;
        char SubChunk2_ID[4];
        union byte4 SubChunk2_SIZE;
    };

    union HEADER_DATA {
        byte data[HEADER_SIZE];
        struct HEADER header;
    };

    HEADER_DATA* header;

    int offset;
    byte* raw;
public:
    ~WAVWrapper();
    WAVWrapper();

    void readHeader(std::ifstream& stream);
    void writeHeader(const std::ifstream& stream);

    void readPiece(const std::ifstream& stream);
    void writePiece(const std::ifstream& stream);
};
#endif //TASK_3_WAVWRAPPER_H
