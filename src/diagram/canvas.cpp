#include "diagram/canvas.h"

void Canvas::Update()
{
    m_drawList = ImGui::GetWindowDrawList();
    m_canvasPos = ImGui::GetCursorScreenPos();
    m_mousePos = ImGui::GetIO().MousePos;
}

ImVec2 Canvas::DrawRect(ImVec2 pos, ImVec2 size)
{
    ImVec2 p_min = ImVec2(m_canvasPos.x + pos.x, m_canvasPos.y + pos.y);
    ImVec2 p_max = ImVec2(p_min.x + size.x, p_min.y + size.y);

    m_drawList->AddRectFilled(p_min, p_max, BLOCK_BACKGROUND_COLOR, 3.0f);
    m_drawList->AddRect(p_min, p_max, BLOCK_BORDER_COLOR, 0.0f, 0, 1.0f);

    return p_min;
}

void Canvas::DrawLine(ImVec2 a, ImVec2 b, bool isActive)
{
    ImU32 bus_color = isActive ? BUS_COLOR_ACTIVE : BUS_COLOR;

    m_drawList->AddLine(
        ImVec2(m_canvasPos.x + a.x, m_canvasPos.y + a.y),
        ImVec2(m_canvasPos.x + b.x, m_canvasPos.y + b.y),
        bus_color, 1.0f);
}

void Canvas::DrawText(ImVec2 pos, std::string text, ImU32 color)
{
    ImVec2 newPos(m_canvasPos.x + pos.x, m_canvasPos.y + pos.y);
    m_drawList->AddText(newPos, color, text.c_str());
}

void Canvas::DrawButton(ImVec2 pos, ImVec2 size, std::string text)
{
    DrawRect(pos, size);

    ImVec2 textSize = ImGui::CalcTextSize(text.c_str());
    float posX = pos.x + (size.x / 2) - (textSize.x / 2);
    float posY = pos.y + (size.y / 2) - (textSize.y / 2);
    DrawText(ImVec2(posX, posY), text);
}

void Canvas::DrawRegister(ImVec2 pos, std::string name, uint8_t value, float width)
{
    DrawRect(pos, ImVec2(width, REGISTER_HEIGHT));

    std::string text = name + " : " + std::to_string(value);
    ImVec2 textSize = ImGui::CalcTextSize(text.c_str());
    float posX = pos.x + (width / 2) - (textSize.x / 2);
    float posY = pos.y + (REGISTER_HEIGHT / 2) - (textSize.y / 2);
    DrawText(ImVec2(posX, posY), text);
}