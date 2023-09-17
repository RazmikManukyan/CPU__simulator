#include "CU.h"
#include "CPU.h"
#include "Register.h"


int main() {

    Memory memory;
    memory.readFromFile("/Users/picsartacademy/CLionProjects/CPU__simulator/assambly.txt");
    memory.printCode();

    auto* registers = new Register;
    CPU cpu(registers);
    cpu.run(memory);
}