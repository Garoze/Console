#include "Memory/Memory.hpp"

class Bus
{
public:
    Bus();

    void write8(std::uint16_t, std::uint8_t);
    void write16(std::uint16_t, std::uint16_t);
    std::uint8_t read8(std::uint16_t);
    std::uint16_t read16(std::uint16_t);

    void debugMemory(std::uint16_t, int);
private:
    Memory memory;
};
