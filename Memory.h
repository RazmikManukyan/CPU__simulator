#ifndef CPU_SIMULATOR_MEMORY_H
#define CPU_SIMULATOR_MEMORY_H
#include <iostream>
#include <map>
#include <fstream>
#include "Instructions.h"

// Define a struct to represent the program memory.
struct Memory {
    std::map<int, std::string> code;

    // Read program instructions from a file and populate the 'code' map.
    void readFromFile(const std::string &filename) {
        std::fstream file(filename);
        if (!file.is_open()) {
            throw std::runtime_error("Failed to open file: " + filename);
        }

        std::string lineText;
        int lineNumber = 1;
        std::string currentLine;

        bool foundStart = false;

        while (std::getline(file, lineText)) {
            if (!foundStart) {
                if (lineText.find("start:") != std::string::npos) {
                    // Found "start:", stop skipping lines and set the flag
                    foundStart = true;
                }
            } else {
                if (!lineText.empty() && lineText.back() == ':') {
                    std::string label = lineText.substr(0, lineText.size() - 1);
                    Instructions::label[lineNumber + 1] = label;
                }
                // Store the line in the code map, starting from line 1
                code[++lineNumber] = lineText;
            }
        }

        if (!foundStart) {
            throw std::runtime_error("No 'start:' marker found in the input file.");
        }

        file.close();
    }

    // Print the contents of the 'code' map (program instructions).
    void printCode() const {
        for (const auto &entry: code) {
            std::cout << "Line " << entry.first << ": " << entry.second << std::endl;
        }
    }
};


#endif //CPU_SIMULATOR_MEMORY_H
