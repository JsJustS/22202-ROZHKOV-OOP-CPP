//
// Created by Just on 02.12.2023.
//

#ifndef INC_22202_ROZHKOV_OOP_CPP_TASK_2_EXECUTOR_H
#define INC_22202_ROZHKOV_OOP_CPP_TASK_2_EXECUTOR_H
#include <string>

class Executor {
public:
    virtual void setExit(bool code) = 0;
    virtual void log(const std::string& message) = 0;
    virtual bool dump(const std::string& filename) = 0;
    virtual void tickField() = 0;
    virtual void setScreenUpdate(bool bl) = 0;
};
#endif //INC_22202_ROZHKOV_OOP_CPP_TASK_2_EXECUTOR_H
