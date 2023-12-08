//
// Created by Just on 02.12.2023.
//

#ifndef TASK_3_CONFIGMANAGER_H
#define TASK_3_CONFIGMANAGER_H

#include <string>
#include <vector>
#include "ConverterFabric.h"

/**
 * Manages config (no way, couldn't guess).
 * Stores order of converters
 * */
class ConfigManager {
private:
public:
    std::vector<ConverterFabric> getFabrics();

    void appendConverterFabric(std::vector<std::string> args);
};
#endif //TASK_3_CONFIGMANAGER_H
