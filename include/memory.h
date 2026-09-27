#pragma once

#include "imgui.h"
#include "imgui_memory_editor.h"

class Memory
{
public:
    Memory();
    void Render();
    int GetAddress();
    void SetAddress(int address);
    uint8_t ReadData();
    void WriteData(uint8_t data);

private:
    MemoryEditor m_memory_editor;
    uint8_t m_data[32];

    int m_address = 0;
};