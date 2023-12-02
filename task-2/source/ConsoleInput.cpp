//
// Created by Just on 18.11.2023.
//
#include "../header/ConsoleInput.h"

std::vector<std::pair<UserAction, std::vector<std::string>>> ConsoleInput::getQueuedActions() {
    std::string input;
    std::getline(std::cin, input);
    std::vector<std::string> parsed = LineParser::parse(input);

    // HELP
    if (parsed.size() > 2) {
        return {{UserAction::HELP, {}}};
    }

    if (parsed.empty()) {
        return {};
    }

    if (parsed[0] == "dump") {
        return {{UserAction::DUMP, {parsed[1]}}};
    } else if (parsed[0] == "tick" || parsed[0] == "t") {
        return {{UserAction::TICK, {(parsed.size() < 2) ? "1" : parsed[1]}}};
    } else if (parsed[0] == "exit") {
        return {{UserAction::EXIT, {}}};
    } else if (parsed[0] == "help") {
        return {{UserAction::HELP, {}}};
    }
    return {{UserAction::HELP, {}}};
}

