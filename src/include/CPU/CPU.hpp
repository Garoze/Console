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
    void INC();
    void DEC();
    void SHL();
    void SHR();
    void AND();
    void BOR();
    void XOR();
    void NOT();
    void PSI();
    void PSA();
    void PSR();
    void POP();
    void ADI();
    void ADA();
    void ADR();
    void ADS();
    void SUI();
    void SUA();
    void SUR();
    void SUS();
    void MUI();
    void MUA();
    void MUR();
    void MUS();
    void DIV();
    void DIA();
    void DIR();
    void DIS();
    void MOI();
    void MOA();
    void MOR();
    void MOS();
    void CMI();
    void CMA();
    void CMR();
    void CMS();
    void JMP();
    void JEQ();
    void JNQ();
    void JMC();
    void JNC();
    void JMO();
    void JNO();
    void JSR();
    void RTS();
    void OUT();
    void HLT();
private:
    Bus bus;
    Flags flags;
    Status status;
    Registers registers;
private:
    std::map<Opcodes, void(CPU::*)()> opcode_t;
};
