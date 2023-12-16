//
// Created by Just on 02.12.2023.
//

#include <iostream>
#include "header/ArgHandler.h"
#include "header/SoundProcessor.h"

#include "header/errors/SoundProcessingError.h"

int main(int argc, char *argv[]) {

    try {
        ArgHandler argHandler(argc, argv);

        SoundProcessor soundProcessor{};

        if (argHandler.isHelpRequested()) {
            soundProcessor.printOutHelp(std::cout);
            return 0;
        }

        if (!argHandler.hasConfigFilename() || !argHandler.hasInputFilenames() || !argHandler.hasInputFilenames()) {
            return 0;
        }

        soundProcessor.loadConfig(argHandler.getConfigFilename());
        soundProcessor.setOutputFileName(argHandler.getOutputFilename());
        soundProcessor.setInputFileNames(argHandler.getInputFilenames());

        soundProcessor.process();
    } catch (WrongArgumentsError& e) {
        std::cerr << "WrongArgumentsError: " << e.what() << std::endl;
        return -2;
    } catch (SoundProcessingError& e) {
        std::cerr << "SoundProcessingError: " << e.what() << std::endl;
        return -1;
    }
    return 0;
}