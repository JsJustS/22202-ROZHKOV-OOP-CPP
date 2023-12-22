//
// Created by Just on 16.12.2023.
//

#include <fstream>
#include <iostream>
#include "CSVParser.h"

#include <tuple>

template<int I=0, typename C, typename T, typename... Args>
void printTupleByRecursion(std::basic_ostream<C, T>& ostream, std::tuple<Args...> const &t,
                           std::enable_if_t<I >= sizeof...(Args)>* = nullptr) {
    // do nothing!!
}

template<int I=0, typename C, typename T, typename... Args>
void printTupleByRecursion(std::basic_ostream<C, T>& ostream, std::tuple<Args...> const &t,
                           std::enable_if_t<I < sizeof...(Args)>* = nullptr) {
    ostream << std::get<I>(t) << "; ";
    printTupleByRecursion<I+1, C, T, Args...>(ostream, t);
}

//operator
template<typename C, typename T, typename... Args>
auto& operator<<(std::basic_ostream<C, T>& ostream, std::tuple<Args...> const &t) {
    printTupleByRecursion(ostream, t);
    return ostream;
}

void testTuplePrinting() {
    std::cout << std::tuple<int, int, double, int, int>(5, 6, 50.3, 3, 7) << std::endl;
    std::cout << std::tuple<int, float, double, int, std::string>(1, 2.3f, 4.5, 6, "seven") << std::endl;
}

void testCSVParser() {
    std::ifstream file("test.csv");
    CSVParser<int, std::string> parser(file, 0);
    for (const std::tuple<int, std::string>& rs : parser) {
        std::cout << rs << std::endl;
    }
}

int main(int argc, char** argv) {
    testTuplePrinting();
    testCSVParser();
    return 0;
}