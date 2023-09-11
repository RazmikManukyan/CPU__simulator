#include "CU.h"
#include "CPU.h"
#include "Register.h"


int main() {

    Memory memory;
    memory.readFromFile("/Users/picsartacademy/CLionProjects/CPU simulator/code.txt");
    memory.printCode();

    auto* registers = new Register;
    CPU cpu(registers);
    cpu.run(memory);
}