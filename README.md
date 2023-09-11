# CPU Simulator

A simple CPU simulator implemented in C++.

## Table of Contents

- [Introduction](#introduction)
- [Features](#features)
- [Getting Started](#getting-started)
- [Usage](#usage)
- [Project Structure](#project-structure)
- [Contributing](#contributing)

## Introduction

The CPU Simulator is a C++ program that emulates the behavior of a simple CPU. It reads a program from memory and executes instructions based on the provided code.

## Features

- Fetching instructions from memory.
- Parsing and executing a variety of CPU instructions.
- Register management.
- Conditional execution using flags.

## Getting Started

### Prerequisites

To compile and run the CPU Simulator, you need:

- C++ compiler (supporting C++11 or later)
- Make sure you have a compatible C++ development environment installed.

### Installation

1. Clone this repository:

   ```shell
   git clone https://github.com/your-username/cpu-simulator.git
   ```

2. Change into the project directory:

   ```shell
   cd cpu-simulator
   ```

3. Compile the code:

   ```shell
   g++ -o cpu_simulator main.cpp Registers.cpp Instructions.cpp Functions.cpp -std=c++11
   ```

4. Run the CPU Simulator:

   ```shell
   ./cpu_simulator
   ```

## Usage

1. Create a program file with your CPU instructions.
2. Load the program into memory.
3. Run the CPU simulator.
4. Monitor the program's execution and inspect register values.

Example program file:

```assembly
start:
    mov eax, 42
    cmp eax, 50
    jl below_50
    mov ebx, 1
    jmp end
below_50:
    mov ebx, 0
end:
    ...
```

## Project Structure

The project is organized as follows:

- `main.cpp`: The main entry point of the simulator.
- `Registers.cpp`: Implementation of the CPU registers.
- `Instructions.cpp`: Implementation of instruction execution logic.
- `Functions.cpp`: Utility functions for parsing and splitting instructions.
- `InstructionsMap.h`: Map of supported instructions.
- `Registers.h`: Header file for register management.
- `Instructions.h`: Header file for instruction execution.
- `CU.h`: Central Unit class for instruction fetching and execution.
- `README.md`: This documentation file.

## Contributing

Contributions are welcome! If you have any improvements, bug fixes, or new features to add, please open an issue or create a pull request.

Make sure to replace placeholders like `your-username` with your actual GitHub username and customize the content as needed to match your project's specifics.
