//
// Created by Just on 18.11.2023.
//

#include "gtest/gtest.h"
#include "../header/Rule.h"
#include "../header/LineParser.h"
#include "../header/ConfigManager.h"
#include "../header/Engine.h"
#include "../header/ConsoleScreen.h"

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
    //"C:\\Users\\Just\\CLionProjects\\22202-ROZHKOV-OOP-CPP\\task-2\\games\\test.lif"
    Engine::loadConfig();

    int barrierColor = ConsoleScreen::rgb2Int(13, 77, 0);
    int textColor = ConsoleScreen::rgb2Int(0, 255, 255);
    int aliveCellColor = ConsoleScreen::rgb2Int(255, 255, 255);
    int deadCellColor = ConsoleScreen::rgb2Int(0, 0, 0);

    int generation = 0;
    while (generation++ <= 40) {
        Engine::clearScreen();
        Engine::drawGUI(textColor, barrierColor, generation);
        Engine::drawField(aliveCellColor, deadCellColor, barrierColor);
        Engine::drawScreen();

        Engine::tickField();
    }

    Engine::stop();
}

TEST(FileReaderTests, ScreenTest){
    ConsoleScreen screen{};
    screen.setWidth(23).setHeight(13);
    screen.clear();
    int green = ConsoleScreen::rgb2Int(0, 255, 0);
    screen.addText(1, 1, "i am Sam i am so cool ha ha ha! yaay i am great",
                   ConsoleScreen::rgb2Int(255, 0, 0));
    screen.addPixel(1, 2, ConsoleScreen::rgb2Int(0, 0, 255));
    screen.addLine(0, 0, 22, 0, green)
            .addLine(22, 0, 22, 12, green)
            .addLine(22, 12, 0, 12, green)
            .addLine(0, 12, 0, 0, green);
    screen.render();
}