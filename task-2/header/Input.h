//
// Created by Just on 18.11.2023.
//

#ifndef TASK_2_INPUT_H
#define TASK_2_INPUT_H

#include <vector>
#include <string>

enum UserAction {
    DUMP,
    TICK,
    EXIT,
    HELP
};

/**
 * Interface for Input Classes.
 * Organizes bridge between user inputs and
 * InputManager.
 * */
class Input {
public:
    virtual ~Input() = default;

    virtual std::vector<std::pair<UserAction, std::vector<std::string>>> getQueuedActions() = 0;
};
#endif //TASK_2_INPUT_H
