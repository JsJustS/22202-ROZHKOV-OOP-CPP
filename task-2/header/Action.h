//
// Created by Just on 25.11.2023.
//

#ifndef INC_22202_ROZHKOV_OOP_CPP_TASK_2_ACTION_H
#define INC_22202_ROZHKOV_OOP_CPP_TASK_2_ACTION_H

#include <functional>
#include <utility>
#include <vector>
#include <string>
#include "Executor.h"

enum ActionResult {
    PASS,
    CONSUME,
    TERMINATE
};

class Action {
    typedef std::function<ActionResult(Executor*, const std::vector<std::string>&)> Runnable;
    typedef std::vector<std::string> Arguments;
private:
    Runnable task;
    Arguments args;
public:
    Action();
    explicit Action(Runnable t);
    explicit Action(const Arguments& a);
    Action(Runnable t, const Arguments& a);

    ActionResult act(Executor* engine);

    void loadTask(Runnable t);
    void loadArgs(const Arguments& a);
};
#endif //INC_22202_ROZHKOV_OOP_CPP_TASK_2_ACTION_H
