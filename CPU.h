#ifndef CPU_SIMULATOR_CPU_H
#define CPU_SIMULATOR_CPU_H
#include "Register.h"
#include "CU.h"
#include "Memory.h"

class CPU {
private:
    Register *registers;
    CU cu;
public:
    explicit CPU(Register *reg) : registers(reg), cu(reg) {}

    void run(const Memory &memory) {
        const std::map<int, std::string> &codeMap = memory.code;
        while (cu.getEip() <= codeMap.size() + 1) {
            Instructions instructions = cu.fetchInstructions(codeMap, cu.getEip());
            cu.executeInstructions(instructions);
        }
    }
};

#endif //CPU_SIMULATOR_CPU_H
