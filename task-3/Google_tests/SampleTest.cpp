//
// Created by Just on 02.12.2023.
//
#include "gtest/gtest.h"
#include "../header/Sample.h"

TEST(SampleTest, simpleTest) {
    Sample sample{};

    sample[0] = 0;
    sample[1] = 1;
    sample.markLoad(true);
    ASSERT_EQ(sample.getAsInt(), 256);

    Sample sample1(sample);
    ASSERT_EQ(sample1.getAsInt(), 256);

    Sample sample2{};
    ASSERT_EQ(sample.isLoaded(), true);
    ASSERT_EQ(sample1.isLoaded(), true);
    ASSERT_EQ(sample2.isLoaded(), false);
}