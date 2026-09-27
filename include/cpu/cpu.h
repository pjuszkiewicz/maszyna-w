#pragma once

#include "cpu/alu.h"
#include "cpu/memory.h"

class CPU
{
public:
    CPU() = default;

    void Step();

private:
    ALU m_alu;
    Memory m_memory;
};
