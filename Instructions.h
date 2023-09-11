#ifndef CPU_SIMULATOR_INSTRUCTIONS_H
#define CPU_SIMULATOR_INSTRUCTIONS_H
#include <iostream>
#include <map>

struct Instructions {
    static std::map<int, std::string> label;
    std::string opcode;//(e.g., "mov", "add")
    std::vector<std::string> operands;
};

std::map<int, std::string> Instructions::label;


#endif //CPU_SIMULATOR_INSTRUCTIONS_H
