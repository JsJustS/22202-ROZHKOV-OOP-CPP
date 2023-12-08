//
// Created by Just on 02.12.2023.
//

#ifndef TASK_3_CONVERTIONMANAGER_H
#define TASK_3_CONVERTIONMANAGER_H

#include <ostream>
#include <vector>

#include "WAVWrapper.h"
#include "Converter.h"
#include "ConverterFabric.h"
#include "ConfigManager.h"
#include "LineParser.h"
#include "FileReader.h"

/**
 * Manages the process of conversion
 * */
class SoundProcessor {
private:
    ConfigManager* config;

    std::string outputFileName;
    std::vector<std::string> inputFileNames;

    static bool areInputsOpen(int size, WAVWrapper* wrappers);
public:
    SoundProcessor();
    ~SoundProcessor();

    static void printOutHelp(std::ostream& out);

    void loadConfig(const std::string& fileName);
    void setOutputFileName(const std::string& fileName);
    void setInputFileNames(const std::vector<std::string>& fileNames);

    void process();

    std::vector<ConverterFabric> getFabricsByConfig();
};

#endif //TASK_3_CONVERTIONMANAGER_H
