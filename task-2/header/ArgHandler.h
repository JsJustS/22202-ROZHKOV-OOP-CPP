//
// Created by Just on 23.11.2023.
//

#ifndef INC_22202_ROZHKOV_OOP_CPP_TASK_2_ARGHANDLER_H
#define INC_22202_ROZHKOV_OOP_CPP_TASK_2_ARGHANDLER_H

#include <string>
#include <getopt.h>

class ArgHandler {
private:
    std::string inputFilename;
    std::string outputFilename;
    int iterations;
public:
    ArgHandler(int argc, char* argv[]);

    bool hasInputFilename() const;
    std::string getInputFilename() const;
    bool hasOutputFilename() const;
    std::string getOutputFilename() const;
    bool hasIterations() const;
    int getIterations() const;
};
#endif //INC_22202_ROZHKOV_OOP_CPP_TASK_2_ARGHANDLER_H
