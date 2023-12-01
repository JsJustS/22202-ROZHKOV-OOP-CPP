//
// Created by Just on 01.12.2023.
//

#ifndef INC_22202_ROZHKOV_OOP_CPP_TASK_2_ACTIONS_H
#define INC_22202_ROZHKOV_OOP_CPP_TASK_2_ACTIONS_H

#include <map>
#include "Action.h"
#include "Input.h"
#include "LineParser.h"

class Actions {
    typedef std::function<ActionResult(Executor*, const std::vector<std::string>&)> Runnable;
private:
    static std::map<UserAction, Runnable> RUNNABLES;

    static Runnable getRunnable(UserAction actionCode);

    static void printHelpList(Executor* engine);
public:
    static Action generate(UserAction actionCode, const std::vector<std::string>& arg);
};
#endif //INC_22202_ROZHKOV_OOP_CPP_TASK_2_ACTIONS_H
