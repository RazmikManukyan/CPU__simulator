#ifndef CPU_SIMULATOR_FUNCTIONS_H
#define CPU_SIMULATOR_FUNCTIONS_H

#include <iostream>
#include <map>
#include "Register.h"
#include "Instructions.h"

namespace Functions {
    // Split a string into tokens based on a delimiter and remove leading/trailing whitespaces.
    std::vector<std::string> split(const std::string &s, char delimiter) {
        std::vector<std::string> tokens;
        std::string token;

        int i = 0;
        while (s[i] == delimiter) {
            i++;
        }

        for (; s[i] != '\0'; ++i) {
            if (s[i] == delimiter) {
                tokens.push_back(token);
                token.clear();
            } else {
                token += s[i];
            }
        }
        tokens.push_back(token);

        for (int j = 0; j < tokens.size(); ++j) {
            if (tokens[j].front() == 'R' && tokens[j].back() == ',') {
                tokens[j].pop_back();
            }
        }

        return tokens;
    }

    // Handle the 'mov' instruction: Move a value from source to destination.
    void mov(const std::vector<std::string> &operands, Register &reg) {
        if (operands.size() != 2) {
            throw std::runtime_error("Invalid 'mov' instruction: Incorrect number of operands.");
        }

        const std::string &destination = operands[0];
        const std::string &source = operands[1];

        try {
            int sourceValue = std::stoi(source);
            reg.setRegisterValue(destination, sourceValue);
        } catch (const std::invalid_argument &e) {
            if(reg.containsRegister(source)){
                int sourceValue = reg.getRegisterValue(source);
                reg.setRegisterValue(destination, sourceValue);
            } else {
                throw std::runtime_error("Invalid 'add' instruction: Operand is not a valid number.");
            }
        }
    }

    // Handle the 'add' instruction: Add values from source to destination.
    void add(const std::vector<std::string> &operands, Register &reg) {
        if (operands.size() != 2) {
            throw std::runtime_error("Invalid 'add' instruction: Incorrect number of operands.");
        }
        const std::string &destination = operands[0];
        const std::string &source = operands[1];

        try {
            int sourceValue = std::stoi(source);
            int currentValue = reg.getRegisterValue(destination);
            reg.setRegisterValue(destination, sourceValue + currentValue);
        } catch (const std::invalid_argument &e) {
            if(reg.containsRegister(source)){
                int sourceValue = reg.getRegisterValue(source);
                int currentValue = reg.getRegisterValue(destination);
                reg.setRegisterValue(destination, sourceValue + currentValue);
            } else {
                throw std::runtime_error("Invalid 'add' instruction: Operand is not a valid number.");
            }
        }
    }

    // Handle the 'sub' instruction: Subtract values from source to destination.
    void sub(const std::vector<std::string> &operands, Register &reg) {
        if(operands.size() != 2) {
            throw std::runtime_error("Invalid 'sub' instructions: Incorrect number of operands.");
        }
        const std::string &destination = operands[0];
        const std::string &source = operands[1];

        try{
            int sourceNum = std::stoi(source);
            int currentValue = reg.getRegisterValue(destination);
            reg.setRegisterValue(destination, currentValue - sourceNum);
        } catch (const std::invalid_argument& e) {
            if(reg.containsRegister(source)) {
                int sourceValue = reg.getRegisterValue(source);
                int currentValue = reg.getRegisterValue(destination);
                reg.setRegisterValue(destination, currentValue - sourceValue);
            } else {
                throw std::runtime_error("Invalid 'sub' instruction: Operand is not a valid number or register.");
            }
        }
    }

    // Handle the 'mul' instruction: Multiply values from source to destination.
    void mul(const std::vector<std::string> &operands, Register &reg) {
        if(operands.size() != 2) {
            throw std::runtime_error("Invalid 'sub' instructions: Incorrect number of operands.");
        }
        const std::string &destination = operands[0];
        const std::string &source = operands[1];

        try{
            int sourceValue = std::stoi(source);
            int currentValue = reg.getRegisterValue(destination);
            reg.setRegisterValue(destination, sourceValue * currentValue);
        } catch (const std::invalid_argument& e) {
            if(reg.containsRegister(source)) {
                int sourceValue = reg.getRegisterValue(source);
                int currentValue = reg.getRegisterValue(destination);
                reg.setRegisterValue(destination, sourceValue * currentValue);
            } else {
                throw std::runtime_error("Invalid 'sub' instruction: Operand is not a valid number or register.");
            }
        }
    }

