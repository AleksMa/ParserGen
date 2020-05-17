cmake_minimum_required(VERSION 3.15)
project(CALCULATOR72)

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

add_executable(CALCULATOR72 ${SRC})