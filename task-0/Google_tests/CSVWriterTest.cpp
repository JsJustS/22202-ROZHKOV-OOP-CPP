//
// Created by Just on 05.10.2023.
//
#include "gtest/gtest.h"
#include "../CSVWriter.h"

using std::ifstream;

TEST(CSVWriterTests, SimpleBehavior) {
    CSVWriter csv("SimpleBehavior.csv", ",");
    ASSERT_EQ(csv.isOpen(), false);
    csv.open();
    ASSERT_EQ(csv.isOpen(), true);

    csv.addWord("Test Word 1").addWord("Test Word 2").nextLine();
    csv.addElement(5).addWord(10);

    csv.save();
    ASSERT_EQ(csv.isOpen(), false);

    // check file

    ifstream fileReader("SimpleBehavior.csv");
    std::string line;

    std::getline(fileReader, line);
    ASSERT_EQ(line, "\"=\"\"Test Word 1\"\"\",\"=\"\"Test Word 2\"\"\"");
    std::getline(fileReader, line);
    ASSERT_EQ(line, "5,\"=\"\"10\"\"\"");
    ASSERT_EQ(fileReader.eof(), true);
}

TEST(CSVWriterTests, EmptyTest) {
    CSVWriter csv("EmptyTest.csv", ",");
    ASSERT_EQ(csv.isOpen(), false);
    csv.open();
    ASSERT_EQ(csv.isOpen(), true);
    csv.save();
    ASSERT_EQ(csv.isOpen(), false);

    // check file

    ifstream fileReader("EmptyTest.csv");
    std::string line;

    std::getline(fileReader, line);
    ASSERT_EQ(line, "");
    ASSERT_EQ(fileReader.eof(), true);
}

TEST(CSVWriterTests, EmptyInputTest) {
    CSVWriter csv("EmptyInputTest.csv", ",");
    ASSERT_EQ(csv.isOpen(), false);
    csv.open();
    ASSERT_EQ(csv.isOpen(), true);
    csv.addWord("").nextLine();
    csv.addElement("");
    csv.save();
    ASSERT_EQ(csv.isOpen(), false);

    // check file

    ifstream fileReader("EmptyInputTest.csv");
    std::string line;

    std::getline(fileReader, line);
    ASSERT_EQ(line, "\"=\"\"\"\"\"");
    std::getline(fileReader, line);
    ASSERT_EQ(line, "");
    ASSERT_EQ(fileReader.eof(), true);
}
