//
// Created by Just on 22.11.2023.
//
#include "header/Engine.h"
#include "header/ArgHandler.h"

int main(int argc, char* argv[]) {
    ArgHandler handler(argc, argv);

    Engine engine{};
    engine.init();
    engine.setLogger(std::cout);

    if (handler.hasInputFilename()) {
        std::string conf = handler.getInputFilename();
        std::string suffix = conf.substr(conf.rfind('.'), conf.length() - conf.rfind('.'));
        if (suffix == ".lif" || suffix == ".life") {
            engine.loadConfig(conf);
        } else {
            engine.log(R"(Input File has wrong format! Use only ".lif" or ".life" formats.)");
            engine.loadConfig();
        }
    } else {
        engine.loadConfig();
    }

    if (!handler.hasOutputFilename() && !handler.hasIterations()) {
        // Online mode
        engine.startOnline();
    } else if (handler.hasOutputFilename() && handler.hasIterations()) {
        // Offline mode
        for (int i = 0; i < handler.getIterations(); ++i) {
            engine.tickGameLogic();
        }
        engine.dump(handler.getOutputFilename());
        engine.log("Successfully iterated for " + std::to_string(handler.getIterations()) + " iteration(s).");
        engine.log("Result is saved in \"" + handler.getOutputFilename() + "\".");
    } else {
        // error
        if (!handler.hasOutputFilename()) {
            engine.log(R"(To use offline mode, specify output file with "-o filename" or "--output=filename")");
        } else if (!handler.hasIterations()) {
            engine.log(R"(To use offline mode, specify amount of iterations to cycle through with "-i x" or "--iterations=x")");
        }
    }

    engine.stop();
    return 0;
}