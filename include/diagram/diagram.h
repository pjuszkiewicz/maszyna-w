#pragma once

#include "imgui.h"
#include <cstdint>
#include <vector>
#include <string>

struct CpuBlock
{
    std::string name;
    std::string short_name;
    uint32_t value;

    ImVec2 pos;
    ImVec2 size;
    bool isActive;
};

class Diagram
{
public:
    Diagram() = default;

    void Render();

private:
    void Update();

    ImVec2 DrawRect(ImVec2 pos, ImVec2 size);
    ImVec2 DrawBlock(CpuBlock &block, int id);
    void DrawOption(ImVec2 pos, const std::string& name);
    void DrawLine(ImVec2 a, ImVec2 b, bool isActive);

    void Draw();
    void DrawALU();

    ImDrawList *m_drawList;
    ImVec2 m_canvasPos;
    ImVec2 m_mousePos;
};