//
// Created by Just on 21.09.2023.
//

#ifndef INC_22202_ROZHKOV_OOP_CPP_LINEPARSER_H
#define INC_22202_ROZHKOV_OOP_CPP_LINEPARSER_H

#include <utility>

#include "string"
#include "vector"

using std::string;

class LineParser {
private:
    string del;
    string stringToParse;
    size_t currentPos;
    size_t initialPos;
public:
    explicit LineParser(string delimiter) {
        del = std::move(delimiter);
        currentPos = std::string::npos;
        initialPos = 0;
    }

    void load(string str) {
        stringToParse = std::move(str);
    }

    void clear();

    string next();

    bool hasNext() const;

    size_t split(std::vector<string> &strings);
};
#endif //INC_22202_ROZHKOV_OOP_CPP_LINEPARSER_H
