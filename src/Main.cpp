#include <vector>
#include <iostream>

#include "include/CPU/CPU.hpp"

int main()
{
    CPU cpu;

    const std::vector<std::uint8_t> code = {
        (int)Opcodes::NOP,
        (int)Opcodes::HLT,
    };
    cpu.loadToMemory(code);
    cpu.step();

    printf("\nMain Memory:\n");
    cpu.viewMemory(0x0000, 2);

    return EXIT_SUCCESS;
}
