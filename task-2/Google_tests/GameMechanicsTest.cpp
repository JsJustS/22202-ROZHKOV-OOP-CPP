//
// Created by Just on 24.11.2023.
#include "gtest/gtest.h"
#include "../header/Rule.h"
#include "../header/Field.h"

TEST(GameTestSuite, RuleBehavior) {
    Rule rule{};

    rule.add(2);
    rule.add(3);
    rule.add(4);
    rule.add(2);

    ASSERT_EQ(rule.toString(), "Rule{2, 3, 4}");

    rule.remove(2);

    ASSERT_EQ(rule.toString(), "Rule{3, 4}");

    ASSERT_EQ(rule.isApplicable(3), true);
    ASSERT_EQ(rule.isApplicable(2), false);

    rule.clear();

    ASSERT_EQ(rule.toString(), "Rule{}");
}

TEST(GameTestSuite, FieldTest){
    Field field(3, 3);
    field.setCell(0, 0, true);

    ASSERT_EQ(field.getCell(0, 0), true);
    ASSERT_EQ(field.getCell(0, 1), false);
    ASSERT_EQ(field.getCell(2, 2), false);

    ASSERT_EQ(field.countAliveNeighbours(0, 0), 0);
    field.setCell(1, 1, true);
    ASSERT_EQ(field.countAliveNeighbours(0, 0), 1);

    ASSERT_EQ(field.toString(), "Field{width=3, height=3, array={[⬜⬛⬛][⬛⬜⬛][⬛⬛⬛]}}");
}
