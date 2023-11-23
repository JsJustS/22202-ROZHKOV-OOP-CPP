//
// Created by Just on 18.11.2023.
//
#include "../header/InputManager.h"
#include "../header/Engine.h"

InputManager::InputManager() {
    this->input = nullptr;
}

InputManager::~InputManager() {
    delete this->input;
}

void InputManager::setInputType(Input &inp) {
    this->input = &inp;
}

void InputManager::processActions() {
    std::vector<std::pair<int, std::string>> queue = this->input->getQueuedActions();

    if (queue.empty()) {
        Engine::setScreenUpdate(true);
        return;
    }

    for (std::pair<int, std::string> pair : queue) {
        ACTION action = static_cast<ACTION>(pair.first);
        std::string data = pair.second;
        switch (action) {

            case DUMP: {
                this->processDUMP(data);
                break;
            }
            case TICK: {
                this->processTICK(data);
                break;
            }
            case EXIT: {
                this->processEXIT(data);
                break;
            }
            case HELP: {
                this->processHELP(data);
                break;
            }
        }
    }
}

void InputManager::processDUMP(const std::string &data) {
    //todo: check data for integrity

    Engine::dump(data);
    Engine::log("Universe dumped!");
}

void InputManager::processTICK(const std::string &data) {
    if (!LineParser::isNumeric(data)) {
        processHELP("");
        return;
    }

    int n = std::stoi(data);
    if (n < 1) {
        processHELP("");
        return;
    }

    for (int i = 0; i < n; ++i) {
        Engine::tickField();
    }

    Engine::setScreenUpdate(true);
}

void InputManager::processEXIT(const std::string &data) {
    Engine::setExit(true);
}

void InputManager::processHELP(const std::string &data) {
    Engine::log("All existing commands:");
    Engine::log("* dump <filename> - save current iteration as a universe.");
    Engine::log("* tick <n=1> - iterate for n generations.");
    Engine::log("* t <n=1> - same as \"tick\".");
    Engine::log("* exit - leave program.");
    Engine::log("* help - print this text.");
}
