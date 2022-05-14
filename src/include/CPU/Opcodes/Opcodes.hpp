#pragma once

#include <cstdint>

enum class Opcodes : std::uint8_t
{
    NOP,
    LDI, LDA, LDR,
    STI, STA, STR,
    INC, DEC,
    SHL, SHR,
    AND, BOR, XOR, NOT,
    PSI, PSA, PSR,
    POP,
    ADI, ADA, ADR, ADS,
    SUI, SUA, SUR, SUS,
    MUI, MUA, MUR, MUS,
    DIV, DIA, DIR, DIS,
    MOI, MOA, MOR, MOS,
    CMI, CMA, CMR, CMS,
    JMP,
    JEQ, JNQ,
    JMC, JNC,
    JMO, JNO,
    JSR,
    RTS,
    OUT,
    HLT,
};
