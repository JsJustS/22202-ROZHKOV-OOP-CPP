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

void createCSVFromStatistic(StatCollector* stat) {
    std::vector<string> words;
    size_t amountOfWords = stat->loadAllWords(words);

    CSVWriter csv("test.csv", ",");
    csv.open();
    csv.addWord("Word").addWord("Frequency").addWord("Percentage").nextLine();
    for (const string& word : words) {
        size_t freq = stat->getWordStat(word);
        csv.addWord(word).addElement(freq).addWord(((double)freq / amountOfWords) * 100).nextLine();
    }
    csv.save();
}

string parseFilename(const string& filename) {
    assert(filename.substr(filename.length()-4) == ".txt");
    return filename.substr(0, filename.length()-4) + ".csv";
}

int main() {
    string inputFilename = "test.txt";
    string outputFilename = parseFilename(inputFilename);

    StatCollector stat{};
    collectStatistics(&stat, inputFilename);
    createCSVFromStatistic(&stat);
    return 0;
}