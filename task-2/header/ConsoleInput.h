//
// Created by Just on 18.11.2023.
//
#ifndef TASK_2_CONSOLEINPUT_H
#define TASK_2_CONSOLEINPUT_H

#include "Input.h"
#include "LineParser.h"
#include <iostream>

/**
 * Extends "Input.h".
 * Processes Console Commands as input
 * */
 class ConsoleInput : public Input {
 public:
     std::vector<std::pair<int, std::string>> getQueuedActions() override;
 };
#endif //TASK_2_CONSOLEINPUT_H
