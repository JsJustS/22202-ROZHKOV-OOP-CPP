//
// Created by Just on 21.09.2023.
//

#ifndef INC_22202_ROZHKOV_OOP_CPP_LINEPARSER_H
#define INC_22202_ROZHKOV_OOP_CPP_LINEPARSER_H

#include "utility"
#include "string"
#include "list"

using std::string;

class LineParser {
private:
    string stringToParse;
    size_t currentPos;
public:
    explicit LineParser() {
        currentPos = 0;
    }

    // Загрузить строку в парсер
    void load(string str) {
        stringToParse = std::move(str);
    }

    // Очистить парсер
    void clear();

    // Вернуть новую подстроку
    string next();

    // Проверка на наличие следующей подстроки
    bool hasNext() const;

    // Разбить строку на подстроки
    size_t split(std::list<string> &strings);
};
#endif //INC_22202_ROZHKOV_OOP_CPP_LINEPARSER_H
