//
// Created by Just on 21.09.2023.
//

#include "LineParser.h"

string LineParser::next() {
    string substring;
    size_t i;
    while (substring.empty() && currentPos < stringToParse.length()) {
        for (i = currentPos; i < stringToParse.length(); ++i) {
            if (!std::isalnum(stringToParse[i])) {
                break;
            }
            substring += stringToParse[i];
        }
        currentPos = i + 1;
    }
    return substring;
}

bool LineParser::hasNext() const {
    return currentPos < stringToParse.length();
}

size_t LineParser::split(std::list<string> &strings) {
    strings.clear();

    // Разбиваем строку на подстроки
    while(this->hasNext()) {
        string nextSub = this->next();
        if (nextSub.empty()) continue;
        strings.push_back(nextSub);
    }

    return strings.size();
}

void LineParser::clear() {
    stringToParse.clear();
    currentPos = 0;
}
