#pragma once

#include <array>
#include <cstdint>

struct Registers
{
    std::uint16_t PC;
    std::uint16_t SP;
    std::array<std::uint16_t, 9> R;
};

