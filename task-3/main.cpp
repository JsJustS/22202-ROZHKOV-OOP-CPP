//
// Created by Just on 02.12.2023.
//



#include <fstream>
#include "header/WAVWrapper.h"

int main(int argc, char *argv[]) {
    /**
     * 1. Open File
     * 2. Read part of it
     * 3. Apply Converter
     * 4. Save as .temp
     * 5. If no converter left, save .temp as .wav
     * else open .temp and use next converter
     * */
    WAVWrapper wav("test.wav");
    wav.open("testOut.wav", WAVWrapper::MODE::OUTPUT);

    if (wav.isOpen(WAVWrapper::MODE::INPUT) && wav.isOpen(WAVWrapper::MODE::OUTPUT)) {
        wav.readHeader();
        wav.writeHeader();
        while (!wav.isEOF()) {
            Sample sample = wav.readSample();
            // modify sample
            wav.loadSample(sample);
            wav.writeSample();
        }
    }

    wav.close();
    return 0;
}