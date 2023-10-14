//
// Created by Just on 21.09.2023.
//

#include "CSVWriter.h"

CSVWriter& CSVWriter::nextLine() {
    f << std::endl;
    startOfLine = true;
    return *this;
}

void CSVWriter::ensureSplit() {
    if (!startOfLine) f << del;
    startOfLine = false;
}
