//
// Created by Just on 01.12.2023.
//

#include "../header/Actions.h"

std::map<UserAction, Actions::Runnable> Actions::RUNNABLES = {
        {
                UserAction::HELP, [](Executor *engine, const std::vector<std::string> & data) -> ActionResult {
            Actions::printHelpList(engine);

            return ActionResult::PASS;
        }
        },
        {
                UserAction::EXIT, [](Executor *engine, const std::vector<std::string> & data) -> ActionResult {
            engine->setExit(true);

            return ActionResult::TERMINATE;
        }
        },
        {
                UserAction::DUMP, [](Executor *engine, const std::vector<std::string> & data) -> ActionResult {
            if (engine->dump(data[0])) {
                engine->log("Universe dumped!");
            }

            return ActionResult::CONSUME;
        }
        },
        {
                UserAction::TICK, [](Executor *engine, const std::vector<std::string> & data) -> ActionResult {
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
                engine->tickField();
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
