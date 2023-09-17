#ifndef CPU_SIMULATOR_INSTRUCTIONSMAP_H
#define CPU_SIMULATOR_INSTRUCTIONSMAP_H
#include <vector>
#include <map>
#include "Functions.h"
#include "Instructions.h"
#include "Register.h"

// Define function pointer types for different instruction handler functions.
using InstructionHandlerVoid = void (*)(const std::vector<std::string>& operands, Register& reg);
using InstructionHandlerBool = bool (*)(const std::vector<std::string>& operands, Register& reg);
using InstructionHandlerInt = int (*)(const std::string& targetLabel, Register& reg, int& EIP);


// Define a struct to map instruction opcodes to their respective handler functions.
struct InstructionsMap {
    std::map<std::string, InstructionHandlerVoid> instructionsMapVoid;
    std::map<std::string, InstructionHandlerBool> instructionsMapBool;
    std::map<std::string, InstructionHandlerInt> instructionsMapInt;


    // Constructor to initialize the instruction maps.
    InstructionsMap(){
        // Void instructions
        instructionsMapVoid["mov"] = &Functions::mov;
        instructionsMapVoid["add"] = &Functions::add;
        instructionsMapVoid["sub"] = &Functions::sub;
        instructionsMapVoid["mul"] = &Functions::mul;
        instructionsMapVoid["div"] = &Functions::div;
        instructionsMapVoid["inc"] = &Functions::inc;
        instructionsMapVoid["dec"] = &Functions::dec;

        // Bool instructions
        instructionsMapBool["cmp"] = &Functions::cmp;

        // Int instructions (with EIP)
        instructionsMapInt["jmp"] = &Functions::jmp;
        instructionsMapInt["je"]  = &Functions::conditionalJumpEqual;
        instructionsMapInt["jne"] = &Functions::conditionalJumpNotEqual;
        instructionsMapInt["jg"]  = &Functions::conditionalJumpIfGreat;
        instructionsMapInt["jl"]  = &Functions::conditionalJumpIfLess;
    }
};


#endif //CPU_SIMULATOR_INSTRUCTIONSMAP_H
