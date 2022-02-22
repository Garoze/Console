#include <cstdio>

#include "include/Bus/Memory/Memory.hpp"

Memory::Memory()
{
    for (auto& b : data)
        b = 0;
}

void Memory::viewAt(std::uint16_t address)
{
    printf("0x%04X: ", address);
    for (int i = 1; i <= 16; ++i)
        printf("%02X ", data[address++]);

    printf("\n");
}

