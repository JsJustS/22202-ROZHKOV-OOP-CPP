//
// Created by Just on 02.12.2023.
//

#ifndef TASK_3_CONVERTER_H
#define TASK_3_CONVERTER_H
/**
 * Abstract interface for Converters.
 * */
class Converter {
public:
    virtual ~Converter()= default;
    virtual std::string getHelp() = 0;
    virtual Sample modify(std::vector<Sample>& sample) = 0;
};
#endif //TASK_3_CONVERTER_H
