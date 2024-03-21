cmake_minimum_required(VERSION 3.26)
project(Logic_Circuit_Simulator)

set(CMAKE_CXX_STANDARD 17)

add_executable(Logic_Circuit_Simulator main.cpp
        Logic_Gate.h
        Logic_Gate.cpp
        circuit.h
        circuit.cpp
        testOperator.cpp
        testOperator.h
        program.cpp
        testing.cpp)
