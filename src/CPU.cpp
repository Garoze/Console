#include <iostream>

#include "include/CPU/CPU.hpp"

#define STACK_START   0xFFFF
#define PROGRAM_START 0x0000

CPU::CPU()
{
    reset();

    opcode_t[Opcodes::NOP] = &CPU::NOP;
    opcode_t[Opcodes::HLT] = &CPU::HLT;
}

void CPU::reset()
{
    registers.SP = STACK_START;
    registers.PC = PROGRAM_START;

    for(auto& r: registers.R) r = 0;

    flags.Z = 0;
    flags.C = 0;
    flags.V = 0;

    status.running = true;
}

void CPU::loadToMemory(const std::vector<std::uint8_t>& code)
{
    for(size_t i = 0; i < code.size(); ++i)
        bus.write8(registers.PC + i, code.at(i));
}

void CPU::viewMemory(std::uint16_t address, int offset)
{
    bus.debugMemory(address, offset);
}

std::uint8_t CPU::fetch8()
{
    return bus.read8(registers.PC++);
}

std::uint16_t CPU::fetch16()
{
    auto value = bus.read16(registers.PC);
    registers.PC += 2;
    return value;
}

void CPU::stackPush(std::uint16_t value)
{
    registers.PC -= 2;
    bus.write16(registers.SP, value);
}

std::uint16_t CPU::stackPop()
{
    auto value = bus.read16(registers.SP);
    registers.SP += 2;
    return value;
}

Opcodes CPU::decode(std::uint8_t opcode)
{
    return (Opcodes)opcode;
}

void CPU::execute(Opcodes instruction)
{
    (this->*opcode_t[instruction])();
}

void CPU::step()
{
    do
    {
        printf("[ DEBUG ] STEP -> ");
        std::uint8_t op = fetch8();
        printf("PC: %04X ", registers.PC);
        auto instruction = decode(op);
        printf("Opcode: %02X Mnemonic: %s\t", op, Mnemonic_t.at(instruction).c_str());
        execute(instruction);
    }
    while(std::cin.get() != 'q');
}

void CPU::NOP() {}

void CPU::HLT()
{
    status.running = false;
}
