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
    Engine(const Field& fld, ConfigManager cfg);

    static Engine* instance;

    Field field;
    ConfigManager config;
public:
    Engine() = delete;
    Engine(Engine const&) = delete;
    void operator=(Engine const&) = delete;

    static Engine* getInstance(std::ostream& out = std::cout);

    void tickField();
};
#endif //TASK_2_ENGINE_H
