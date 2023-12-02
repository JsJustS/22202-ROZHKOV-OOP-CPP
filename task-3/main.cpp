//
// Created by Just on 02.12.2023.
//



#include <fstream>
#include "header/WAVWrapper.h"

int main (int argc, char* argv[]) {
    /**
     * 1. Open File
     * 2. Read part of it
     * 3. Apply Converter
     * 4. Save as .temp
     * 5. If no converter left, save .temp as .wav
     * else open .temp and use next converter
     * */
    std::ifstream file ("test.wav");

    WAVWrapper wav{};
    wav.readHeader(file);

    file.close();
    return 0;
}