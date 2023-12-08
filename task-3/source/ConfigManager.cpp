//
// Created by Just on 02.12.2023.
//
#include "../header/ConfigManager.h"

std::string ConfigManager::getOutputFileName() {
    return this->outputFileName;
}

std::vector<std::string> ConfigManager::getInputFileNames() {
    return this->inputFileNames;
}