    // Handle the 'div' instruction: Divide values from source to destination.
    void div(const std::vector<std::string> &operands, Register &reg) {
        if(operands.size() != 2) {
            throw std::runtime_error("Invalid 'sub' instructions: Incorrect number of operands.");
        }
        const std::string &destination = operands[0];
        const std::string &source = operands[1];

        try{
            int sourceValue = std::stoi(source);

            if(sourceValue == '0') {
                throw std::runtime_error("Division by zero.");
            }

            int currentValue = reg.getRegisterValue(destination);
            reg.setRegisterValue(destination, currentValue / sourceValue);
        } catch (const std::invalid_argument& e) {
            if(reg.containsRegister(source)) {
                int sourceValue = reg.getRegisterValue(source);
                if (sourceValue == 0) {
                    throw std::runtime_error("Division by zero.");
                }
                int currentValue = reg.getRegisterValue(destination);
                reg.setRegisterValue(destination, currentValue / sourceValue);
            } else {
                throw std::runtime_error("Invalid 'div' instruction: Operand is not a valid number or register.");
            }
        }
    }

    // Handle the 'cmp' instruction: Compare two values and set flags.
    bool cmp(const std::vector<std::string> &operands, Register &reg) {
        if (operands.size() != 2) {
            throw std::runtime_error("Invalid 'sub' instructions: Incorrect number of operands.");
        }
        const std::string &value1 = operands[0];
        const std::string &value2 = operands[1];

        int num1, num2;
        try {
            num1 = std::stoi(value1);
        } catch (const std::invalid_argument& e) {
            if(reg.containsRegister(value1)) {
                num1 = reg.getRegisterValue(value1);
            } else {
                throw std::runtime_error("Invalid 'cmp' instruction: Operand 1 is not a valid number or register.");
            }
        }

        try {
            num2 = std::stoi(value2);
        } catch (const std::invalid_argument& e) {
            if(reg.containsRegister(value2)) {
                num2 = reg.getRegisterValue(value2);
            } else {
                throw std::runtime_error("Invalid 'cmp' instruction: Operand 1 is not a valid number or register.");
            }
        }
        // Compare the operands and set flags
        reg.setFlag("ZF", num1 == num2);
        reg.setFlag("GT", num1 > num2);
        return (num1 == num2);
    }

    // Handle unconditional jump ('jmp') to a target label.
    int jmp(const std::string& targetLabel,Register& reg, int& EIP) {
        for(const auto& label : Instructions::label) {
            if(targetLabel == label.second) {
                EIP = label.first;
                std::cout << EIP << "EIP";
                return EIP + 1;
            }
        }
        throw std::runtime_error("Label not found: " + targetLabel);
    }

    // Handle conditional jump if equal ('je') to a target label.
    int conditionalJumpEqual(const std::string& targetLabel,Register& reg, int& EIP) {
        if(reg.getFlag("ZF")) {
            for (const auto &label: Instructions::label) {
                if (targetLabel == label.second) {
                    EIP = label.first;
                    return EIP;
                }
            }
        }
        return EIP;
    }

    // Handle conditional jump if not equal ('jne') to a target label.
    int conditionalJumpNotEqual(const std::string& targetLabel,Register& reg, int& EIP) {
        if(!reg.getFlag("ZF")) {
            for (const auto &label: Instructions::label) {
                if (targetLabel == label.second) {
                    EIP = label.first;
                    return EIP;
                }
            }
        }
        return EIP;
    }

    // Handle conditional jump if greater ('jg') to a target label.
    int conditionalJumpIfGreat(const std::string& targetLabel,Register& reg, int& EIP) {
        if(reg.getFlag("GT")) {
            for (const auto &label: Instructions::label) {
                if (targetLabel == label.second) {
                    EIP = label.first;
                    return EIP;
                }
            }
        }
        return EIP;
    }

    // Handle conditional jump if less ('jl') to a target label.
    int conditionalJumpIfLess(const std::string& targetLabel,  Register& reg, int& EIP) {
        if(!reg.getFlag("GT")) {
            for (const auto &label: Instructions::label) {
                if (targetLabel == label.second) {
                    EIP = label.first;
                    return EIP;
                }
            }
        }
        return EIP;
    }

    // Increment the value of a register by 1.
    void inc(const std::vector<std::string>& operands, Register& reg) {
        if (operands.size() != 1) {
            throw std::runtime_error("Invalid 'inc' instruction: Incorrect number of operands.");
        }

        const std::string& destination = operands[0];

        try {
            int currentValue = reg.getRegisterValue(destination);
            reg.setRegisterValue(destination, currentValue + 1);
        } catch (const std::runtime_error& e) {
            throw std::runtime_error("Invalid 'inc' instruction: ");
        }
    }

    // Decrement the value of a register by 1.
    void dec(const std::vector<std::string>& operands, Register& reg) {
        if (operands.size() != 1) {
            throw std::runtime_error("Invalid 'dec' instruction: Incorrect number of operands.");
        }

        const std::string& destination = operands[0];

        try {
            int currentValue = reg.getRegisterValue(destination);
            reg.setRegisterValue(destination, currentValue - 1);
        } catch (const std::runtime_error& e) {
            throw std::runtime_error("Invalid 'dec' instruction: ");
        }
    }
}

#endif //CPU_SIMULATOR_FUNCTIONS_H
