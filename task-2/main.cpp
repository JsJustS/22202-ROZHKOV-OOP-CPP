//
// Created by Just on 22.11.2023.
//
#include "header/Engine.h"
#include "header/ArgHandler.h"

int main(int argc, char* argv[]) {
    ArgHandler handler(argc, argv);

    Engine::init();
    Engine::setLogger(std::cout);

    if (handler.hasInputFilename()) {
        std::string conf = handler.getInputFilename();
        std::string suffix = conf.substr(conf.rfind('.'), conf.length() - conf.rfind('.'));
        if (suffix == ".lif" || suffix == ".life") {
            Engine::loadConfig(conf);
        } else {
            Engine::log(R"(Input File has wrong format! Use only ".lif" or ".life" formats.)");
            Engine::loadConfig();
        }
    } else {
        Engine::loadConfig();
    }

    if (!handler.hasOutputFilename() && !handler.hasIterations()) {
        // Online mode
        Engine::startOnline();
    } else if (handler.hasOutputFilename() && handler.hasIterations()) {
        // Offline mode
        for (int i = 0; i < handler.getIterations(); ++i) {
            Engine::tickField();
        }
        Engine::dump(handler.getOutputFilename());
        Engine::log("Successfully iterated for " + std::to_string(handler.getIterations()) + " iteration(s).");
        Engine::log("Result is saved in \"" + handler.getOutputFilename() + "\".");
    } else {
        // error
        if (!handler.hasOutputFilename()) {
            Engine::log(R"(To use offline mode, specify output file with "-o filename" or "--output=filename")");
        } else if (!handler.hasIterations()) {
            Engine::log(R"(To use offline mode, specify amount of iterations to cycle through with "-i x" or "--iterations=x")");
        }
    }

    Engine::stop();
    return 0;
}