//
// Created by Just on 18.11.2023.
//
#include "../header/ConsoleInput.h"

std::vector<std::pair<int, std::string>> ConsoleInput::getQueuedActions() {
    std::string input;
    std::getline(std::cin, input);
    std::vector<std::string> parsed = LineParser::parse(input);

    // HELP
    if (parsed.size() > 2) {
        return {{3, ""}};
    }

    if (parsed.empty()) {
        return {};
    }

    if (parsed[0] == "dump") {
        return {{0, parsed[1]}};
    } else if (parsed[0] == "tick" || parsed[0] == "t") {
        return {{1, (parsed.size() < 2) ? "1" : parsed[1]}};
    } else if (parsed[0] == "exit") {
        return {{2, ""}};
    } else if (parsed[0] == "help") {
        return {{3, ""}};
    }
    return {{3, ""}};
}

