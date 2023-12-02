//
// Created by Just on 18.11.2023.
//
#include "../header/ConfigManager.h"

ConfigManager::ConfigManager() {
    this->fileFormat = "";
    this->universeName = "";
    this->fieldWidth = 0;
    this->fieldHeight = 0;
    this->birthRule = new Rule();
    this->survivalRule = new Rule();

    this->logger = nullptr;
}

std::vector<std::pair<int, int>> ConfigManager::load(const std::string& universe) {
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
            this->log("Junk Data on Line " + std::to_string(lineIndex));
            continue;
        }

        int x = std::stoi(parsed[0]);
        int y = std::stoi(parsed[1]);

        coords.emplace_back(x, y);
    }

    // if file was not broken, return coords
    bool isOk = reader.isOk();

    reader.close();

    // check if something missing
    checkForIntegrity();

    return (isOk) ? coords : std::vector<std::pair<int, int>>{};
}

std::string ConfigManager::toString() const {
    std::string string{};
    string += "Config{";
    string += "fileFormat=" + this->fileFormat + ", ";
    string += "universeName=" + this->universeName + ", ";
    string += "fieldWidth=" + std::to_string(this->fieldWidth) + ", ";
    string += "fieldHeight=" + std::to_string(this->fieldHeight) + ", ";
    string += "birthRule=" + this->birthRule->toString() + ", ";
    string += "survivalRule=" + this->survivalRule->toString() + "}";
    return string;
}

std::unordered_map<std::string, std::string> ConfigManager::toMap() const {
    std::unordered_map<std::string, std::string> map{};
    map["fileFormat"] = this->fileFormat;
    map["universeName"] = this->universeName;
    map["fieldWidth"] = std::to_string(this->fieldWidth);
    map["fieldHeight"] = std::to_string(this->fieldHeight);
    map["birthRule"] = this->birthRule->toString();
    map["survivalRule"] = this->survivalRule->toString();
    return map;
}

std::string ConfigManager::getFileFormat() const {return this->fileFormat;}
std::string ConfigManager::getUniverseName() const {return this->universeName;}
int ConfigManager::getFieldWidth() const {return this->fieldWidth;}
int ConfigManager::getFieldHeight() const {return this->fieldHeight;}
bool ConfigManager::canBirth(char count) const {
    return this->birthRule->isApplicable(count);
}
bool ConfigManager::canSurvive(char count) const {
    return this->survivalRule->isApplicable(count);
}

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
        this->log("ConfigWarning: No Universe Name found, using generated \"" + this->universeName + "\".");
    }
    if (fieldWidth < 1 || fieldWidth > std::numeric_limits<int>::max() ||
        fieldHeight < 1 || fieldHeight > std::numeric_limits<int>::max()) {
        this->fieldWidth = 20;
        this->fieldHeight = 20;
        this->log("ConfigWarning: Bad Field Size (or no Field Size) provided, using " +
        std::to_string(this->fieldWidth) + "/" + std::to_string(this->fieldHeight) + ".");
    }
    if (birthRule->isEmpty()) {
        this->log("ConfigWarning: No rule for Birth provided.");
    }
    if (survivalRule->isEmpty()) {
        this->log("ConfigWarning: No rule for Survival provided.");
    }
}

void ConfigManager::processFileFormat(const std::vector<std::string> &data) {
    if (data.size() != 2) {throw std::invalid_argument("File Format is not supported.");}
    this->fileFormat = data[1];
}

void ConfigManager::processUniverseName(const std::vector<std::string> &data, int lineIndex) {
    if (data.size() < 2) {
        this->log("Junk Data on Line " + std::to_string(lineIndex));
        return;
    }

    for (int i = 1; i < data.size() - 1; i++) {
        this->universeName += data[i] + " ";
    }
    this->universeName += data[data.size() - 1];
}

void ConfigManager::processRules(const std::vector<std::string> &data, int lineIndex) {
    if (data.size() != 2) {
        this->log("Junk Data on Line " + std::to_string(lineIndex));
        return;
    }

    std::vector<std::string> pair = LineParser::parse(data[1], '/');
    for (std::string ruleset : pair) {
        bool isB = ruleset[0] == 'B';
        bool isS = ruleset[0] == 'S';
        if (!isB && !isS) {
            this->log("Junk Data on Line " + std::to_string(lineIndex));
            continue;
        }
        for (int i = 1; i < ruleset.length(); i++) {
            if (!LineParser::isNumeric(ruleset.substr(i, 1))) {
                this->log("Junk Data on Line " + std::to_string(lineIndex));
                continue;
            }
            char cell = (char) std::stoi(ruleset.substr(i, 1));
            if (isB) {
                this->birthRule->add(cell);
            } else {
                this->survivalRule->add(cell);
            }
        }
    }
}

void ConfigManager::processSize(const std::vector<std::string> &data, int lineIndex) {
    if (data.size() != 2) {
        this->log("Junk Data on Line " + std::to_string(lineIndex));
        return;
    }

    std::vector<std::string> pair = LineParser::parse(data[1], '/');
    if (pair.size() != 2 || !LineParser::isNumeric(pair[0]) || !LineParser::isNumeric(pair[1])) {
        this->log("Junk Data on Line " + std::to_string(lineIndex));
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

ConfigManager::~ConfigManager() {
    delete this->birthRule;
    delete this->survivalRule;
}

std::string ConfigManager::getRulesAsString() {
    std::string stringBirth = "B";
    std::string stringSurvive = "S";
    for (char i = 0; i < 9 ; ++i) {
        if (this->birthRule->isApplicable(i)) {
            stringBirth += std::to_string((int)i);
        }
        if (this->survivalRule->isApplicable(i)) {
            stringSurvive += std::to_string((int)i);
        }
    }
    return stringBirth + "/" + stringSurvive;
}

void ConfigManager::setLogger(std::ostream& out) {
    this->logger = &out;
}

void ConfigManager::log(const std::string &message) {
    if (this->logger == nullptr) return;
    (*this->logger) << message << std::endl;
}
