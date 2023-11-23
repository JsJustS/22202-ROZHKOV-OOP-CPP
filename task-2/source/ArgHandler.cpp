//
// Created by Just on 23.11.2023.
//
#include "../header/ArgHandler.h"

ArgHandler::ArgHandler(int argc, char **argv) {
    char* argFIn = nullptr;
    char* argFOut = nullptr;
    char* argIt = nullptr;
    static struct option long_options[] = {
            {"output",     required_argument, nullptr, 'o'},
            {"iterations", required_argument, nullptr, 'i'},
            {nullptr, 0, nullptr, 0}
    };
    int option_index;
    int c;
    while ((c = getopt_long(argc, argv, "io", long_options, &option_index)) != -1) {
        switch (c) {
            case 'o': {
                argFOut = optarg;
                break;
            }
            case 'i': {
                argIt = optarg;
                break;
            }
            case '?': {
                argFIn = optarg;
                break;
            }
        }
    }

    this->inputFilename = (argFIn) ? std::string(argFIn) : std::string{};
    this->outputFilename = (argFOut) ? std::string(argFOut) : std::string{};
    this->iterations = (argIt) ? std::stoi(std::string(argIt)) : -1;
}

bool ArgHandler::hasInputFilename() const {
    return !this->inputFilename.empty();
}

bool ArgHandler::hasOutputFilename() const {
    return !this->outputFilename.empty();
}

bool ArgHandler::hasIterations() const {
    return this->iterations > -1;
}

std::string ArgHandler::getInputFilename() const {
    return this->inputFilename;
}

std::string ArgHandler::getOutputFilename() const {
    return this->outputFilename;
}

int ArgHandler::getIterations() const {
    return this->iterations;
}

