//
// Created by Just on 05.10.2023.
//
#include "gtest/gtest.h"
#include "../BitArray.h"

TEST(Alot, initTest) {
    BitArray array(12, 3662);
    std::cout << array.to_string() << std::endl;
    for (int i = 0; i < array.size(); i++) {
        std::cout << "the " << i << " bit is: "<< ((array[i])?"1":"0") << std::endl;
    }
}
/*
  228           224
11100100 | 1110 # 0000 - 3662
11110000 | 0110 # 0110

 11101010
 111010100
*/