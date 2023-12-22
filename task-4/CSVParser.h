//
// Created by Just on 16.12.2023.
//

#ifndef TASK_4_CSVPARSER_H
#define TASK_4_CSVPARSER_H

template<typename... Args>
class CSVParser {
private:
    std::ifstream file;
    unsigned int lineToSkip;
    std::string del;
    std::string scr;

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

    template<typename T>
    T parseString(std::string text) {
        // todo: throw Unsupported Typer error
    }

    template<>
    long long parseString<long long>(std::string text) {
        return 0;
    }

    template<>
    unsigned long long parseString<unsigned long long>(std::string text) {
        return 0;
    }

    template<>
    long parseString<long >(std::string text) {
        return 0;
    }

    template<>
    unsigned long parseString<unsigned long>(std::string text) {
        return 0;
    }

    template<>
    int parseString<int>(std::string text) {
        return 0;
    }

    template<>
    std::string parseString<std::string>(std::string text) {
        return {};
    }

    template<>
    char parseString<char>(std::string text) {
        return 0;
    }

    template<>
    float parseString<float>(std::string text) {
        return .0f;
    }

    template<>
    double parseString<double>(std::string text) {
        return 0;
    }

    template<>
    long double parseString<long double>(std::string text) {
        return 0;
    }
public:
    CSVParser(std::ifstream& file, unsigned int lineToSkip = 0,
              std::string del = ",", std::string scr = "\"\"");

    Iterator begin();
    Iterator end();

    std::tuple<Args...> readLine();

    bool isEOF();
};

#endif //TASK_4_CSVPARSER_H
