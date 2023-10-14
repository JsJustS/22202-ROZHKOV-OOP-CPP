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

    do {
        LineParser parser(fileReader.next());
        std::list<string> myStrings = parser.split();

        for (auto const& it: myStrings) {
            stat->add(it);
        }
    } while(fileReader.hasNext());
    fileReader.close();
}

void createCSVFromStatistic(StatCollector* stat, const string& outputFilename, bool reverse) {
    std::list<string> words = stat->getAll(reverse);
    size_t amountOfWords = stat->getFullAmountOfWords();

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
    string inputFilename;
    string outputFilename;
    bool reversedSorting = false;

    try {
        if (argc < 2 || 4 < argc) throw std::out_of_range("Wrong amount of arguments.");
        inputFilename = (string)argv[1];
        if (inputFilename.substr(inputFilename.length()-4) != ".txt") throw std::invalid_argument(
                "Input file is not in a .TXT format.");
        switch (argc) {
            case 4:
                reversedSorting = (string)argv[3] == "-r";
            case 3:
                outputFilename = (string)argv[2];
                if (outputFilename.substr(outputFilename.length()-4) != ".csv") throw std::invalid_argument(
                        "Output file is not in a .CSV format.");
                break;
            case 2:
                outputFilename = inputFilename.substr(0, inputFilename.length()-4) + ".csv";
                break;
            default: return 1;
        }
    } catch (const std::logic_error& err) {
        std::cout << err.what();
        return 1;
    }

    // Начинаем работу с файлами
    StatCollector stat;
    collectStatistics(&stat, inputFilename);
    createCSVFromStatistic(&stat, outputFilename, reversedSorting);
    return 0;
}