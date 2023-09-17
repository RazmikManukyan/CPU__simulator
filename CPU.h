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
    // Constructor takes a Register pointer as a parameter.
    explicit CPU(Register *reg) : registers(reg), cu(reg) {}

    // Method to run the CPU with a given memory object.
    void run(const Memory &memory) {
        // Retrieve the code map from the memory.
        const std::map<int, std::string> &codeMap = memory.code;

        // Continue execution as long as the EIP (Instruction Pointer) is within the codeMap boundaries.
        while (cu.getEip() <= codeMap.size() + 1) {
            // Fetch the next set of instructions from the codeMap.
            Instructions instructions = cu.fetchInstructions(codeMap, cu.getEip());

            // Execute the fetched instructions using the Control Unit (CU).
            cu.executeInstructions(instructions);
        }
    }
};

#endif //CPU_SIMULATOR_CPU_H
