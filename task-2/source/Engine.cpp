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
    std::cout << "deleting logger" << std::endl;
    //delete instance->logger;
    std::cout << "deleted. deleting config" << std::endl;
    delete instance->config;
    std::cout << "deleted. deleting field" << std::endl;
    delete instance->field;
    std::cout << "deleted. deleting fieldOld" << std::endl;
    delete instance->fieldOld;
    std::cout << "deleted. deleting instance" << std::endl;
    delete instance;
    std::cout << "deleted." << std::endl;
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
            line += (instance->field->getCell(x, y)) ? "⬜" : "⬛";
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

    Engine::log(instance->config->toString());

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            char count = instance->fieldOld->countAliveNeighbours(x, y);
            //std::cout << x << "|" << y << "|" << (int)count << std::endl;
            bool shouldBirth = instance->config->canBirth(count);
            bool shouldSurvive = instance->config->canSurvive(count);

            instance->field->setCell(x, y, shouldBirth || shouldSurvive);
        }
    }
}
