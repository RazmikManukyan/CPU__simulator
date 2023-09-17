#ifndef CPU_SIMULATOR_CU_H
#define CPU_SIMULATOR_CU_H

#include <iostream>
#include "InstructionsMap.h"
#include "Register.h"
#include "Instructions.h"
#include "Functions.h"

class CU {
    Register *reg;
    InstructionsMap instructionsMap;
public:
    // Constructor takes a Register pointer as a parameter and initializes EIP.
    explicit CU(Register *reg) : reg(reg), EIP(2) {}

    // Fetch instructions from memory and return them as an Instructions object.
    Instructions fetchInstructions(const std::map<int, std::string> &memory, int EIP) {
        while (EIP > 0 && EIP - 1 <= memory.size()) {
            const std::string &instructionText = memory.at(EIP);
            if (!instructionText.empty() && instructionText.back() == ':') {
                ++EIP; // Skip labels
                continue;
            }
            if (instructionText == "end" || instructionText == "end:") {
                std::cout << "Program execution finished." << std::endl;
                reg->printRegisters();
                exit(0);
            }
            Instructions instructions = parseInstruction(instructionText, EIP);
            return instructions;
        }
        throw std::runtime_error("End of program.");
    }

    // Parse a single instruction and return it as an Instructions object.
    Instructions parseInstruction(const std::string &instructionText, int &lineNumber) {
        Instructions instructions;
        std::vector<std::string> tokens = Functions::split(instructionText, ' ');
        if (!tokens.empty() && tokens[0].back() == ':') {
            std::string label = tokens[0].substr(0, tokens[0].size() - 1);
            tokens.erase(tokens.begin());
        }

        if (!tokens.empty()) {
            instructions.opcode = tokens[0];
            tokens.erase(tokens.begin());
        }
        for (const auto &token: tokens) {
            instructions.operands.push_back(token);
        }

        return instructions;
    }

    // Execute the instructions based on their opcode and operands.
    void executeInstructions(const Instructions &instructions) {
        const std::string &opcode = instructions.opcode;
        const std::vector<std::string> &operands = instructions.operands;

        auto voidHandler = instructionsMap.instructionsMapVoid.find(opcode);
        auto boolHandler = instructionsMap.instructionsMapBool.find(opcode);
        auto intHandler = instructionsMap.instructionsMapInt.find(opcode);

        if (voidHandler != instructionsMap.instructionsMapVoid.end()) {
            // Call the corresponding void instruction handler
            voidHandler->second(operands, *reg);
        } else if (boolHandler != instructionsMap.instructionsMapBool.end()) {
            // Call the corresponding bool instruction handler
            bool cmpResult = boolHandler->second(operands, *reg);
            reg->setFlag("ZF", cmpResult);
        } else if (intHandler != instructionsMap.instructionsMapInt.end()) {
            // Call the corresponding int instruction handler
            EIP = intHandler->second(operands[0], *reg, EIP);
        } else {
            // Handle the case where the instruction is not found in any map
            throw std::runtime_error("Unknown instruction: " + opcode);
        }
        ++EIP;
    }

    // Get the current value of EIP (Instruction Pointer).
    int getEip() const {
        return EIP;
    }
private:
    int EIP; // The Instruction Pointer.
};

#endif //CPU_SIMULATOR_CU_H
