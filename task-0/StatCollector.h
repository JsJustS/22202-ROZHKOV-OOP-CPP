//
// Created by Just on 21.09.2023.
//

#ifndef INC_22202_ROZHKOV_OOP_CPP_STATCOLLECTOR_H
#define INC_22202_ROZHKOV_OOP_CPP_STATCOLLECTOR_H

#include "utility"
#include "string"
#include "map"
#include "vector"
#include "algorithm"

using std::string;
class StatCollector {
private:
    std::map<string, size_t> dictionary;
public:
    explicit StatCollector() = default;

    void add(const string& word);

    size_t loadAllWords(std::vector<string> &words, bool reverse);

    size_t getWordStat(const string& word);

    void clear() {
        dictionary.clear();
    }
};
#endif //INC_22202_ROZHKOV_OOP_CPP_STATCOLLECTOR_H
