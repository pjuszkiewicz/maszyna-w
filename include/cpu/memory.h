#pragma once

#include <cstdint>

class Memory
{
public:
    Memory()
    {
        for (int i = 0; i < 31; i++)
        {
            m_data[i] = 0;
        }
    }

    int GetAddress() { return m_address; }
    void SetAddress(int address) { m_address = address; }
    uint8_t ReadData() { return m_data[m_address]; }
    void WriteData(uint8_t data) { m_data[m_address] = data; }

private:
    int m_address = 0;
    uint8_t m_data[32];
};