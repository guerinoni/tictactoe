cmake_minimum_required(VERSION 3.5)

project(tictactoe VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_program(CLANG_TIDY_COMMAND NAMES clang-tidy)
if (CLANG_TIDY_COMMAND)
    set(CMAKE_CXX_CLANG_TIDY "${CLANG_TIDY_COMMAND};--format-style=file")
endif ()

add_subdirectory(src)

enable_testing()

add_subdirectory(tests)
