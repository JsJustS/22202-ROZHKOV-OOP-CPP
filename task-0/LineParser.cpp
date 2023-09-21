//
// Created by Just on 21.09.2023.
//

#include "LineParser.h"

string LineParser::next() {
    string substring = stringToParse.substr(initialPos, currentPos - initialPos);
    initialPos = currentPos + 1;
    currentPos = stringToParse.find(del, initialPos);
    return substring;
}

bool LineParser::hasNext() const {
    return currentPos != std::string::npos;
}

size_t LineParser::split(std::vector<string> &strings) {
    currentPos = stringToParse.find(del);
    strings.clear();

    // Разбиваем строку на подстроки
    while(this->hasNext()) {
        strings.push_back(this->next());
    }

    // Не забываем добавить последний элемент
    strings.push_back(
            stringToParse.substr(
                    initialPos,
                    std::min(currentPos, stringToParse.size()) - initialPos + 1
                    )
            );

    return strings.size();
}

void LineParser::clear() {
    stringToParse.clear();
    currentPos = std::string::npos;
    initialPos = 0;
}
