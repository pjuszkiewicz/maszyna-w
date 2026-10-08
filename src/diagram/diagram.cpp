#include "diagram/diagram.h"

#include <iostream>
#include <string>

void Diagram::DrawOption(ImVec2 pos, const std::string &name, bool isActive, bool isReverse)
{
    if (!isReverse)
    {
        m_canvas.DrawText(pos, name, isActive ? BUS_COLOR_ACTIVE : TEXT_COLOR);

        ImVec2 a(pos.x + 40, pos.y + 9);
        ImVec2 b(pos.x + 70, pos.y + 9);
        m_canvas.DrawLine(a, b, isActive);
    }
    else
    {
        m_canvas.DrawText(ImVec2(pos.x + 35, pos.y), name, isActive ? BUS_COLOR_ACTIVE : TEXT_COLOR);

        ImVec2 a(pos.x, pos.y + 9);
        ImVec2 b(pos.x + 30, pos.y + 9);
        m_canvas.DrawLine(a, b, isActive);
    }
}

void Diagram::Render()
{
    ImGui::Begin("Schemat");

    m_canvas.Update();
    Draw();

    ImGui::End();
}

void Diagram::DrawALU()
{
    ImVec2 pos = ImVec2(100, 100);
    m_canvas.DrawRect(pos, ImVec2(150, 150));

    m_canvas.DrawText(ImVec2(pos.x + 10, pos.y + 10), "ALU");
    m_canvas.DrawText(ImVec2(pos.x + 10, pos.y + 20), "Wartość: 255");

    DrawOption(ImVec2(pos.x - 70, pos.y + 64 + (20 * 0)), "weak");
    DrawOption(ImVec2(pos.x - 70, pos.y + 64 + (20 * 1)), "dod");
    DrawOption(ImVec2(pos.x - 70, pos.y + 64 + (20 * 2)), "ode");
    DrawOption(ImVec2(pos.x - 70, pos.y + 64 + (20 * 3)), "przep");
}

void Diagram::DrawMemory()
{
    ImVec2 pos = ImVec2(500, 100);
    m_canvas.DrawRect(pos, ImVec2(150, 150));

    m_canvas.DrawText(ImVec2(pos.x + 10, pos.y + 10), "Pamięć");
    m_canvas.DrawText(ImVec2(pos.x + 10, pos.y + 38), "Adres: 0");
    m_canvas.DrawText(ImVec2(pos.x + 10, pos.y + 38 + 16), "Wartość: 255");

    DrawOption(ImVec2(pos.x + 150, pos.y + 64 + (20 * 0)), "czyt", true, true);
    DrawOption(ImVec2(pos.x + 150, pos.y + 64 + (20 * 1)), "pisz", false, true);
}

void Diagram::Draw()
{
    ImVec2 buttonSize(REGISTER_WIDTH / 4, 20.0f);
    for (int i = 0; i < 4; i++)
    {
        ImVec2 buttonPos(8 + (buttonSize.x * i), 8);
        m_canvas.DrawButton(buttonPos, buttonSize, std::to_string(i + 1));
    }

    m_canvas.DrawRegister(ImVec2(8, 28), "RZ", 0);

    m_canvas.DrawRegister(ImVec2(170, 28), "RP", 0);

    m_canvas.DrawRegister(ImVec2(8, 64), "RM", 0);
    m_canvas.DrawRegister(ImVec2(170, 64), "AP", 0);

    // DrawALU();
    // DrawMemory();
}

// ImVec2 Diagram::DrawBlock(CpuBlock &block, int id)
// {
//     ImVec2 p_min = ImVec2(m_canvasPos.x + block.pos.x, m_canvasPos.y + block.pos.y);
//     ImVec2 p_max = ImVec2(p_min.x + block.size.x, p_min.y + block.size.y);

//     // Wykrywanie najechania myszą (Hover) i kliknięcia
//     bool is_hovered = (m_mousePos.x >= p_min.x && m_mousePos.x <= p_max.x &&
//                        m_mousePos.y >= p_min.y && m_mousePos.y <= p_max.y);

//     if (is_hovered && ImGui::IsMouseClicked(0))
//     {
//         selected_block = id;
//     }

//     // Dobór koloru obramowania i tła
//     ImU32 bg_color = block.isActive ? IM_COL32(40, 80, 40, 255) : IM_COL32(50, 50, 50, 255);
//     ImU32 border_color = IM_COL32(150, 150, 150, 255);

//     if (selected_block == id)
//     {
//         border_color = IM_COL32(255, 255, 0, 255); // Żółty dla zaznaczenia
//     }
//     else if (is_hovered)
//     {
//         border_color = IM_COL32(255, 255, 255, 255); // Biały przy najechaniu
//     }

//     // Rysowanie prostokąta bloku
//     m_drawList->AddRectFilled(p_min, p_max, bg_color, 6.0f);
//     m_drawList->AddRect(p_min, p_max, border_color, 6.0f, 0, 2.0f);

//     // Rysowanie etykiety i wartości
//     std::string val_str = "HEX: 0x" + std::to_string(block.value);
//     // m_drawList->AddText(ImVec2(p_min.x + 10, p_min.y + 10), IM_COL32(255, 255, 255, 255), block.name);
//     // m_drawList->AddText(ImVec2(p_min.x + 10, p_min.y + 32), IM_COL32(180, 220, 180, 255), val_str.c_str());

//     return p_min;
// };