//
// Created by Just on 05.10.2023.
//
#include "gtest/gtest.h"
#include "../FileReader.h"

using std::ofstream;

TEST(FileReaderTests, SimpleBehavior) {
    // Create txt file
    ofstream myfile;
    myfile.open ("SimpleBehavior.txt");
    myfile << "string 1\n";
    myfile << "string 2\n";
    myfile << "string 3";
    myfile.close();

    FileReader fileReader("SimpleBehavior.txt");
    ASSERT_EQ(fileReader.isOpen(), false);

    fileReader.open();
    ASSERT_EQ(fileReader.isOpen(), true);

    ASSERT_EQ(fileReader.hasNext(), true);
    ASSERT_EQ(fileReader.next(), "string 1");
    ASSERT_EQ(fileReader.hasNext(), true);
    ASSERT_EQ(fileReader.next(), "string 2");
    ASSERT_EQ(fileReader.hasNext(), true);
    ASSERT_EQ(fileReader.next(), "string 3");
    ASSERT_EQ(fileReader.hasNext(), false);

    fileReader.close();
    ASSERT_EQ(fileReader.isOpen(), false);
}

TEST(FileReaderTests, EmptyFile) {
    // Create txt file
    ofstream myfile;
    myfile.open ("EmptyFile.txt");
    myfile.close();

    FileReader fileReader("EmptyFile.txt");
    ASSERT_EQ(fileReader.isOpen(), false);

    fileReader.open();
    ASSERT_EQ(fileReader.isOpen(), true);

    ASSERT_EQ(fileReader.hasNext(), false);

    fileReader.close();
    ASSERT_EQ(fileReader.isOpen(), false);
}

TEST(FileReaderTests, SeveralEmptyLines) {
    // Create txt file
    ofstream myfile;
    myfile.open ("SeveralEmptyLines.txt");
    myfile << "\n\ntest\n\n";
    myfile.close();

    FileReader fileReader("SeveralEmptyLines.txt");
    ASSERT_EQ(fileReader.isOpen(), false);

    fileReader.open();
    ASSERT_EQ(fileReader.isOpen(), true);

    ASSERT_EQ(fileReader.hasNext(), true);
    ASSERT_EQ(fileReader.next(), "");
    ASSERT_EQ(fileReader.hasNext(), true);
    ASSERT_EQ(fileReader.next(), "");
    ASSERT_EQ(fileReader.hasNext(), true);
    ASSERT_EQ(fileReader.next(), "test");
    ASSERT_EQ(fileReader.hasNext(), true);
    ASSERT_EQ(fileReader.next(), "");
    ASSERT_EQ(fileReader.hasNext(), false);

    fileReader.close();
    ASSERT_EQ(fileReader.isOpen(), false);
}

TEST(FileReaderTests, OneLine) {
    // Create txt file
    ofstream myfile;
    myfile.open ("OneLine.txt");
    myfile << "one line";
    myfile.close();

    FileReader fileReader("OneLine.txt");
    ASSERT_EQ(fileReader.isOpen(), false);

    fileReader.open();
    ASSERT_EQ(fileReader.isOpen(), true);

    ASSERT_EQ(fileReader.hasNext(), true);
    ASSERT_EQ(fileReader.next(), "one line");
    ASSERT_EQ(fileReader.hasNext(), false);

    fileReader.close();
    ASSERT_EQ(fileReader.isOpen(), false);
}