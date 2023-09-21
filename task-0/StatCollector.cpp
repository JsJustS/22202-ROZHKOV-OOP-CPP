//
// Created by Just on 21.09.2023.
//

#include "StatCollector.h"

void StatCollector::add(const string& word) {
    dictionary[word] = this->getWordStat(word) + 1;
}

size_t StatCollector::getWordStat(const string& word) {
    return dictionary.find(word) != dictionary.end()? dictionary[word] : 0;
}

size_t StatCollector::loadAllWords(std::vector<string> &words) {
    size_t amount = 0;
    std::vector<std::pair<string, size_t>> wordsAndValues;
    for (auto & it : dictionary) {
        amount += it.second;
        wordsAndValues.emplace_back(it.first, it.second);
    }

    std::sort(
            wordsAndValues.begin(),
            wordsAndValues.end(),
            [](auto &left, auto &right) {
                return left.second < right.second;
            }
    );

    for (auto & it : wordsAndValues) {
        words.push_back(it.first);
    }

    return amount;
}
