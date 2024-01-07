//
// Created by Just on 02.12.2023.
//

#ifndef TASK_3_ARGHANDLER_H
#define TASK_3_ARGHANDLER_H
#include <string>
#include <cstring>
#include <vector>

#include "errors/WrongArgumentsError.h"

class ArgHandler {
private:
    std::string configFileName;
    std::string outputFileName;
    std::vector<std::string> inputFileNames;
    bool helpRequested;
public:
    ArgHandler(int argc, char* argv[]) noexcept(false);

    bool hasInputFilenames() const;
    std::vector<std::string> getInputFilenames() const;
    bool hasOutputFilename() const;
    std::string getOutputFilename() const;
    bool hasConfigFilename() const;
    std::string getConfigFilename() const;
    bool isHelpRequested() const;
};

#endif //TASK_3_ARGHANDLER_H
