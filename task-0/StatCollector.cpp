//
// Created by Just on 21.09.2023.
//

#include "StatCollector.h"

void StatCollector::add(const string& word) {
    if (word.empty()) return;
    dictionary[word] = this->getWordStat(word) + 1;
}

size_t StatCollector::getWordStat(const string& word) {
    return dictionary.find(word) != dictionary.end()? dictionary[word] : 0;
}

size_t StatCollector::getFullAmountOfWords() {
    size_t amount = 0;
    for (auto & it : dictionary) {
        amount += it.second;
    }
    return amount;
}

std::list<string> StatCollector::getAll(bool sortDirector) {
    std::list<std::pair<string, size_t>> wordsAndValues;
    for (auto & it : dictionary) {
        wordsAndValues.emplace_back(it.first, it.second);
    }

    wordsAndValues.sort([&sortDirector](auto &left, auto &right) {
        return (sortDirector) ? left.second < right.second : left.second > right.second;
    });

    std::list<string> words;
    for (auto & it : wordsAndValues) {
        words.push_back(it.first);
    }

    return words;
}
