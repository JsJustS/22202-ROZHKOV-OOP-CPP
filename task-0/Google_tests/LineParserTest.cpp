//
// Created by Just on 05.10.2023.
//

#include "gtest/gtest.h"
#include "../LineParser.h"

TEST(LineParserTests, SimpleBehavior) {

    string firstString = "string number 1";
    string secondString = "string number two";
    string thirdString = "StriNg %% NmbEEr/Th3EE";

    LineParser parser(firstString);
    std::list<string> myStrings = parser.split();

    std::list<string>::iterator it = myStrings.begin();
    ASSERT_EQ(myStrings.size(), 3);
    ASSERT_EQ(*it, "string");
    std::advance(it, 1);
    ASSERT_EQ(*it, "number");
    std::advance(it, 1);
    ASSERT_EQ(*it, "1");

    parser.load(secondString);
    myStrings = parser.split();

    it = myStrings.begin();
    ASSERT_EQ(myStrings.size(), 3);
    ASSERT_EQ(*it, "string");
    std::advance(it, 1);
    ASSERT_EQ(*it, "number");
    std::advance(it, 1);
    ASSERT_EQ(*it, "two");

    parser.load(thirdString);
    myStrings = parser.split();

    it = myStrings.begin();
    ASSERT_EQ(myStrings.size(), 3);
    ASSERT_EQ(*it, "StriNg");
    std::advance(it, 1);
    ASSERT_EQ(*it, "NmbEEr");
    std::advance(it, 1);
    ASSERT_EQ(*it, "Th3EE");
}

TEST(LineParserTests, EmptyString) {

    string emptyString = "";

    LineParser parser(emptyString);
    std::list<string> myStrings = parser.split();

    ASSERT_EQ(myStrings.size(), 0);
}

TEST(LineParserTests, DelimeterString) {

    string delimiterString = "% @#";

    LineParser parser(delimiterString);
    std::list<string> myStrings = parser.split();

    ASSERT_EQ(myStrings.size(), 0);
}

TEST(LineParserTests, DelimeterEndString) {
    string delimiterEndString = "Hello there! My name is Sam% @#";

    LineParser parser(delimiterEndString);
    std::list<string> myStrings = parser.split();

    std::list<string>::iterator it = myStrings.begin();
    ASSERT_EQ(myStrings.size(), 6);
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
