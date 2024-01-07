cmake_minimum_required(VERSION 3.26)
project(22202_rozhkov_oop_cpp_task_4)

set(CMAKE_CXX_STANDARD 14)

add_executable(22202_rozhkov_oop_cpp_task_4
        errors/CSVError.h   errors/CSVError.cpp
        CSVParser.h         CSVParser.cpp
        main.cpp
        #        test.cpp
)