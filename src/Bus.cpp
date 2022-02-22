#include "include/Bus/Bus.hpp"

Bus::Bus()
{}

void Bus::write8(std::uint16_t address, std::uint8_t value)
{
    memory[address] = value;
}

void Bus::write16(std::uint16_t address, std::uint16_t value)
{
    memory[address + 0] = value;
    memory[address + 1] = value >> 8;
}

std::uint8_t Bus::read8(std::uint16_t address)
{
    return memory[address];
}

std::uint16_t Bus::read16(std::uint16_t address)
{
    auto value = (read8(address + 1) << 8) | read8(address);
    return value;
}

void Bus::debugMemory(std::uint16_t address, int offset)
{
    for (std::uint16_t i = 1; i <= offset; ++i)
    {
        memory.viewAt(address);
        address += 16;
    }
}

