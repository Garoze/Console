#include <vector>
#include <iostream>

#include "include/CPU/CPU.hpp"

int main()
{
    CPU cpu;
    cpu.setDebug(true);

    const std::vector<std::uint8_t> code = {
        (int)Opcodes::LDI, 0x01, 0xCD, 0xAB,
        (int)Opcodes::STR, 0xEF, 0xFF, 0x01,
        (int)Opcodes::STA, 0xFF, 0xFF, 0xEF, 0xFF,
        (int)Opcodes::LDA, 0x02, 0xEF, 0xFF,
        (int)Opcodes::OUT, 0x02,
        (int)Opcodes::HLT,
    };
    cpu.loadToMemory(code);
    cpu.step();

    printf("\nMain Memory:\n");
    cpu.viewMemory(0x0000, 2);
    printf("\nStack Memory:\n");
    cpu.viewMemory(0xFFEF, 2);

    return EXIT_SUCCESS;
}
