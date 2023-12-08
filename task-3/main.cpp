//
// Created by Just on 02.12.2023.
//

#include <iostream>
#include "header/ArgHandler.h"
#include "header/SoundProcessor.h"

int main(int argc, char *argv[]) {
    ArgHandler argHandler(argc, argv);

    SoundProcessor soundProcessor{};

    if (argHandler.isHelpRequested()) {
        SoundProcessor::printOutHelp(std::cout);
        return 0;
    }

    if (!argHandler.hasConfigFilename() || !argHandler.hasInputFilenames() || !argHandler.hasInputFilenames()) {
        return 0;
    }

    soundProcessor.loadConfig(argHandler.getConfigFilename());
    soundProcessor.setOutputFileName(argHandler.getOutputFilename());
    soundProcessor.setInputFileNames(argHandler.getInputFilenames());

    soundProcessor.process();
    return 0;
}