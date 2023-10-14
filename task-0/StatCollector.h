//
// Created by Just on 21.09.2023.
//

#ifndef INC_22202_ROZHKOV_OOP_CPP_STATCOLLECTOR_H
#define INC_22202_ROZHKOV_OOP_CPP_STATCOLLECTOR_H

#include "utility"
#include "string"
#include "map"
#include "list"
#include "algorithm"

using std::string;
class StatCollector {
private:
    std::map<string, size_t> dictionary;
public:

    void add(const string& word);

    std::list<string> getAll(bool sortDirector);

    size_t getWordStat(const string& word);

    size_t getFullAmountOfWords();

    void clear() {
        dictionary.clear();
    }
};
#endif //INC_22202_ROZHKOV_OOP_CPP_STATCOLLECTOR_H
