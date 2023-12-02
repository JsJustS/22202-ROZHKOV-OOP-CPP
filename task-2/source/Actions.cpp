//
// Created by Just on 01.12.2023.
//

#include "../header/Actions.h"

#define TASK [](Executor *engine, const std::vector<std::string> & data) -> ActionResult

// INIT RUNNABLES MAP
std::map<UserAction, Actions::Runnable> Actions::RUNNABLES = {
        {
                UserAction::HELP, TASK {
            Actions::printHelpList(engine);

            return ActionResult::PASS;
        }
        },
        {
                UserAction::EXIT,  TASK {
            engine->setExit(true);

            return ActionResult::TERMINATE;
        }
        },
        {
                UserAction::DUMP, TASK {
            if (engine->dump(data[0])) {
                engine->log("Universe dumped!");
            }

            return ActionResult::CONSUME;
        }
        },
        {
                UserAction::TICK, TASK {
            if (!LineParser::isNumeric(data[0])) {
                Actions::printHelpList(engine);
                return ActionResult::PASS;
            }

            int n = std::stoi(data[0]);
            if (n < 1) {
                Actions::printHelpList(engine);
                return ActionResult::PASS;
            }

            for (int i = 0; i < n; ++i) {
                engine->tickGameLogic();
            }

            engine->setScreenUpdate(true);
            return ActionResult::CONSUME;
        }
        }
};

Action Actions::generate(UserAction actionCode, const std::vector<std::string> &arg) {
    return Action(Actions::getRunnable(actionCode), arg);
}

Actions::Runnable Actions::getRunnable(UserAction actionCode) {
    return Actions::RUNNABLES[actionCode];
}

void Actions::printHelpList(Executor *engine) {
    engine->log("All existing commands:");
    engine->log("* dump <filename> - save current iteration as a universe.");
    engine->log("* tick <n=1> - iterate for n generations.");
    engine->log("* t <n=1> - same as \"tick\".");
    engine->log("* exit - leave program.");
    engine->log("* help - print this text.");
}
