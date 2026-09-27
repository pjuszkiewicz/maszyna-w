#pragma once

class ALU
{
public:
    ALU() = default;
    void Add(uint8_t value);
    void Subtract(uint8_t value);
    

private:
    uint8_t m_value = 0;
};