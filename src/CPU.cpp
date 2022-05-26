#include <iostream>

#include "include/CPU/CPU.hpp"

#define STACK_START   0xFFFF
#define PROGRAM_START 0x0000

CPU::CPU()
{
    reset();
    // NOP //
    opcode_t[Opcodes::NOP] = &CPU::NOP;
    // Load Opcodes //
    opcode_t[Opcodes::LDI] = &CPU::LDI;
    opcode_t[Opcodes::LDA] = &CPU::LDA;
    opcode_t[Opcodes::LDR] = &CPU::LDR;
    // Store Opcodes //
    opcode_t[Opcodes::STI] = &CPU::STI;
    opcode_t[Opcodes::STA] = &CPU::STA;
    opcode_t[Opcodes::STR] = &CPU::STR;
    // Arithmetic Opcodes //
    opcode_t[Opcodes::INC] = &CPU::INC;
    opcode_t[Opcodes::DEC] = &CPU::DEC;
    // Stack Opcodes //
    opcode_t[Opcodes::PSI] = &CPU::PSI;
    opcode_t[Opcodes::PSA] = &CPU::PSA;
    opcode_t[Opcodes::PSR] = &CPU::PSR;
    opcode_t[Opcodes::POP] = &CPU::POP;
    // OUT //
    opcode_t[Opcodes::OUT] = &CPU::OUT;
    // HLT //
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

void CPU::setDebug(bool debug)
{
    flags.debug = debug;
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
    registers.SP -= 2;
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
        auto op = fetch8();
        printf("PC: %04X ", registers.PC);
        auto instruction = decode(op);
        printf("Opcode: %02X Asm: %s ", op, Mnemonic_t.at(instruction).c_str());
        execute(instruction);
    }
    while(std::cin.get() != 'q');
}

void CPU::NOP() {}

void CPU::LDI()
{
    auto r = fetch8();
    auto value = fetch16();
    if (flags.debug) printf("R%d, #%04X", r, value);
    registers.R[r] = value;
}

void CPU::LDA()
{
    auto r = fetch8();
    auto address = fetch16();
    if (flags.debug) printf("R%d, [$%04X]", r, address);
    registers.R[r] = bus.read16(address);
}

void CPU::LDR()
{
    auto r = fetch8();
    auto s = fetch8();
    if (flags.debug) printf("R%d, R%d", r, s);
    registers.R[r] = registers.R[s];
}

void CPU::STI()
{
    auto address = fetch16();
    auto value = fetch16();
    if (flags.debug) printf("$%04X, #%4X", address, value);
    bus.write16(address, value);
}

void CPU::STA()
{
    auto dst = fetch16();
    auto src = fetch16();
    if (flags.debug) printf("$%04X, [$%04X]", dst, src);
    bus.write16(dst, bus.read16(src));
}

void CPU::STR()
{
    auto address = fetch16();
    auto r = fetch8();
    if (flags.debug) printf("$%04X, R%d", address, r);
    bus.write16(address, registers.R[r]);
}

void CPU::INC()
{
    auto r = fetch8();
    ++registers.R[r];
}

void CPU::DEC()
{
    auto r = fetch8();
    --registers.R[r];
}

void CPU::PSI()
{
    auto value = fetch16();
    if (flags.debug) printf("$%04X", value);
    stackPush(value);
}

void CPU::PSA()
{
    auto address = fetch16();
    if (flags.debug) printf("$%04X", address);
    stackPush(bus.read16(address));
}
void CPU::PSR()
{
    auto r = fetch8();
    if (flags.debug) printf("R%d", r);
    stackPush(registers.R[r]);
}

void CPU::POP()
{
    auto r = fetch8();
    if (flags.debug) printf("R%d", r);
    registers.R[r] = stackPop();
}

void CPU::OUT()
{
    auto r = fetch8();
    printf("R%d -> #%04X", r, registers.R[r]);
}

void CPU::HLT()
{
    status.running = false;
}
