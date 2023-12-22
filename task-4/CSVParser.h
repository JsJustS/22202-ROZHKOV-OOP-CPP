//
// Created by Just on 16.12.2023.
//

#ifndef TASK_4_CSVPARSER_H
#define TASK_4_CSVPARSER_H

template<typename... Args>
class CSVParser {
private:

    class Iterator {
    private:
        CSVParser& parent;
        bool isEOF;
        std::tuple<Args...> lastTuple;
    public:
        explicit Iterator(CSVParser& parent) : parent(parent), isEOF(false) {}

        std::tuple<Args...>& operator*();
        std::tuple<Args...>* operator->();

        Iterator& operator++();
        Iterator operator++(int);
        friend bool operator== (const Iterator& a, const Iterator& b);
        friend bool operator!= (const Iterator& a, const Iterator& b);
    };
public:
    CSVParser(std::ifstream& file, unsigned int lineToSkip = 0,
              std::string del = ",", std::string scr = "\"\"");

    Iterator begin();
    Iterator end();
};

#endif //TASK_4_CSVPARSER_H
