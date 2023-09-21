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
    for (auto & it : dictionary) {
        words.push_back(it.first);
        amount++;
    }
    return amount;
}
