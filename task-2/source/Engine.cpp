//
// Created by Just on 18.11.2023.
//
#include <utility>

#include "../header/Engine.h"

Engine* Engine::instance = nullptr;

Engine::Engine() {
    this->field = nullptr;
    this->fieldOld = nullptr;
    this->config = nullptr;
    this->logger = nullptr;
}

void Engine::init() {;
    instance = new Engine();
}

void Engine::stop() {
    delete instance->config;
    delete instance->field;
    delete instance->fieldOld;
    delete instance;
    instance = nullptr;
}

void Engine::loadConfig(const std::string &filename) {
    instance->config = new ConfigManager();
    std::vector<std::pair<int, int>> coords = instance->config->load(filename);

    instance->field = new Field(
            instance->config->getFieldWidth(),
            instance->config->getFieldHeight()
    );
    instance->fieldOld = new Field(
            instance->config->getFieldWidth(),
            instance->config->getFieldHeight()
    );

    instance->field->load(coords);
}

void Engine::setLogger(std::ostream &out) {
    delete instance->logger;
    instance->logger = &out;
}

void Engine::log(const std::string &message) {
    if (instance->logger == nullptr) return;
    (*instance->logger) << message << std::endl;
}

void Engine::draw() {
    Engine::log("=========");

    int width = instance->config->getFieldWidth();
    int height = instance->config->getFieldHeight();
    for (int y = 0; y < height; ++y) {
        std::string line{};
        for (int x = 0; x < width; ++x) {
            //line += (instance->field->getCell(x, y)) ? "⬜" : "⬛";
            line += (instance->field->getCell(x, y)) ? "# " : ". ";
        }
        Engine::log(line);
    }
}

void Engine::tick() {
    int width = instance->config->getFieldWidth();
    int height = instance->config->getFieldHeight();

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            instance->fieldOld->setCell(
                    x, y,
                    instance->field->getCell(x, y)
            );
        }
    }

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            char count = instance->fieldOld->countAliveNeighbours(x, y);
            bool shouldBirth = instance->config->canBirth(count);
            bool shouldSurvive = instance->config->canSurvive(count);

            if (instance->fieldOld->getCell(x, y)) {
                instance->field->setCell(x, y, shouldSurvive);
            } else {
                instance->field->setCell(x, y, shouldBirth);
            }

        }
    }
}
