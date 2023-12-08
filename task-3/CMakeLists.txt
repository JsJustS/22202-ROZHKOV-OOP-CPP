cmake_minimum_required(VERSION 3.26)
project(22202_rozhkov_oop_cpp_task_3)

set(CMAKE_CXX_STANDARD 14)

add_executable(22202_rozhkov_oop_cpp_task_3
        header/ArgHandler.h         source/ArgHandler.cpp
        header/ConfigManager.h      source/ConfigManager.cpp
        header/SoundProcessor.h     source/SoundProcessor.cpp
        header/ConverterFabric.h
        header/Converter.h
        header/Sample.h             source/Sample.cpp
        header/WAVWrapper.h         source/WAVWrapper.cpp
        header/LineParser.h         source/LineParser.cpp
        header/FileReader.h         source/FileReader.cpp
        main.cpp
)

add_subdirectory(Google_tests)