cmake_minimum_required(VERSION 3.26)
project(22202_rozhkov_oop_cpp_task_2)

set(CMAKE_CXX_STANDARD 14)

add_executable(22202_rozhkov_oop_cpp_task_2
        header/ConfigManager.h  source/ConfigManager.cpp
        header/LineParser.h     source/LineParser.cpp
        header/Rule.h           source/Rule.cpp
        header/FileReader.h     source/FileReader.cpp
        header/FileWriter.h     source/FileWriter.cpp
        header/InputManager.h   source/InputManager.cpp
        header/Input.h
        header/Screen.h
        header/Engine.h         source/Engine.cpp
        header/Field.h          source/Field.cpp
        header/ConsoleInput.h   source/ConsoleInput.cpp
        header/ConsoleScreen.h  source/ConsoleScreen.cpp
        main.cpp
)

add_subdirectory(Google_tests)