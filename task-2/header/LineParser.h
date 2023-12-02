//
// Created by Just on 19.11.2023.
//

#ifndef INC_22202_ROZHKOV_OOP_CPP_TASK_2_LINEPARSER_H
#define INC_22202_ROZHKOV_OOP_CPP_TASK_2_LINEPARSER_H

#include <vector>
#include <string>

class LineParser {
public:
    static std::vector<std::string> parse(const std::string & line, char sep = ' ');

    static bool isNumeric(const std::string & line);
};
#endif //INC_22202_ROZHKOV_OOP_CPP_TASK_2_LINEPARSER_H
