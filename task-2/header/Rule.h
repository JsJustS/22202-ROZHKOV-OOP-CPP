//
// Created by Just on 18.11.2023.
//

#ifndef INC_22202_ROZHKOV_OOP_CPP_TASK_2_RULE_H
#define INC_22202_ROZHKOV_OOP_CPP_TASK_2_RULE_H
/**
 * Wrapper for a rule
 * */

#include <string>
#include <cstring>

class Rule {
private:
    char setSize;
    char* set;
public:
    Rule();

    ~Rule();

    bool isApplicable(char numberOfCells) const;

    void add(char numberOfCells);

    void remove(char numberOfCells);

    void clear();

    bool isEmpty() const;

    std::string toString() const;
};
#endif //INC_22202_ROZHKOV_OOP_CPP_TASK_2_RULE_H
