#pragma once

#include "imgui.h"
#include <cstdint>
#include <vector>
#include <string>
#include "diagram/colors.h"
#include "diagram/canvas.h"

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
    ImVec2 DrawBlock(CpuBlock &block, int id);

    void DrawOption(ImVec2 pos, const std::string& name, bool isActive = false, bool isReverse = false);

    void Draw();
    void DrawALU();
    void DrawMemory();

    Canvas m_canvas;
};