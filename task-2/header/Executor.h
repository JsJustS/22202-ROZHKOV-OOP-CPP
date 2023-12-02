//
// Created by Just on 02.12.2023.
//

#ifndef INC_22202_ROZHKOV_OOP_CPP_TASK_2_EXECUTOR_H
#define INC_22202_ROZHKOV_OOP_CPP_TASK_2_EXECUTOR_H
#include <string>
/**
 * Abstract class
 * Provides contract between Action and Engine classes
 * */
class Executor {
public:
    virtual void init() = 0;
    virtual void stop() = 0;
    virtual void setExit(bool code) = 0;

    virtual void log(const std::string& message) = 0;
    virtual bool dump(const std::string& filename) = 0;

    virtual void tickGameLogic() = 0;
    virtual void setScreenUpdate(bool bl) = 0;
};
#endif //INC_22202_ROZHKOV_OOP_CPP_TASK_2_EXECUTOR_H
