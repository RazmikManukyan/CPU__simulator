#ifndef CPU_SIMULATOR_INSTRUCTIONS_H
#define CPU_SIMULATOR_INSTRUCTIONS_H

#include <iostream>
#include <map>

struct Instructions {
    // Static member to store labels and their associated line numbers.
    static std::map<int, std::string> label;

    // Opcode for the instruction (e.g., "mov", "add").
    std::string opcode;

    // Vector to store operands of the instruction.
    std::vector<std::string> operands;
};

// Initialize the static member 'label' to store labels and line numbers.
std::map<int, std::string> Instructions::label;

#endif //CPU_SIMULATOR_INSTRUCTIONS_H
