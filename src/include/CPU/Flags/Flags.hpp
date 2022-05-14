#pragma once

#include <cstdint>

struct Status
{
    bool running;
};

struct Flags
{
    bool debug = false;
    std::uint8_t Z : 1;
    std::uint8_t C : 1;
    std::uint8_t V : 1;
};
