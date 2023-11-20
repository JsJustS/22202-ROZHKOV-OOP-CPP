//
// Created by Just on 18.11.2023.
//

#ifndef TASK_2_CONFIG_H
#define TASK_2_CONFIG_H

#include <unordered_map>
#include <string>
#include <limits>
#include <chrono>
#include "Rule.h"
#include "Field.h"

/**
 * RunTime container for Game Settings:
 * Rules, #R
 * Field Size, #S
 * Universe name, #N
 * */
class ConfigManager {
private:
    std::string fileFormat;
    std::string universeName;
    int fieldWidth;
    int fieldHeight;
    Rule birthRule;
    Rule survivalRule;

    std::ostream* logger;

    void checkForIntegrity();
    void parseMeta(const std::vector<std::string> & data, int lineIndex);
    void processFileFormat(const std::vector<std::string> & data);
    void processUniverseName(const std::vector<std::string> & data, int lineIndex);
    void processRules(const std::vector<std::string> & data, int lineIndex);
    void processSize(const std::vector<std::string> & data, int lineIndex);
public:

    ConfigManager(std::ostream& out);

    // loads settings from file with the specified name
    void load(const std::string& universe, Field& field);

    // dumps config as a string
    std::string toString() const;

    // dumps config as a hashMap
    std::unordered_map<std::string, std::string> toMap() const;

    std::string getFileFormat() const;
    std::string getUniverseName() const;
    int getFieldWidth() const;
    int getFieldHeight() const;
    Rule getBirthRule() const;
    Rule getSurvivalRule() const;
};
#endif //TASK_2_CONFIG_H
