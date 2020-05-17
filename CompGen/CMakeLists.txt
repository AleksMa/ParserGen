cmake_minimum_required(VERSION 3.15)
project(LEXERLAB4)

set(CMAKE_CXX_STANDARD 20)

file(GLOB SRC
        "*.h"
        "*.cpp"
        "Compiler/*"
        "Token/*"
        "../Utils/*"
        "../Utils/Message/*"
        "../Utils/Token/*"
        "../Utils/Node/*"
        "../Utils/Position/*"
        )

add_executable(LEXERLAB4 ${SRC})