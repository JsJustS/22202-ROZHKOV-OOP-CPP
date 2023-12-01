//
// Created by Just on 18.11.2023.
//
#include "../header/InputManager.h"

InputManager::InputManager() {
    this->input = nullptr;
}

InputManager::~InputManager() {
    delete this->input;
}

void InputManager::setInputDevice(Input &inp) {
    this->input = &inp;
}

void InputManager::tick() {
    std::vector<std::pair<UserAction, std::vector<std::string>>> freshUserActions = this->input->getQueuedActions();
    for (const std::pair<UserAction, std::vector<std::string>> &userActionWithData: freshUserActions) {
        this->queue.push_back(
                Actions::generate(
                        userActionWithData.first,
                        userActionWithData.second
                )
        );
    }
}

std::vector<Action> InputManager::getUserActions() {
    std::vector<Action> temp(this->queue);
    this->queue.clear();
    return temp;
}
