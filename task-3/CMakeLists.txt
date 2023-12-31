cmake_minimum_required(VERSION 3.26)
project(22202_rozhkov_oop_cpp_task_3)

set(CMAKE_CXX_STANDARD 14)

add_executable(22202_rozhkov_oop_cpp_task_3
        header/errors/SoundProcessingError.h
        header/errors/WrongArgumentsError.h
        header/errors/OutOfRangeStreamIdError.h
        header/errors/FileError.h
        header/ArgHandler.h                         source/ArgHandler.cpp
        header/ConfigManager.h                      source/ConfigManager.cpp
        header/SoundProcessor.h                     source/SoundProcessor.cpp
        header/Converters/ConverterFabric.h
        header/Converters/ConverterMixFabric.h      source/Converters/ConverterMixFabric.cpp
        header/Converters/ConverterMuteFabric.h     source/Converters/ConverterMuteFabric.cpp
        header/Converters/ConverterFadeFabric.h     source/Converters/ConverterFadeFabric.cpp
        header/Converters/Converter.h
        header/Converters/ConverterMix.h            source/Converters/ConverterMix.cpp
        header/Converters/ConverterMute.h           source/Converters/ConverterMute.cpp
        header/Converters/ConverterFade.h           source/Converters/ConverterFade.cpp
        header/Sample.h                             source/Sample.cpp
        header/WAVWrapper.h                         source/WAVWrapper.cpp
        header/LineParser.h                         source/LineParser.cpp
        header/FileReader.h                         source/FileReader.cpp
        main.cpp
)

add_subdirectory(Google_tests)