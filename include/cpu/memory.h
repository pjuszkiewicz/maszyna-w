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

    // External functions
    bool GetCzyt() { return m_czyt; }
    void SetCzyt(bool value) { m_czyt = value; }

    bool GetPisz() { return m_pisz; }
    void SetPisz(bool value) { m_pisz = value; }

    bool GetWys() { return m_wys; }
    void SetWys(bool value) { m_wys = value; }

    bool GetWes() { return m_wes; }
    void SetWes(bool value) { m_wes = value; }

private:
    int m_address = 0;
    uint8_t m_data[32];

    bool m_czyt = false;
    bool m_pisz = false;
    bool m_wys = false;
    bool m_wes = false;
};