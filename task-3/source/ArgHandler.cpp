//
// Created by Just on 08.12.2023.
//
#include "../header/ArgHandler.h"

ArgHandler::ArgHandler(int argc, char** argv) {
    this->inputFileNames = {};
    if (argc == 2 && strcmp( argv[1], "-h") == 0) {
        this->helpRequested = true;
        this->configFileName = "";
        this->outputFileName = "";
        return;
    } else if (argc > 4 && strcmp( argv[1], "-c") == 0) {
        this->helpRequested = false;
        this->configFileName = argv[2];
        this->outputFileName = argv[3];
        for (int i = 4; i < argc; ++i) {
            this->inputFileNames.emplace_back(argv[i]);
        }
        return;
    }
    //todo: throw error about wrong arguments
}

bool ArgHandler::hasInputFilenames() const {
    return !this->inputFileNames.empty();
}

std::vector<std::string> ArgHandler::getInputFilenames() const {
    return this->inputFileNames;
}

bool ArgHandler::hasOutputFilename() const {
    return !this->outputFileName.empty();
}

std::string ArgHandler::getOutputFilename() const {
    return this->outputFileName;
}

bool ArgHandler::hasConfigFilename() const {
    return !this->configFileName.empty();
}

std::string ArgHandler::getConfigFilename() const {
    return this->configFileName;
}

bool ArgHandler::isHelpRequested() const {
    return this->helpRequested;
}

