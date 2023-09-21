//
// Created by Just on 21.09.2023.
//

#include "LineParser.h"

string LineParser::next() {
    string substring;
    size_t i;
    for (i = currentPos; i < stringToParse.length(); ++i) {
        if (del.find(stringToParse[i]) == std::string::npos) {
            break;
        }
        substring += stringToParse[i];
    }
    currentPos = i + 1;
    return substring;
}

bool LineParser::hasNext() const {
    return currentPos < stringToParse.length();
}

size_t LineParser::split(std::list<string> &strings) {
    strings.clear();

    // Разбиваем строку на подстроки
    while(this->hasNext()) {
        strings.push_back(this->next());
    }

    return strings.size();
}

void LineParser::clear() {
    stringToParse.clear();
    currentPos = 0;
}
