//
// Created by Just on 19.09.2023.
//

#include "FileReader.h"
#include "LineParser.h"

int main() {
    FileReader fileReader("test.txt");
    fileReader.open();

    LineParser parser(" ");
    std::vector<string> myStrings;
    while (fileReader.hasNext()) {
        parser.load(fileReader.next());
        size_t x = parser.split(myStrings);
        parser.clear();
        for (int i = 0; i < x; i++) {
            std::cout << myStrings[i] << ";";
        }
        std::cout << std::endl;
    }
    fileReader.close();
    return 0;
}