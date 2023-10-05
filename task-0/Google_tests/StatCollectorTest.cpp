#include "gtest/gtest.h"
#include "../StatCollector.h"

TEST(StatCollectorTests, SimpleStoringBehavior) {
    StatCollector stat;
    string firstString = "string1";
    string secondString = "string2";
    string thirdString = "string3";

    for (short i = 0; i < 3; i++) {stat.add(firstString);}
    for (short i = 0; i < 5; i++) {stat.add(secondString);}
    for (short i = 0; i < 7; i++) {stat.add(thirdString);}

    ASSERT_EQ(stat.getWordStat(firstString), 3);
    ASSERT_EQ(stat.getWordStat(secondString), 5);
    ASSERT_EQ(stat.getWordStat(thirdString), 7);
}

TEST(StatCollectorTests, ClearingBehavior) {
    StatCollector stat;
    string firstString = "string1";
    string secondString = "string2";

    for (short i = 0; i < 3; i++) {stat.add(firstString);}
    for (short i = 0; i < 5; i++) {stat.add(secondString);}

    ASSERT_EQ(stat.getWordStat(firstString), 3);
    ASSERT_EQ(stat.getWordStat(secondString), 5);

    stat.clear();

    ASSERT_EQ(stat.getWordStat(firstString), 0);
    ASSERT_EQ(stat.getWordStat(secondString), 0);

    for (short i = 0; i < 10; i++) {stat.add(firstString);}
    for (short i = 0; i < 2; i++) {stat.add(secondString);}

    ASSERT_EQ(stat.getWordStat(firstString), 10);
    ASSERT_EQ(stat.getWordStat(secondString), 2);
}

TEST(StatCollectorTests, AddBehavior) {
    StatCollector stat;
    string firstString = "string1";
    string secondString = "string2";
    string thirdString = "string3";

    // add words in a random pattern
    for (short i = 0; i < 3; i++) {stat.add(firstString);}
    for (short i = 0; i < 5; i++) {stat.add(secondString);}
    for (short i = 0; i < 7; i++) {stat.add(thirdString);}
    for (short i = 0; i < 5; i++) {stat.add(secondString);}
    for (short i = 0; i < 7; i++) {stat.add(thirdString);}
    for (short i = 0; i < 3; i++) {stat.add(firstString);}

    ASSERT_EQ(stat.getWordStat(firstString), 3*2);
    ASSERT_EQ(stat.getWordStat(secondString), 5*2);
    ASSERT_EQ(stat.getWordStat(thirdString), 7*2);
}

TEST(StatCollectorTests, AllWordsBehavior) {
    StatCollector stat;
    string firstString = "string1";
    string secondString = "string2";
    string thirdString = "string3";

    for (short i = 0; i < 13; i++) {stat.add(firstString);}
    for (short i = 0; i < 15; i++) {stat.add(secondString);}
    for (short i = 0; i < 17; i++) {stat.add(thirdString);}

    std::list<string> words;
    size_t amountOfWords = stat.loadAllWords(words, false);

    std::list<string>::iterator it = words.begin();

    ASSERT_EQ(amountOfWords, 45);
    ASSERT_EQ(*it, thirdString);
    std::advance(it, 1);
    ASSERT_EQ(*it, secondString);
    std::advance(it, 1);
    ASSERT_EQ(*it, firstString);

    size_t newAmountOfWords = stat.loadAllWords(words, true);
    it = words.begin();

    ASSERT_EQ(newAmountOfWords, 45);
    ASSERT_EQ(*it, firstString);
    std::advance(it, 1);
    ASSERT_EQ(*it, secondString);
    std::advance(it, 1);
    ASSERT_EQ(*it, thirdString);
}