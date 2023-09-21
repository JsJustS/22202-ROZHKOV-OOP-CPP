
#include "FileReader.h"

bool FileReader::hasNext() {
    return f.peek() != EOF;
}

string FileReader::next() {
    string line;
    std::getline(f, line);
    return line;
}
