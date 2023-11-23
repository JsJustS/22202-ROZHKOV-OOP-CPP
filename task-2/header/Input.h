//
// Created by Just on 18.11.2023.
//

#ifndef TASK_2_INPUT_H
#define TASK_2_INPUT_H

#include <vector>
#include <string>

/**
 * Interface for Input Classes.
 * Organizes bridge between user inputs and
 * InputManager.
 * */
class Input {
public:
    virtual ~Input() = default;

    virtual std::vector<std::pair<int, std::string>> getQueuedActions() = 0;
};
#endif //TASK_2_INPUT_H
