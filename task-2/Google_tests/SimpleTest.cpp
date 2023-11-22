//
// Created by Just on 18.11.2023.
//

#include "gtest/gtest.h"
#include "../header/Rule.h"
#include "../header/LineParser.h"
#include "../header/ConfigManager.h"
#include "../header/Engine.h"

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
    ConfigManager config{};
    //config.setLogger(std::cout);

    std::vector<std::pair<int, int>> coords = config.load(
            "C:\\Projects\\NSU\\OOP\\22202-rozhkov-oop-cpp\\task-2\\games\\test.lif"
    );

    Field field(config.getFieldWidth(), config.getFieldHeight());
    Field fieldOld(config.getFieldWidth(), config.getFieldHeight());

    field.load(coords);

    std::cout << config.toString() << std::endl;
    std::cout << field.toString() << std::endl;
    std::cout << fieldOld.toString() << std::endl;

    std::cout << (int)field.countAliveNeighbours(2, 3) << std::endl;
}

TEST(FileReaderTests, EngineTest){
    Engine::init();
    Engine::setLogger(std::cout);
    Engine::loadConfig("C:\\Projects\\NSU\\OOP\\22202-rozhkov-oop-cpp\\task-2\\games\\test.lif");

    Engine::draw(); // ask Screen to draw current Field on itself

    Engine::tick(); // move field to fieldOld, calculate new Field according to rules
    Engine::draw();

    Engine::tick();
    Engine::draw();

    Engine::stop();
}