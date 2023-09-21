//
// Created by Just on 19.09.2023.
//

#include "FileReader.h"
#include "LineParser.h"
#include "StatCollector.h"

int main() {
    FileReader fileReader("test.txt");
    fileReader.open();

    LineParser parser(" ");
    std::vector<string> myStrings;

    StatCollector stat{};

    while (fileReader.hasNext()) {
        parser.load(fileReader.next());
        size_t x = parser.split(myStrings);
        parser.clear();

        for (int i = 0; i < x; i++) {
            std::cout << myStrings[i] << ";";
            stat.add(myStrings[i]);
        }
        std::cout << std::endl;
    }
    fileReader.close();

    myStrings.clear();
    size_t amountOfWords = stat.loadAllWords(myStrings);
    std::cout << "Full amount of collected word: " << amountOfWords << std::endl;
    for (const string& word : myStrings) {
        std::cout << "\"" << word << "\"" << " - " << stat.getWordStat(word) << std::endl;
    }
    return 0;
}