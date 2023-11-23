//
// Created by Just on 18.11.2023.
//

#ifndef TASK_2_INPUTMANAGER_H
#define TASK_2_INPUTMANAGER_H

#include "Input.h"
#include <vector>
#include <string>

/**
 * Manages user input.
 * */
class InputManager {
private:
    Input* input;

    enum ACTION {
        DUMP,
        TICK,
        EXIT,
        HELP
    };
public:
    InputManager();
    ~InputManager();

    void setInputType(Input& inp);
    void processActions();

    void processDUMP(const std::string& data);
    void processTICK(const std::string& data);
    void processEXIT(const std::string& data);
    void processHELP(const std::string& data);
};
#endif //TASK_2_INPUTMANAGER_H
