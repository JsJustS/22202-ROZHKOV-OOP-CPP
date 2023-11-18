cmake_minimum_required(VERSION 3.26)
project(22202_rozhkov_oop_cpp_task_2)

set(CMAKE_CXX_STANDARD 14)

add_executable(22202_rozhkov_oop_cpp_task_2
        header/ConfigManager.h  source/
        header/FileReader.h
        header/InputManager.h
        header/Input.h
        header/Screen.h
        header/Engine.h
        header/Field.h
        header/ConsoleInput.h
        header/ConsoleScreen.h
)

add_subdirectory(Google_tests)