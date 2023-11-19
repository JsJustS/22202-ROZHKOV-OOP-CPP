//
// Created by Just on 18.11.2023.
//
#include <vector>
#include <ctime>
#include "../header/ConfigManager.h"
#include "../header/FileReader.h"
#include "../header/LineParser.h"

ConfigManager::ConfigManager(std::ostream& out) {
    this->fileFormat = "";
    this->universeName = "";
    this->fieldWidth = 0;
    this->fieldHeight = 0;
    this->birthRule = Rule();
    this->survivalRule = Rule();
    this->logger = &out;
}

void ConfigManager::load(const std::string& universe, Field field) {
    FileReader reader(universe);
    reader.open();

    if (!reader.isOpen()) {
        reader.close();
        throw std::runtime_error("Could not open file \"" + universe + "\".");
    }

    // check file format
    if (reader.hasNext()) {
        std::vector<std::string> parsed = LineParser::parse(reader.next());
        if (!parsed.empty() && parsed[0][0] == '#') {
            processFileFormat(parsed);
        } else {
            throw std::invalid_argument("No File Format found.");
        }
    }

    // parse file if format is okay
    int lineIndex = 1;
    std::vector<std::pair<int, int>> coords{};
    while(reader.hasNext()) {
        lineIndex++;

        std::vector<std::string> parsed = LineParser::parse(reader.next());
        if (parsed.empty()) {continue;}
        if (parsed[0][0] == '#') {
            parseMeta(parsed, lineIndex);
            continue;
        }

        if (parsed.size() != 2 || !LineParser::isNumeric(parsed[0]) || !LineParser::isNumeric(parsed[1])) {
            (*this->logger) << "Junk Data on Line " << lineIndex << std::endl;
            continue;
        }

        int x = std::stoi(parsed[0]);
        int y = std::stoi(parsed[1]);

        coords.emplace_back(x, y);
    }

    // if file was not broken, load field
    if (reader.isOk()) {
        field.load(coords);
    }

    reader.close();

    // check if something missing
    checkForIntegrity();
}

std::string ConfigManager::toString() const {
    std::string string{};
    string += "Config{";
    string += "fileFormat=" + this->fileFormat + ", ";
    string += "universeName=" + this->universeName + ", ";
    string += "fieldWidth=" + std::to_string(this->fieldWidth) + ", ";
    string += "fieldHeight=" + std::to_string(this->fieldHeight) + ", ";
    string += "birthRule=" + this->birthRule.toString() + ", ";
    string += "survivalRule=" + this->survivalRule.toString() + "}";
    return string;
}

std::unordered_map<std::string, std::string> ConfigManager::toMap() const {
    std::unordered_map<std::string, std::string> map{};
    map["fileFormat"] = this->fileFormat;
    map["universeName"] = this->universeName;
    map["fieldWidth"] = std::to_string(this->fieldWidth);
    map["fieldHeight"] = std::to_string(this->fieldHeight);
    map["birthRule"] = this->birthRule.toString();
    map["survivalRule"] = this->survivalRule.toString();
    return map;
}

std::string ConfigManager::getFileFormat() const {return this->fileFormat;}
std::string ConfigManager::getUniverseName() const {return this->universeName;}
int ConfigManager::getFieldWidth() const {return this->fieldWidth;}
int ConfigManager::getFieldHeight() const {return this->fieldHeight;}
Rule ConfigManager::getBirthRule() const {return this->birthRule;}
Rule ConfigManager::getSurvivalRule() const {return this->survivalRule;}

void ConfigManager::checkForIntegrity() {
    if (fileFormat.empty()) {
        throw std::invalid_argument("No File Format found.");
    } else if (fileFormat != "1.06") {
        throw std::invalid_argument("File Format \"" + fileFormat + "\" is not supported.");
    }

    if (universeName.empty()) {
        const auto p1 = std::chrono::system_clock::now();
        long long seconds = std::chrono::duration_cast<std::chrono::seconds>(p1.time_since_epoch()).count();
        this->universeName = "Uni" + std::to_string(seconds);
        (*this->logger) << "ConfigWarning: No Universe Name found, using generated \""
        << this->universeName <<"\"."<< std::endl;
    }
    if (fieldWidth < 1 || fieldWidth > std::numeric_limits<int>::max() ||
        fieldHeight < 1 || fieldHeight > std::numeric_limits<int>::max()) {
        this->fieldWidth = 20;
        this->fieldHeight = 20;
        (*this->logger) << "ConfigWarning: Bad Field Size (or no Field Size) provided, using "
        << this->fieldWidth << "/" << this->fieldHeight <<"."<< std::endl;
    }
    if (birthRule.isEmpty()) {
        (*this->logger) << "ConfigWarning: No rule for Birth provided." << std::endl;
    }
    if (survivalRule.isEmpty()) {
        (*this->logger) << "ConfigWarning: No rule for Survival provided." << std::endl;
    }
}

void ConfigManager::processFileFormat(const std::vector<std::string> &data) {
    if (data.size() != 2) {throw std::invalid_argument("File Format is not supported.");}
    this->fileFormat = data[1];
}

void ConfigManager::processUniverseName(const std::vector<std::string> &data, int lineIndex) {
    if (data.size() < 2) {
        (*this->logger) << "Junk Data on Line " << lineIndex << std::endl;
        return;
    }

    for (int i = 1; i < data.size() - 1; i++) {
        this->universeName += data[i] + " ";
    }
    this->universeName += data[data.size() - 1];
}

void ConfigManager::processRules(const std::vector<std::string> &data, int lineIndex) {
    if (data.size() != 2) {
        (*this->logger) << "Junk Data on Line " << lineIndex << std::endl;
        return;
    }

    std::vector<std::string> pair = LineParser::parse(data[1], '/');
    for (std::string ruleset : pair) {
        bool isB = ruleset[0] == 'B';
        bool isS = ruleset[0] == 'S';
        if (!isB && !isS) {
            (*this->logger) << "Junk Data on Line " << lineIndex << std::endl;
            continue;
        }
        for (int i = 1; i < ruleset.length(); i++) {
            if (!LineParser::isNumeric(ruleset.substr(i, 1))) {
                (*this->logger) << "Junk Data on Line " << lineIndex << std::endl;
                continue;
            }
            char cell = (char) std::stoi(ruleset.substr(i, 1));
            if (isB) {
                this->birthRule.add(cell);
            } else {
                this->survivalRule.add(cell);
            }
        }
    }
}

void ConfigManager::processSize(const std::vector<std::string> &data, int lineIndex) {
    if (data.size() != 2) {
        (*this->logger) << "Junk Data on Line " << lineIndex << std::endl;
        return;
    }

    std::vector<std::string> pair = LineParser::parse(data[1], '/');
    if (pair.size() != 2 || !LineParser::isNumeric(pair[0]) || !LineParser::isNumeric(pair[1])) {
        (*this->logger) << "Junk Data on Line " << lineIndex << std::endl;
        return;
    }

    this->fieldWidth = std::stoi(pair[0]);
    this->fieldHeight = std::stoi(pair[1]);
}

void ConfigManager::parseMeta(const std::vector<std::string> &data, int lineIndex) {
    if (data[0][0] == '#') {
        const std::string& header = data[0];
        if (header == "#N") {
            processUniverseName(data, lineIndex);
        } else if (header == "#R") {
            processRules(data, lineIndex);
        } else if (header == "#S") {
            processSize(data, lineIndex);
        }
    }
}
