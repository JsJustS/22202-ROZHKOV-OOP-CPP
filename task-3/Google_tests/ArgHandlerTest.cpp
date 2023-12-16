//
// Created by Just on 16.12.2023.
//
#include "gtest/gtest.h"
#include "../header/ArgHandler.h"
#include <cstring>

TEST(ArgHandlerTests, simpleTest) {
    ASSERT_ANY_THROW(ArgHandler(0, nullptr));
    ASSERT_ANY_THROW(ArgHandler(1, nullptr));
    ASSERT_ANY_THROW(ArgHandler(3, nullptr));

    char name[5] = "test";
    char flag[3] = "-h";
    char** data = new char*[2];
    data[0] = name;
    data[1] = flag;
    ArgHandler argHandler1(2, data);

    ASSERT_EQ(argHandler1.hasOutputFilename(), false);
    ASSERT_EQ(argHandler1.hasInputFilenames(), false);
    ASSERT_EQ(argHandler1.hasConfigFilename(), false);
    ASSERT_EQ(argHandler1.isHelpRequested(), true);

    delete [] data;

    data = new char*[5];
    data[0] = name;
    flag[1] = 'c';
    data[1] = flag;

    char config[4] = "con";
    char outputName[4] = "out";
    char inputName[3] = "in";
    data[2] = config;
    data[3] = outputName;
    data[4] = inputName;

    ArgHandler argHandler2(5, data);

    ASSERT_EQ(argHandler2.hasOutputFilename(), true);
    ASSERT_EQ(argHandler2.hasInputFilenames(), true);
    ASSERT_EQ(argHandler2.hasConfigFilename(), true);
    ASSERT_EQ(argHandler2.isHelpRequested(), false);

    ASSERT_EQ(argHandler2.getInputFilenames()[0], "in");
    ASSERT_EQ(argHandler2.getOutputFilename(), "out");
    ASSERT_EQ(argHandler2.getConfigFilename(), "con");

    delete [] data;
}