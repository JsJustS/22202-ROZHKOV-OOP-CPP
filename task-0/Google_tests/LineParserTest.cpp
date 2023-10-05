//
// Created by Just on 05.10.2023.
//

#include "gtest/gtest.h"
#include "../LineParser.h"

TEST(LineParserTests, SimpleBehavior) {
    LineParser parser;
    std::list<string> myStrings;

    string firstString = "string number 1";
    string secondString = "string number two";
    string thirdString = "StriNg %% NmbEEr/Th3EE";
    size_t amountOfSubstrings;

    parser.load(firstString);
    amountOfSubstrings = parser.split(myStrings);
    parser.clear();

    std::list<string>::iterator it = myStrings.begin();
    ASSERT_EQ(amountOfSubstrings, 3);
    ASSERT_EQ(*it, "string");
    std::advance(it, 1);
    ASSERT_EQ(*it, "number");
    std::advance(it, 1);
    ASSERT_EQ(*it, "1");

    parser.load(secondString);
    amountOfSubstrings = parser.split(myStrings);
    parser.clear();

    it = myStrings.begin();
    ASSERT_EQ(amountOfSubstrings, 3);
    ASSERT_EQ(*it, "string");
    std::advance(it, 1);
    ASSERT_EQ(*it, "number");
    std::advance(it, 1);
    ASSERT_EQ(*it, "two");

    parser.load(thirdString);
    amountOfSubstrings = parser.split(myStrings);
    parser.clear();

    it = myStrings.begin();
    ASSERT_EQ(amountOfSubstrings, 3);
    ASSERT_EQ(*it, "StriNg");
    std::advance(it, 1);
    ASSERT_EQ(*it, "NmbEEr");
    std::advance(it, 1);
    ASSERT_EQ(*it, "Th3EE");
}

TEST(LineParserTests, EmptyString) {
    LineParser parser;
    std::list<string> myStrings;

    string emptyString = "";

    parser.load(emptyString);
    size_t amountOfSubstrings = parser.split(myStrings);
    parser.clear();

    ASSERT_EQ(amountOfSubstrings, 0);
}

TEST(LineParserTests, DelimeterString) {
    LineParser parser;
    std::list<string> myStrings;

    string delimiterString = "% @#";

    parser.load(delimiterString);
    size_t amountOfSubstrings = parser.split(myStrings);
    parser.clear();

    ASSERT_EQ(amountOfSubstrings, 0);
}

TEST(LineParserTests, DelimeterEndString) {
    LineParser parser;
    std::list<string> myStrings;

    string delimiterEndString = "Hello there! My name is Sam% @#";

    parser.load(delimiterEndString);
    size_t amountOfSubstrings = parser.split(myStrings);
    parser.clear();

    std::list<string>::iterator it = myStrings.begin();
    ASSERT_EQ(amountOfSubstrings, 6);
    ASSERT_EQ(*it, "Hello");
    std::advance(it, 1);
    ASSERT_EQ(*it, "there");
    std::advance(it, 1);
    ASSERT_EQ(*it, "My");
    std::advance(it, 1);
    ASSERT_EQ(*it, "name");
    std::advance(it, 1);
    ASSERT_EQ(*it, "is");
    std::advance(it, 1);
    ASSERT_EQ(*it, "Sam");
}
