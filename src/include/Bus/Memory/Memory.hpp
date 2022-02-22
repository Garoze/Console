#pragma once

#include <array>
#include <cstdint>

#define MEMORY_SIZE 64 * 1024

class Memory
{
public:
    Memory();

    void viewAt(std::uint16_t);
public:
    std::uint8_t& operator[](std::uint16_t i)
    {
        return data[i];
    }
private:
    std::array<std::uint8_t, MEMORY_SIZE> data;
};
