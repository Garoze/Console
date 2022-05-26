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
    void setDebug(bool);
private:
    std::uint8_t fetch8();
    std::uint16_t fetch16();
    Opcodes decode(std::uint8_t);
    void execute(Opcodes);
private:
    void stackPush(std::uint16_t);
    std::uint16_t stackPop();
private:
    void NOP(); // NOP
    void LDI(); // Load Immediate
    void LDA(); // Load Absolure
    void LDR(); // Load Register
    void STI(); // Store Immediate
    void STA(); // Store Absolure
    void STR(); // Store Register
    void SHL(); // Shift Register Left
    void SHR(); // Shift Register Right
    void AND(); // AND Register
    void BOR(); // BOR Register
    void XOR(); // XOR Register
    void NOT(); // NOT Register
    void PSI(); // Push Immediate
    void PSA(); // Push Absolure
    void PSR(); // Push Register
    void POP(); // Pop to Register
    void INC(); // Increment Register
    void DEC(); // Decrement Register
    void ADI(); // ADD to a register a Immediate value
    void ADA(); // ADD to a register a Absolute value
    void ADR(); // ADD to a register a register value
    void SUI(); // SUB to a register a Immediate value
    void SUA(); // SUB to a register a Absolute value
    void SUR(); // SUB to a register a register value
    void MUI();
    void MUA();
    void MUR();
    void DIV();
    void DIA();
    void DIR(); // DIV
    void MOI();
    void MOA();
    void MOR(); // MOR
    void CMI();
    void CMA();
    void CMR(); //CMP
    void JMP();
    void JEQ();
    void JNQ();
    void JMC();
    void JNC();
    void JMO();
    void JNO();
    void JSR();
    void RTS();
    void OUT(); // Print a Register value
    void HLT(); // Halt the CPU
private:
    Bus bus;
    Flags flags;
    Status status;
    Registers registers;
private:
    std::map<Opcodes, void(CPU::*)()> opcode_t;
};
