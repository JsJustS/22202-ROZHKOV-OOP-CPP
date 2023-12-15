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
        if (args.size() != 3) { throw WrongArgumentsError("Wrong amount of arguments for MUTE converter."); }
        if (!LineParser::isNumeric(args[1]) || !LineParser::isNumeric(args[2])) {
            throw WrongArgumentsError("Wrong argument types provided for MUTE converter.");
        }
        int secondStart = std::stoi(args[1]);
        int secondEnd = std::stoi(args[2]);
        this->fabricList.push_back(std::make_shared<ConverterMuteFabric>(secondStart, secondEnd));
    } else if (converterName == "mix") {
        if (args.size() < 3 || args.size() > 4) { throw WrongArgumentsError("Wrong amount of arguments for MIX converter."); }
        if (args[1][0] != '$' || !LineParser::isNumeric(args[1].substr(1)) || !LineParser::isNumeric(args[2])) {
            throw WrongArgumentsError("Wrong argument types provided for MIX converter.");
        }
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
    } else if (converterName == "fadein" || converterName == "fadeout") {
        if (args.size() != 4) { throw WrongArgumentsError("Wrong amount of arguments for FADEIN/FADEOUT converter."); }
        if (!LineParser::isNumeric(args[1]) || !LineParser::isNumeric(args[2]) || !LineParser::isNumeric(args[3])) {
            throw WrongArgumentsError("Wrong argument types provided for FADEIN/FADEOUT converter.");
        }
        int secondStart = std::stoi(args[1]);
        int secondEnd = std::stoi(args[2]);
        int k = std::stoi(args[3]);
        bool isIn = converterName == "fadein";
        this->fabricList.push_back(std::make_shared<ConverterFadeFabric>(secondStart, secondEnd, k, isIn));
    }
}
