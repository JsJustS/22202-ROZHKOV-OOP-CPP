#ifndef OOP_CPP_FILEREADER_H
#define OOP_CPP_FILEREADER_H

#include "utility"
#include "string"
#include "iostream"
#include "fstream"

using std::string;
using std::ifstream;
// Чтение файла построчно
class FileReader {
private:
    string filename;
    ifstream f;
public:
    explicit FileReader(string fname) {
        filename = std::move(fname);
    }

    // открыть файл
    void open() {
        f.open(filename);
    }

    // дай след. строчку
    string next();

    // есть ли еще данные для считывания
    bool hasNext();

    // закрыть файл
    void close() {
        f.close();
    }

    // вернуть в начало
    void reset() {
        f.clear();
        f.seekg(0);
    }


    bool isOpen() {
        return f.is_open();
    }
};
#endif //OOP_CPP_FILEREADER_H