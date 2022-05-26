#pragma once

#include <cstdint>

enum class Opcodes : std::uint8_t
{
    NOP,
    LDI, LDA, LDR,
    STI, STA, STR,
    SHL, SHR,
    AND, BOR, XOR, NOT,
    PSI, PSA, PSR,
    POP,
    INC, DEC,
    ADI, ADA, ADR,
    SUI, SUA, SUR,
    MUI, MUA, MUR,
    DIV, DIA, DIR,
    MOI, MOA, MOR,
    CMI, CMA, CMR,
    JMP,
    JEQ, JNQ,
    JMC, JNC,
    JMO, JNO,
    JSR,
    RTS,
    OUT,
    HLT,
};
