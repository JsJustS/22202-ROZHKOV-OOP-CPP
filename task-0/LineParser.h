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

    // Ресетнуть парсер
    void reset();

    // Вернуть новую подстроку
    string next();

    // Проверка на наличие следующей подстроки
    bool hasNext() const;
public:
    explicit LineParser(string str): stringToParse(std::move(str)) {
        currentPos = 0;
    }

    // Загрузить строку в парсер
    void load(string str) {
        reset();
        stringToParse = std::move(str);
    }

    // Разбить строку на подстроки
    std::list<string> split();
};
#endif //INC_22202_ROZHKOV_OOP_CPP_LINEPARSER_H
