#ifndef CPU_SIMULATOR_FUNCTIONS_H
#define CPU_SIMULATOR_FUNCTIONS_H

#include <iostream>
#include <map>
#include "Register.h"
#include "Instructions.h"

namespace Functions {
    std::vector<std::string> split(const std::string &s, char delimiter) {
        std::vector<std::string> tokens;
        std::string token;

        int i = 0;
        while (s[i] == delimiter) {
            i++;
        }

        for (i; s[i] != '\0'; ++i) {
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
}

#endif //CPU_SIMULATOR_FUNCTIONS_H
