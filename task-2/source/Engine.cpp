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
    this->screen = nullptr;
}

void Engine::init() {;
    instance = new Engine();
    instance->screen = new ConsoleScreen(30, 5);
}

void Engine::stop() {
    delete instance->config;
    delete instance->field;
    delete instance->fieldOld;
    delete instance->screen;
    delete instance;
    instance = nullptr;
}

void Engine::loadConfig(const std::string &filename) {
    instance->config = new ConfigManager();
    std::vector<std::pair<int, int>> coords = instance->config->load(filename);

    int fw = instance->config->getFieldWidth();
    int fh = instance->config->getFieldHeight();

    instance->field = new Field(fw,fh);
    instance->fieldOld = new Field(fw,fh);

    instance->field->load(coords);

    instance->screen->setWidth(2*fw + 3).setHeight(fh + 6);
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
    instance->screen->clear();

    int white = ConsoleScreen::rgb2Int(255, 255, 255);
    int black = ConsoleScreen::rgb2Int(0, 0, 0);
    int barrier = ConsoleScreen::rgb2Int(13, 77, 0);
    int aqua = ConsoleScreen::rgb2Int(0, 255, 255);

    int width = instance->config->getFieldWidth();
    int height = instance->config->getFieldHeight();

    int textX = (instance->screen->getWidth() - instance->config->getUniverseName().length()) / 2;
    if (textX < 0) {
        textX = 0;
    }
    instance->screen->addText(textX, 1,
                              instance->config->getUniverseName(),
                              aqua);
    instance->screen->addLine(0, 0,
                              instance->screen->getWidth() - 1, 0,
                              barrier);
    instance->screen->addLine(0, 2,
                              instance->screen->getWidth() - 1, 2,
                              barrier);
    instance->screen->addLine(instance->screen->getWidth() - 1, 2,
                              instance->screen->getWidth() - 1, instance->screen->getHeight() - 3,
                              barrier);
    instance->screen->addLine(instance->screen->getWidth() - 1, instance->screen->getHeight() - 3,
                              0, instance->screen->getHeight() - 3,
                              barrier);
    instance->screen->addLine(0, instance->screen->getHeight() - 3,
                              0, 2,
                              barrier);

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            instance->screen->addPixel(2*x+2, y+3,(instance->field->getCell(x, y)) ? white : black);
        }
    }
    instance->screen->render();
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
