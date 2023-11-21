//
// Created by Just on 18.11.2023.
//
#include <utility>

#include "../header/Engine.h"

Engine* Engine::instance = nullptr;

Engine::Engine(const Field& fld, ConfigManager cfg) : field(fld),config(std::move(cfg)) {}

Engine *Engine::getInstance(std::ostream &out) {
    if (instance) return instance;
    ConfigManager config{out};
    Field field{};
    config.load("C:\\Users\\Just\\CLionProjects\\22202-ROZHKOV-OOP-CPP\\task-2\\games\\test.lif", field);

    instance = new Engine(field, config);
    return instance;
}

