#ifndef CPU_SIMULATOR_REGISTERS_H
#define CPU_SIMULATOR_REGISTERS_H
#include <iostream>
#include <vector>
#include <map>

struct Flags {
    bool ZF;
    bool GT;
    Flags(): ZF(false), GT(false) {}
};

class Register{
    std::map<std::string, int> reg;
    Flags flags;
public:
    Register() {
        reg["R1"] = 0;
        reg["R2"] = 0;
        reg["R3"] = 0;
        reg["R4"] = 0;
        reg["R5"] = 0;
        reg["R6"] = 0;
        reg["R7"] = 0;
        reg["R8"] = 0;
        reg["R9"] = 0;
    }

    int getRegisterValue(const std::string& name) {
        if (reg.find(name) != reg.end()) {
            return reg[name];
        }
        throw std::runtime_error("Register '" + name + "' not found!" );
    }

    void setRegisterValue(const std::string& name, int value) {
        if(reg.find(name) != reg.end()) {
            reg[name] = value;
        } else {
            throw std::runtime_error("Register '" + name + "' not found!");
        }
    }

    bool containsRegister(const std::string& registerName) const {
        return reg.find(registerName) != reg.end();
    }

    void printRegisters(const std::string& registerName = "") const {
        if(registerName.empty()) {
            for(const auto& pair : reg) {
                std::cout << pair.first << ":" << pair.second << std::endl;
            }
        } else {
            if(reg.find(registerName) != reg.end()) {
                std::cout << registerName << ":" << reg.at(registerName) << std::endl;
            } else {
                throw std::runtime_error("Register '" + registerName + "' not found!");
            }
        }
    }

    void setFlag(const std::string& flagName, bool value) {
        if (flagName == "ZF") {
            flags.ZF = value;
        } else if (flagName == "GT") {
            flags.GT = value;
        }  else {
            throw std::runtime_error("Invalid flag name: " + flagName);
        }
    }

    bool getFlag(const std::string& flagName) const {
        if (flagName == "ZF") {
            return flags.ZF;
        } else if (flagName == "GT") {
            return flags.GT;
        } else {
            throw std::runtime_error("Invalid flag name: " + flagName);
        }
    }
};

#endif //CPU_SIMULATOR_REGISTERS_H
