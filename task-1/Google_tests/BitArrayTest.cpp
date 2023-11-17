//
// Created by Just on 05.10.2023.
//
#include "gtest/gtest.h"
#include "../BitArray.h"

#define BitContainerType unsigned char

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
    BitArray array(5, 19);
    array.set();
    ASSERT_EQ(array.to_string(), "11111");
    array.set(1, false);
    ASSERT_EQ(array.to_string(), "10111");
    array.set(1);
    ASSERT_EQ(array.to_string(), "11111");

    array.reset(1);
    ASSERT_EQ(array.to_string(), "10111");
    array.reset();
    ASSERT_EQ(array.to_string(), "00000");

    array.push_back(true);
    ASSERT_EQ(array.to_string(), "000001");
    array.push_back(false);
    ASSERT_EQ(array.to_string(), "0000010");

    array.resize(5);
    ASSERT_EQ(array.to_string(), "00000");
    array.resize(10, true);
    ASSERT_EQ(array.to_string(), "0000011111");

    BitArray anotherArray(5, 19); //10011
    anotherArray.swap(array);

    ASSERT_EQ(array.to_string(), "10011");
    ASSERT_EQ(array.size(), 5);
    ASSERT_EQ(anotherArray.to_string(), "0000011111");
    ASSERT_EQ(anotherArray.size(), 10);

    array.clear();
    ASSERT_EQ(array.to_string(), "");
    ASSERT_EQ(array.size(), 0);
}

TEST(BitArrayTestSuite, ExtractingTest) {
    BitArray array(5, 19);
    std::vector<BitContainerType> arrVector{152};
    ASSERT_EQ(array.to_vector(), arrVector);
    ASSERT_EQ(array.to_string(), "10011");
    ASSERT_EQ(array.empty(), false);
    ASSERT_EQ(array.any(), true);
    ASSERT_EQ(array.none(), false);
    ASSERT_EQ(array.count(), 3);
    ASSERT_EQ(array.size(), 5);

    BitArray emptyArray = BitArray();
    std::vector<BitContainerType> emptyVector;
    ASSERT_EQ(emptyArray.to_vector(), emptyVector);
    ASSERT_EQ(emptyArray.to_string(), "");
    ASSERT_EQ(emptyArray.empty(), true);
    ASSERT_EQ(emptyArray.any(), false);
    ASSERT_EQ(emptyArray.none(), true);
    ASSERT_EQ(emptyArray.count(), 0);
    ASSERT_EQ(emptyArray.size(), 0);

    BitArray fullArray = BitArray(5, 31);
    std::vector<BitContainerType> fullVector{248};
    ASSERT_EQ(fullArray.to_vector(), fullVector);
    ASSERT_EQ(fullArray.to_string(), "11111");
    ASSERT_EQ(fullArray.empty(), false);
    ASSERT_EQ(fullArray.any(), true);
    ASSERT_EQ(fullArray.none(), false);
    ASSERT_EQ(fullArray.count(), 5);
    ASSERT_EQ(fullArray.size(), 5);
}

TEST(BitArrayTestSuite, OperatorTest) {
    BitArray a(5, 19); // 10011
    BitArray b(5, 12); // 01100
    ASSERT_EQ(a == b, false);
    ASSERT_EQ(a != b, true);

    a = b;
    ASSERT_EQ(a.to_string(), b.to_string());
    ASSERT_EQ(a == b, true);
    ASSERT_EQ(a != b, false);

    // a = 01100
    ASSERT_EQ("00011", (a >> 2).to_string());
    ASSERT_EQ("10000", (a << 2).to_string());
    ASSERT_EQ("10011", (a ^ BitArray(5, 31)).to_string());
    ASSERT_EQ("01100", (a & BitArray(5, 31)).to_string());
    ASSERT_EQ("01111", (a | BitArray(5, 3)).to_string());

    b >>= 2;
    ASSERT_EQ("00011", b.to_string());
    b <<= 4;
    ASSERT_EQ("10000", b.to_string());
    b ^= BitArray(5, 31);
    ASSERT_EQ("01111", b.to_string());
    b &= BitArray(5, 30);
    ASSERT_EQ("01110", b.to_string());
    b |= BitArray(5, 1);
    ASSERT_EQ("01111", b.to_string());

    ASSERT_EQ(a[1], b[4]);
    ASSERT_EQ(a[0], b[0]);
    ASSERT_ANY_THROW(a[42]);

    a.clear();
    a[0] = true;
    a[9] = true;

    ASSERT_EQ("10011", (~a).to_string());
}