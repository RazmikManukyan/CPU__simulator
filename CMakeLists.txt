cmake_minimum_required(VERSION 3.26)
project(CPU_simulator)

set(CMAKE_CXX_STANDARD 17)

add_executable(CPU_simulator main.cpp
        Register.h
        CPU.h
        CU.h
        Functions.h
        Instructions.h
        InstructionsMap.h
        Memory.h
)