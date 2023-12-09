//
// Created by Just on 02.12.2023.
//
#include <cstring>
#include <memory>
#include "../header/ConfigManager.h"

std::vector<std::shared_ptr<ConverterFabric>> ConfigManager::getFabrics() {
    return this->fabricList;
}

void ConfigManager::appendConverterFabric(std::vector<std::string>& args) {
    if (args.empty()) {return;}

    std::string converterName = args[0];
    if (converterName == "mute") {
        //todo: throw argument count error
        if (args.size() != 3) { return; }
        //todo: throw argument error
        if (!LineParser::isNumeric(args[1]) || !LineParser::isNumeric(args[2])) {return;}
        int secondStart = std::stoi(args[1]);
        int secondEnd = std::stoi(args[2]);
        this->fabricList.push_back(std::make_shared<ConverterMuteFabric>(secondStart, secondEnd));
    } else if (converterName == "mix") {
        //todo: throw argument count error
        if (args.size() < 3 || args.size() > 4) { return; }
        //todo: throw argument error
        if (args[1][0] != '$' || !LineParser::isNumeric(args[1].substr(1)) || !LineParser::isNumeric(args[2])) {return;}
        int streamId = std::stoi(args[1].substr(1));
        int secondStart = std::stoi(args[2]);
        int secondEnd;
        if (args.size() == 3) {
            secondEnd = -1;
        } else {
            if (!LineParser::isNumeric(args[3])) {return;}
            secondEnd = std::stoi(args[3]);
        }
        this->fabricList.push_back(std::make_shared<ConverterMixFabric>(streamId, secondStart, secondEnd));
    } else if (converterName == "reverb") {
        //todo: throw argument count error
        if (args.size() != 2) { return; }
        //todo: throw argument error
        if (!LineParser::isNumeric(args[1])) { return; }
        int echoCount = std::stoi(args[1]);
        this->fabricList.push_back(std::make_shared<ConverterReverbFabric>(echoCount));
    }
}
