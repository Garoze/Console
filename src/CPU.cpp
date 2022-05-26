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
    // Bitwise Opcodes //
    opcode_t[Opcodes::SHL] = &CPU::SHL;
    opcode_t[Opcodes::SHR] = &CPU::SHR;
    opcode_t[Opcodes::AND] = &CPU::AND;
    opcode_t[Opcodes::BOR] = &CPU::BOR;
    opcode_t[Opcodes::XOR] = &CPU::XOR;
    opcode_t[Opcodes::NOT] = &CPU::NOT;
    // Stack Opcodes //
    opcode_t[Opcodes::PSI] = &CPU::PSI;
    opcode_t[Opcodes::PSA] = &CPU::PSA;
    opcode_t[Opcodes::PSR] = &CPU::PSR;
    opcode_t[Opcodes::POP] = &CPU::POP;
    // Increment Opcodes //
    opcode_t[Opcodes::INC] = &CPU::INC;
    opcode_t[Opcodes::DEC] = &CPU::DEC;
    // Arithmetic Opcodes //
                            // ADD //
    opcode_t[Opcodes::ADI] = &CPU::ADI;
    opcode_t[Opcodes::ADA] = &CPU::ADA;
    opcode_t[Opcodes::ADR] = &CPU::ADR;
                            // SUB //
    opcode_t[Opcodes::SUI] = &CPU::SUI;
    opcode_t[Opcodes::SUA] = &CPU::SUA;
    opcode_t[Opcodes::SUR] = &CPU::SUR;
                            // MUL //
    opcode_t[Opcodes::MUI] = &CPU::MUI;
    opcode_t[Opcodes::MUA] = &CPU::MUA;
    opcode_t[Opcodes::MUR] = &CPU::MUR;
                            // DIV //
    opcode_t[Opcodes::DIV] = &CPU::DIV;
    opcode_t[Opcodes::DIA] = &CPU::DIA;
    opcode_t[Opcodes::DIR] = &CPU::DIR;
                            // MOD //
    opcode_t[Opcodes::MOI] = &CPU::MOI;
    opcode_t[Opcodes::MOA] = &CPU::MOA;
    opcode_t[Opcodes::MOR] = &CPU::MOR;
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

void CPU::SHL()
{
    auto r = fetch8();
    auto value = fetch8();
    if (flags.debug) printf("R%d, #%02X", r, value);
    registers.R[r] <<= value;
}

void CPU::SHR()
{
    auto r = fetch8();
    auto value = fetch8();
    if (flags.debug) printf("R%d, #%02X", r, value);
    registers.R[r] >>= value;
}

void CPU::AND()
{
    auto r = fetch8();
    auto value = fetch8();
    if (flags.debug) printf("R%d, #%02X", r, value);
    registers.R[r] &= value;
}

void CPU::BOR()
{
    auto r = fetch8();
    auto value = fetch8();
    if (flags.debug) printf("R%d, #%02X", r, value);
    registers.R[r] |= value;
}

void CPU::XOR()
{
    auto r = fetch8();
    auto value = fetch8();
    if (flags.debug) printf("R%d, #%02X", r, value);
    registers.R[r] ^= value;
}

void CPU::NOT()
{
    auto r = fetch8();
    auto value = registers.R[r];
    if (flags.debug) printf("R%d", r);
    registers.R[r] = ~value;
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

void CPU::INC()
{
    auto r = fetch8();
    if (flags.debug) printf("R%d", r);
    ++registers.R[r];
}

void CPU::DEC()
{
    auto r = fetch8();
    if (flags.debug) printf("R%d", r);
    --registers.R[r];
}

void CPU::ADI()
{
    auto r = fetch8();
    auto value = fetch16();
    if (flags.debug) printf("R%d, #%04X", r, value);
    registers.R[r] += value;
}

void CPU::ADA()
{
    auto r = fetch8();
    auto address = fetch16();
    if (flags.debug) printf("R%d, [$%04X]", r, address);
    registers.R[r] += bus.read16(address);
}

void CPU::ADR()
{
    auto dst = fetch8();
    auto src = fetch8();
    if (flags.debug) printf("R%d, R%d", dst, src);
    registers.R[dst] = registers.R[src];
}

void CPU::SUI()
{
    auto r = fetch8();
    auto value = fetch16();
    if (flags.debug) printf("R%d, #%04X", r, value);
    registers.R[r] -= value;
}

void CPU::SUA()
{
    auto r = fetch8();
    auto address = fetch16();
    if (flags.debug) printf("R%d, [$%04X]", r, address);
    registers.R[r] -= bus.read16(address);
}

void CPU::SUR()
{
    auto dst = fetch8();
    auto src = fetch8();
    if (flags.debug) printf("R%d, R%d", dst, src);
    registers.R[dst] -= registers.R[src];
}

void CPU::MUI()
{
    auto r = fetch8();
    auto value = fetch16();
    if (flags.debug) printf("R%d, #%04X", r, value);
    registers.R[r] *= value;
}

void CPU::MUA()
{
    auto r = fetch8();
    auto address = fetch16();
    if (flags.debug) printf("R%d, [$%04X]", r, address);
    registers.R[r] *= bus.read16(address);
}

void CPU::MUR()
{
    auto dst = fetch8();
    auto src = fetch8();
    if (flags.debug) printf("R%d, R%d", dst, src);
    registers.R[dst] *= registers.R[src];
}

void CPU::DIV()
{
    auto r = fetch8();
    auto value = fetch16();
    if (flags.debug) printf("R%d, #%04X", r, value);
    registers.R[r] /= value;
}

void CPU::DIA()
{
    auto r = fetch8();
    auto address = fetch16();
    if (flags.debug) printf("R%d, [$%04X]", r, address);
    registers.R[r] /= bus.read16(address);
}

void CPU::DIR()
{
    auto dst = fetch8();
    auto src = fetch8();
    if (flags.debug) printf("R%d, R%d", dst, src);
    registers.R[dst] /= registers.R[dst];
}

void CPU::MOI()
{
    auto r = fetch8();
    auto value = fetch16();
    if (flags.debug) printf("R%d, #%04X", r, value);
    registers.R[r] %= value;
}

void CPU::MOA()
{
    auto r = fetch8();
    auto address = fetch16();
    if (flags.debug) printf("R%d, [$%04X]", r, address);
    registers.R[r] %= bus.read16(address);
}

void CPU::MOR()
{
    auto dst = fetch8();
    auto src = fetch8();
    if (flags.debug) printf("R%d, R%d", dst, src);
    registers.R[dst] %= registers.R[src];
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
