//
// Created by Just on 18.11.2023.
//

#ifndef TASK_2_ENGINE_H
#define TASK_2_ENGINE_H
/**
 * Main class for the game
 * */
#include <iostream>

#include "Field.h"
#include "ConfigManager.h"

//todo: Main engine
class Engine {
private:
    Engine(const Field& fld, const Field& fld1, ConfigManager cfg);

    static Engine* instance;

    Field* field;
    Field* fieldOld;
    ConfigManager* config;

    std::ostream* logger;

    Engine();
public:
    Engine(Engine const&) = delete;
    void operator=(Engine const&) = delete;

    static void stop();
    static void init();

    static void setLogger(std::ostream& out);
    static void log(const std::string &message);

    static void loadConfig(const std::string& filename);

    static void draw();
    static void tick();
};
#endif //TASK_2_ENGINE_H
