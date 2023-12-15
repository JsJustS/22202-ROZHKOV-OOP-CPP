//
// Created by Just on 02.12.2023.
//

#ifndef TASK_3_CONFIGMANAGER_H
#define TASK_3_CONFIGMANAGER_H

#include <string>
#include <vector>
#include <memory>
#include "Converters/ConverterFabric.h"
#include "Converters/ConverterMixFabric.h"
#include "Converters/ConverterMuteFabric.h"
#include "Converters/ConverterFadeFabric.h"
#include "LineParser.h"

/**
 * Manages config (no way, couldn't guess).
 * Stores order of converters
 * */
class ConfigManager {
private:
    std::vector<std::shared_ptr<ConverterFabric>> fabricList;
public:
    std::vector<std::shared_ptr<ConverterFabric>> getFabrics();

    void appendConverterFabric(std::vector<std::string>& args);
};
#endif //TASK_3_CONFIGMANAGER_H
