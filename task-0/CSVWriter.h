//
// Created by Just on 21.09.2023.
//

#ifndef INC_22202_ROZHKOV_OOP_CPP_CSVWRITER_H
#define INC_22202_ROZHKOV_OOP_CPP_CSVWRITER_H

#include <utility>

#include "string"
#include "iostream"
#include "fstream"
#include "cassert"

using std::string;
using std::ofstream;

class CSVWriter {
private:
    string filename;
    ofstream f;
    string del;

    bool startOfLine;

    void ensureSplit();
public:
    explicit CSVWriter(string fname, string delimiter) {
        assert(fname.substr(fname.length() - 4) == ".csv");
        filename = std::move(fname);
        del = std::move(delimiter);

        startOfLine = true;
    }

    // охранить данные в формате csv
    void open() {
        f.open(filename);
    }

    // Добавить элемент в csv формате
    template <typename T>
    CSVWriter& addElement(T el) {
        ensureSplit();
        f << el;
        return *this;
    }

    template <typename T>
    CSVWriter& addWord(T el) {
        ensureSplit();
        f << R"("="")" << el << R"(""")";
        return *this;
    }

    // Перевод на следующую строку файла
    CSVWriter& nextLine();

    // закрыть и сохранить файл
    void save() {
        f.close();
    }
};
#endif //INC_22202_ROZHKOV_OOP_CPP_CSVWRITER_H
