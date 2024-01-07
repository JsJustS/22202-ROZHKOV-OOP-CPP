//
// Created by Just on 16.12.2023.
//

#ifndef TASK_4_CSVPARSER_H
#define TASK_4_CSVPARSER_H

#include <fstream>
#include <functional>
#include <vector>
#include <sstream>

#include "errors/CSVError.h"

namespace csv {
    template <typename T> inline bool isType(const std::string& s) {
        std::istringstream iss(s);
        T dummy;
        iss >> std::noskipws >> dummy;
        return iss.eof() && !iss.fail();
    }

    template <typename T> inline T convert(const std::string&, unsigned int row, unsigned int col) {
        throw CSVError(row, col, "Unsupported Type.");
    }
    template <> inline int convert<int>(const std::string& value, unsigned int row, unsigned int col) {
        if (!isType<int>(value)) throw CSVError(row, col, "Unsupported Type.");
        return std::stoi(value);
    }
    template <> inline std::string convert<std::string>(const std::string& value, unsigned int, unsigned int) {
        return value;
    }
}

template<typename... Args>
class CSVParser {
private:
    std::ifstream& file;
    char del;
    std::string scr;

    std::tuple<Args...>* data;
    unsigned int linesRead;

    class Iterator {
    private:
        CSVParser* parent;
        std::tuple<Args...>* data;
    public:
        explicit Iterator(CSVParser<Args...>* parent, std::tuple<Args...>* data) {
            this->parent = parent;
            this->data = data;
        }

        const std::tuple<Args...>& operator*() {return *data;}
        const std::tuple<Args...>* operator->() {return data;}

        Iterator& operator++() {
            this->data = this->parent->readLine();
            return *this;
        }

        friend bool operator== (const Iterator& a, const Iterator& b) {
            return a.data == b.data;
        }

        friend bool operator!= (const Iterator& a, const Iterator& b) {
            return a.data != b.data;
        }
    };

    // Функция-помощник для преобразования строки в нужный тип
    template<typename T>
    T convert(const std::string& value, unsigned int column) {
        return csv::convert<T>(value, this->linesRead, column + 1);
    }

    // Вспомогательная функция для создания кортежа из вектора строк
    template<size_t... Indices>
    std::tuple<Args...> vectorToTupleHelper(const std::vector<std::string>& input, std::index_sequence<Indices...>) {
        return std::make_tuple(convert<Args>(input[Indices], Indices)...);
    }

    // Функция, которая преобразует вектор строк в кортеж разных типов
    std::tuple<Args...> vectorToTuple(const std::vector<std::string>& input) {
        if (input.size() != sizeof...(Args)) {
            throw CSVError(this->linesRead, "Number of rows does not match the number of provided types.");
        }
        return vectorToTupleHelper(input, std::make_index_sequence<sizeof...(Args)>());
    }

    std::vector<std::string> splitString(const std::string& str) {
        std::vector<std::string> result;
        std::stringstream ss(str);
        std::string token;
        while (std::getline(ss, token, this->del)) {
            result.push_back(token);
        }
        return result;
    }

    std::tuple<Args...> parseLine(const std::string& line) {

        std::vector<std::string> values = splitString(line);

        // Проверяем, что количество значений соответствует количеству типов в std::tuple
        if (values.size() != sizeof...(Args)) {
            throw CSVError(this->linesRead, "Number of rows does not match the number of provided types.");
        }

        return vectorToTuple(values);
    }

public:
    explicit CSVParser(std::ifstream& file, unsigned int lineToSkip = 0,
                       char del = ',', const std::string& scr = "\"\"");

    ~CSVParser() {
        delete this->data;
    }

    Iterator begin() {
        readLine();
        return Iterator(this, this->data);
    }
    Iterator end() {
        return Iterator(this, nullptr);
    }

    std::tuple<Args...>* readLine() {
        if (this->isEOF()) {
            delete this->data;
            this->data = nullptr;
        } else {
            this->linesRead++;

            std::string line;
            if (!std::getline(this->file, line) || line.empty()) {
                delete this->data;
                this->data = nullptr;
                return this->data;
            }
            *this->data = this->parseLine(line);
        }
        return this->data;
    }

    bool isEOF() {
        return this->file.eof() || !this->file.is_open();
    }
};

template<typename... Args>
CSVParser<Args...>::CSVParser(std::ifstream &file, unsigned int lineToSkip,
                              char del, const std::string& scr) : file(file), del(del), linesRead(0) {
    this->scr = scr;
    this->data = new std::tuple<Args...>;

    for (int i = 0; i < lineToSkip; ++i) {this->readLine();}
}

#endif //TASK_4_CSVPARSER_H
