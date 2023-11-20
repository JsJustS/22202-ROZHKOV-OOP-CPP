//
// Created by Just on 18.11.2023.
//

#include "gtest/gtest.h"
#include "../header/Rule.h"
#include "../header/LineParser.h"
#include "../header/ConfigManager.h"

TEST(FileReaderTests, RuleBehavior) {
    Rule rule{};

    rule.add(2);
    rule.add(3);
    rule.add(4);
    rule.add(2);

    std::cout << rule.toString() << std::endl;

    rule.remove(2);

    std::cout << rule.toString() << std::endl;

    ASSERT_EQ(rule.isApplicable(3), true);
    ASSERT_EQ(rule.isApplicable(2), false);

    rule.clear();

    std::cout << rule.toString() << std::endl;
}

TEST(FileReaderTests, LineParserBehaviour) {
    ASSERT_EQ(LineParser::isNumeric("1234567890"), true);
    ASSERT_EQ(LineParser::isNumeric("-1234567890"), true);
    ASSERT_EQ(LineParser::isNumeric("-1234.567890"), false);
    ASSERT_EQ(LineParser::isNumeric("-1234-567890"), false);
    ASSERT_EQ(LineParser::isNumeric("1234.567890"), false);
    ASSERT_EQ(LineParser::isNumeric("-"), false);
    ASSERT_EQ(LineParser::isNumeric(""), false);

    for (std::string piece: LineParser::parse("Hello   There    I   am   SAM!!!!")) {
        std::cout << "|" << piece << "|" << std::endl;
    }
}

TEST(FileReaderTests, ConfigManagerBehaviour) {
    ConfigManager config{std::cout};

    Field field{};

    config.load("C:\\Users\\Just\\CLionProjects\\22202-ROZHKOV-OOP-CPP\\task-2\\games\\test.lif", field);

    std::cout << config.toString() << std::endl;
    std::cout << field.toString() << std::endl;
}