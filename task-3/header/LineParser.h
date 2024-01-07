//
// Created by Just on 08.12.2023.
//

#ifndef INC_22202_ROZHKOV_OOP_CPP_TASK_3_LINEPARSER_H
#define INC_22202_ROZHKOV_OOP_CPP_TASK_3_LINEPARSER_H
#include <vector>
#include <string>

class LineParser {
public:
    static std::vector<std::string> parse(const std::string & line, char sep = ' ');

    static bool isNumeric(const std::string & line);
};
#endif //INC_22202_ROZHKOV_OOP_CPP_TASK_3_LINEPARSER_H
