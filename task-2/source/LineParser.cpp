//
// Created by Just on 19.11.2023.
//
#include "../header/LineParser.h"

std::vector <std::string> LineParser::parse(const std::string &line, char sep) {
    std::vector<std::string> vector{};
    int last = (!line.empty() && line[0] == sep) ? 0 : -1;
    int delta = (!line.empty() && line[0] == sep) ? 1 : 1;
    for (int i = 0; i < line.size(); i++) {
        if (line[i] == sep) {
            if (i - last > 1) {
                vector.push_back(line.substr(last + 1, i - last - delta));
            }
            last = i;
        }
    }
    if (!line.empty() && line[line.size()-1] != sep) {
        vector.push_back(line.substr(last + 1, line.size() - last - delta));
    }
    return vector;
}

bool LineParser::isNumeric(const std::string &line) {
    if (line.empty() || (line[0] != '-' && !std::isdigit(line[0]))) {
        return false;
    }

    if (line[0] == '-' && line.length() == 1) {
        return false;
    }

    for (int i = 1; i < line.length(); i++) {
        if (!std::isdigit(line[i])) {
            return false;
        }
    }
    return true;
}

