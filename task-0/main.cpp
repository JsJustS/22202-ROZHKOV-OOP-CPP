//
// Created by Just on 19.09.2023.
//

#include "FileReader.h"
#include "LineParser.h"
#include "StatCollector.h"
#include "CSVWriter.h"

void collectStatistics(StatCollector* stat, const string& filename) {
    FileReader fileReader(filename);
    fileReader.open();

    LineParser parser(" ");
    std::vector<string> myStrings;

    while (fileReader.hasNext()) {
        parser.load(fileReader.next());
        size_t x = parser.split(myStrings);
        parser.clear();

        for (int i = 0; i < x; i++) {
            stat->add(myStrings[i]);
        }
    }
    fileReader.close();
}

void createCSVFromStatistic(StatCollector* stat, const string& outputFilename, bool reverse) {
    std::vector<string> words;
    size_t amountOfWords = stat->loadAllWords(words, reverse);

    CSVWriter csv(outputFilename, ",");
    csv.open();
    csv.addWord("Word").addWord("Frequency").addWord("Percentage").nextLine();
    for (const string& word : words) {
        size_t freq = stat->getWordStat(word);
        csv.addWord(word).addElement(freq).addWord(((double)freq / amountOfWords) * 100).nextLine();
    }
    csv.save();
}

int main(int argc, char* argv[]) {
    // Проверяем инпут данные
    if (argc < 2 || 4 < argc) return 1;
    string inputFilename = (string)argv[1];
    assert(inputFilename.substr(inputFilename.length()-4) == ".txt");
    string outputFilename;
    bool reversedSorting;
    switch (argc) {
        case 4:
            reversedSorting = (string)argv[3] == "-r";
        case 3:
            outputFilename = (string)argv[2];
            assert(outputFilename.substr(outputFilename.length()-4) == ".csv");
            break;
        case 2:
            outputFilename = inputFilename.substr(0, inputFilename.length()-4) + ".csv";
            break;
        default: return 1;
    }
    // Начинаем работу с файлами
    StatCollector stat{};
    collectStatistics(&stat, inputFilename);
    createCSVFromStatistic(&stat, outputFilename, reversedSorting);
    return 0;
}