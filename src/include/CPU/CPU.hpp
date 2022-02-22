#pragma once

#include <vector>

#include "Flags/Flags.hpp"
#include "Opcodes/Opcodes.hpp"
#include "Opcodes/Mnemonics.hpp"
#include "Registers/Registers.hpp"

#include "../Bus/Bus.hpp"

class CPU
{
public:
    CPU();

    void step();
public:
    void reset();
    void loadToMemory(const std::vector<std::uint8_t>&);
    void viewMemory(std::uint16_t, int = 20);
private:
    std::uint8_t fetch8();
    std::uint16_t fetch16();
    Opcodes decode(std::uint8_t);
    void execute(Opcodes);
private:
    void stackPush(std::uint16_t);
    std::uint16_t stackPop();
private:
    void NOP();
    void HLT();
private:
    Bus bus;
    Flags flags;
    Status status;
    Registers registers;
private:
    std::map<Opcodes, void(CPU::*)()> opcode_t;
};
