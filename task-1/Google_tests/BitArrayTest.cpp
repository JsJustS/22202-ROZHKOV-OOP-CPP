//
// Created by Just on 05.10.2023.
//
#include "gtest/gtest.h"
#include "../BitArray.h"

#include <crtdbg.h>

TEST(BitArrayTestSuite, ConstructorTest) {
    BitArray emptyArray = BitArray();
    ASSERT_EQ(emptyArray.size(), 0);

    BitArray array(5, 18);
    ASSERT_EQ(array.size(), 5);
    ASSERT_EQ(array.get(0), 1);
    ASSERT_EQ(array.get(1), 0);
    ASSERT_EQ(array.get(2), 0);
    ASSERT_EQ(array.get(3), 1);
    ASSERT_EQ(array.get(4), 0);

    BitArray copiedArray(array);

    ASSERT_EQ(copiedArray.size(), 5);
    ASSERT_EQ(copiedArray.get(0), 1);
    ASSERT_EQ(copiedArray.get(1), 0);
    ASSERT_EQ(copiedArray.get(2), 0);
    ASSERT_EQ(copiedArray.get(3), 1);
    ASSERT_EQ(copiedArray.get(4), 0);

    //18: 10010
    BitArray newestArray = BitArray(3, 18);
    ASSERT_EQ(newestArray.size(), 3);
    ASSERT_EQ(newestArray.get(0), 1);
    ASSERT_EQ(newestArray.get(1), 0);
    ASSERT_EQ(newestArray.get(2), 0);

    BitArray newestestArray = BitArray(3, 7);
    ASSERT_EQ(newestestArray.size(), 3);
    ASSERT_EQ(newestestArray.get(0), 1);
    ASSERT_EQ(newestestArray.get(1), 1);
    ASSERT_EQ(newestestArray.get(2), 1);
}

TEST(BitArrayTestSuite, ModifyingTest) {
    //
}

TEST(BitArrayTestSuite, ExtractingTest) {
    //get
    //operator[]
}

TEST(BitArrayTestSuite, OperatorTest) {
    //operator==
    //operator!=
    //operator&
    //operator|
    //operator^
}