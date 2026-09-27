#include "diagram/diagram.h"

#include <iostream>
#include <string>

const ImU32 BUS_COLOR = IM_COL32(0, 0, 0, 255);
const ImU32 BUS_COLOR_ACTIVE = IM_COL32(255, 0, 0, 255);

const ImU32 BLOCK_BACKGROUND_COLOR = IM_COL32(255, 255, 255, 255);
const ImU32 BLOCK_BORDER_COLOR = IM_COL32(0, 0, 0, 255);

const ImU32 TEXT_COLOR = IM_COL32(0, 0, 0, 255);

static int selected_block = -1;

void Diagram::Update()
{
    m_drawList = ImGui::GetWindowDrawList();
    m_canvasPos = ImGui::GetCursorScreenPos();
    m_mousePos = ImGui::GetIO().MousePos;
}

void Diagram::Render()
{
    ImGui::Begin("Schemat");

    Update();
    Draw();

    ImGui::End();
}

void Diagram::DrawLine(ImVec2 a, ImVec2 b, bool isActive)
{
    ImU32 bus_color = isActive ? BUS_COLOR_ACTIVE : BUS_COLOR;

    m_drawList->AddLine(
        ImVec2(a.x, a.y),
        ImVec2(b.x, b.y),
        bus_color, 1.0f);
}

ImVec2 Diagram::DrawRect(ImVec2 pos, ImVec2 size)
{
    ImVec2 p_min = ImVec2(m_canvasPos.x + pos.x, m_canvasPos.y + pos.y);
    ImVec2 p_max = ImVec2(p_min.x + size.x, p_min.y + size.y);

    m_drawList->AddRectFilled(p_min, p_max, BLOCK_BACKGROUND_COLOR, 3.0f);
    m_drawList->AddRect(p_min, p_max, BLOCK_BORDER_COLOR, 3.0f, 0, 1.0f);

    return p_min;
}

void Diagram::DrawOption(ImVec2 pos, const std::string& name)
{
    m_drawList->AddText(pos, TEXT_COLOR, name.c_str());
    DrawLine(ImVec2(pos.x + 40, pos.y + 8), ImVec2(pos.x + 70, pos.y + 8), false);
}

void Diagram::DrawALU()
{
    ImVec2 pos = DrawRect(ImVec2(100, 100), ImVec2(150, 150));

    m_drawList->AddText(ImGui::GetFont(), 24.0f, ImVec2(pos.x + 10, pos.y + 10), TEXT_COLOR, "ALU");
    m_drawList->AddText(ImVec2(pos.x + 10, pos.y + 38), TEXT_COLOR, "Wartość: 255");

    DrawOption(ImVec2(pos.x - 70, pos.y + 64 + (20 * 0)), "weak");
    DrawOption(ImVec2(pos.x - 70, pos.y + 64 + (20 * 1)), "dod");
    DrawOption(ImVec2(pos.x - 70, pos.y + 64 + (20 * 2)), "ode");
    DrawOption(ImVec2(pos.x - 70, pos.y + 64 + (20 * 3)), "przep");
}

void Diagram::Draw()
{
    DrawALU();
}

ImVec2 Diagram::DrawBlock(CpuBlock &block, int id)
{
    ImVec2 p_min = ImVec2(m_canvasPos.x + block.pos.x, m_canvasPos.y + block.pos.y);
    ImVec2 p_max = ImVec2(p_min.x + block.size.x, p_min.y + block.size.y);

    // Wykrywanie najechania myszą (Hover) i kliknięcia
    bool is_hovered = (m_mousePos.x >= p_min.x && m_mousePos.x <= p_max.x &&
                       m_mousePos.y >= p_min.y && m_mousePos.y <= p_max.y);

    if (is_hovered && ImGui::IsMouseClicked(0))
    {
        selected_block = id;
    }

    // Dobór koloru obramowania i tła
    ImU32 bg_color = block.isActive ? IM_COL32(40, 80, 40, 255) : IM_COL32(50, 50, 50, 255);
    ImU32 border_color = IM_COL32(150, 150, 150, 255);

    if (selected_block == id)
    {
        border_color = IM_COL32(255, 255, 0, 255); // Żółty dla zaznaczenia
    }
    else if (is_hovered)
    {
        border_color = IM_COL32(255, 255, 255, 255); // Biały przy najechaniu
    }

    // Rysowanie prostokąta bloku
    m_drawList->AddRectFilled(p_min, p_max, bg_color, 6.0f);
    m_drawList->AddRect(p_min, p_max, border_color, 6.0f, 0, 2.0f);

    // Rysowanie etykiety i wartości
    std::string val_str = "HEX: 0x" + std::to_string(block.value);
    // m_drawList->AddText(ImVec2(p_min.x + 10, p_min.y + 10), IM_COL32(255, 255, 255, 255), block.name);
    // m_drawList->AddText(ImVec2(p_min.x + 10, p_min.y + 32), IM_COL32(180, 220, 180, 255), val_str.c_str());

    return p_min;
};