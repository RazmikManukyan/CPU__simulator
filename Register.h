#ifndef CPU_SIMULATOR_REGISTERS_H
#define CPU_SIMULATOR_REGISTERS_H
#include <iostream>
#include <vector>
#include <map>

// Define a struct to store CPU flags (e.g., Zero Flag, Greater Than Flag).
struct Flags {
    bool ZF;// Zero Flag
    bool GT;// Greater Than Flag
    Flags(): ZF(false), GT(false) {}// Initialize flags to false.
};

// Define a class to represent CPU registers and flags.
class Register{
    std::map<std::string, int> reg;// Map to store register values.
    Flags flags;// Flags object to store CPU flags.
public:
    Register() {
        // Initialize default registers (R1-R9) with initial values of 0.
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

    // Get the value of a specific register by name.
    int getRegisterValue(const std::string& name) {
        if (reg.find(name) != reg.end()) {
            return reg[name];
        }
        throw std::runtime_error("Register '" + name + "' not found!" );
    }

    // Set the value of a specific register by name.
    void setRegisterValue(const std::string& name, int value) {
        if(reg.find(name) != reg.end()) {
            reg[name] = value;
        } else {
            throw std::runtime_error("Register '" + name + "' not found!");
        }
    }

    // Check if a register with the given name exists.
    bool containsRegister(const std::string& registerName) const {
        return reg.find(registerName) != reg.end();
    }

    // Print the values of registers (all or a specific one).
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

    // Set a CPU flag by name (e.g., "ZF" for Zero Flag, "GT" for Greater Than Flag).
    void setFlag(const std::string& flagName, bool value) {
        if (flagName == "ZF") {
            flags.ZF = value;
        } else if (flagName == "GT") {
            flags.GT = value;
        }  else {
            throw std::runtime_error("Invalid flag name: " + flagName);
        }
    }

    // Get the value of a CPU flag by name (e.g., "ZF" for Zero Flag, "GT" for Greater Than Flag).
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
