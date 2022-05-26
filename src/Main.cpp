#include <vector>
#include <iostream>

#include "include/CPU/CPU.hpp"

int main()
{
    CPU cpu;
    cpu.setDebug(true);

    const std::vector<std::uint8_t> code = {
        (int)Opcodes::LDI, 0x01, 0x01, 0x00,
        (int)Opcodes::SHL, 0x01, 0x01,
        (int)Opcodes::OUT, 0x01,
        (int)Opcodes::HLT,
    };
    cpu.loadToMemory(code);
    cpu.step();

    printf("\nMain Memory:\n");
    cpu.viewMemory(0x0000, 2);
    // printf("\nStack Memory:\n");
    // cpu.viewMemory(0xFFEF, 2);

    return EXIT_SUCCESS;
}
