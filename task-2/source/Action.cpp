//
// Created by Just on 01.12.2023.
//

#include "../header/Action.h"

Action::Action() {
    this->task = [](Executor* a, const Arguments& b)->ActionResult{return ActionResult::PASS;};
    this->args = {};
}

Action::Action(Action::Runnable t) {
    this->task = std::move(t);
    this->args = {};
}

Action::Action(const Arguments& a) {
    this->task = [](Executor* a, const Arguments& b)->ActionResult{return ActionResult::PASS;};
    this->args = a;
}

Action::Action(Action::Runnable t, const Action::Arguments &a) {
    this->task = std::move(t);
    this->args = a;
}

ActionResult Action::act(Executor* engine) {
    return this->task(engine, this->args);
}

void Action::loadTask(Action::Runnable t) {
    this->task = std::move(t);
}

void Action::loadArgs(const Action::Arguments &a) {
    this->args = a;
}
