#pragma once

#include "imgui.h"
#include <cstdint>
#include <vector>
#include <string>
#include "diagram/colors.h"

const float REGISTER_WIDTH = 128.0f;
const float REGISTER_HEIGHT = 24.0f;

class Canvas
{
public:
    Canvas() = default;

    void Update();

    ImVec2 DrawRect(ImVec2 pos, ImVec2 size);
    void DrawLine(ImVec2 a, ImVec2 b, bool isActive);
    void DrawText(ImVec2 pos, std::string text, ImU32 color = TEXT_COLOR);
    void DrawRegister(ImVec2 pos, std::string name, uint8_t value, float width = REGISTER_WIDTH);
    void DrawButton(ImVec2 pos, ImVec2 size, std::string text);

private:
    ImDrawList *m_drawList;
    ImVec2 m_canvasPos;
    ImVec2 m_mousePos;
};