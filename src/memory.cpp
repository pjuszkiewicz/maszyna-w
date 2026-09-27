#include "memory.h"

Memory::Memory()
{
    m_memory_editor.Open = true;
    m_memory_editor.ReadOnly = false;

    for (int i = 0; i < 31; i++)
    {
        m_data[i] = 0;
    }
}

int Memory::GetAddress()
{
    return m_address;
}

void Memory::SetAddress(int address)
{
    m_address = address;
}

uint8_t Memory::ReadData()
{
    return m_data[m_address];
}

void Memory::WriteData(uint8_t data)
{
    m_data[m_address] = data;
}

void Memory::Render()
{
    m_memory_editor.DrawWindow("Pamięć", m_data, sizeof(m_data));
}