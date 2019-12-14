cmake_minimum_required(VERSION 3.14)
project(SICXE)

set(CMAKE_CXX_STANDARD 17)

add_executable(SICXE main.cpp assembler.cpp assembler.h assembler.h command.h command.cpp)