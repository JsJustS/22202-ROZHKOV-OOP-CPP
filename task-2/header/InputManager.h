//
// Created by Just on 18.11.2023.
//

#ifndef TASK_2_INPUTMANAGER_H
#define TASK_2_INPUTMANAGER_H

#include "Input.h"
#include "Actions.h"
#include <vector>
#include <string>

/**
 * Manages user input.
 * */
class InputManager {
private:
    Input* input;
    std::vector<Action> queue;
public:
    InputManager();
    ~InputManager();

    void setInputDevice(Input& inp);
    std::vector<Action> getUserActions();
    void tick();
};
#endif //TASK_2_INPUTMANAGER_H
