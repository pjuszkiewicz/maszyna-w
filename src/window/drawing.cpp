#include <iostream>
#include <string>

#include <GLFW/glfw3.h>

#include "app.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "imgui_internal.h"

struct CpuBlock
{
    int id;
    const char *name;
    ImVec2 pos;     // Pozycja w przestrzeni świata (World Space)
    ImVec2 size;    // Rozmiar bloku
    uint32_t value; // Wartość (np. rejestru)
    bool isActive;  // Czy blok jest aktywny w danym cyklu
};

void DrawCpuDiagram()
{
    ImGui::Begin("Główny Viewport");
    // 1. Stan canvasu i danych
    static ImVec2 scrolling = ImVec2(0.0f, 0.0f);
    static int selected_block_id = -1; // -1 = żaden blok nie jest zaznaczony

    static CpuBlock regA = {0, "Rejestr A (ACC)", ImVec2(50.0f, 50.0f), ImVec2(150.0f, 65.0f), 0x00FF, false};
    static CpuBlock regB = {1, "Rejestr B", ImVec2(50.0f, 150.0f), ImVec2(150.0f, 65.0f), 0x0012, false};
    static CpuBlock alu = {2, "Jednostka ALU", ImVec2(280.0f, 85.0f), ImVec2(170.0f, 95.0f), 0x0111, true};

    // 2. Pobranie obszaru canvasu
    ImVec2 canvas_p0 = ImGui::GetCursorScreenPos();
    ImVec2 canvas_sz = ImGui::GetContentRegionAvail();
    if (canvas_sz.x < 50.0f)
        canvas_sz.x = 50.0f;
    if (canvas_sz.y < 50.0f)
        canvas_sz.y = 50.0f;
    ImVec2 canvas_p1 = ImVec2(canvas_p0.x + canvas_sz.x, canvas_p0.y + canvas_sz.y - 120.0f); // Miejsce na panel atrybutów na dole

    ImDrawList *draw_list = ImGui::GetWindowDrawList();
    ImGuiIO &io = ImGui::GetIO();

    // Rysowanie tła canvasu
    draw_list->AddRectFilled(canvas_p0, canvas_p1, IM_COL32(30, 30, 35, 255));
    draw_list->AddRect(canvas_p0, canvas_p1, IM_COL32(70, 70, 80, 255));

    // 3. Niewidzialny przycisk przechwytujący mysz (tylko w obszarze canvasu)
    ImGui::SetCursorScreenPos(canvas_p0);
    ImGui::InvisibleButton("canvas_interactor", ImVec2(canvas_p1.x - canvas_p0.x, canvas_p1.y - canvas_p0.y),
                           ImGuiButtonFlags_MouseButtonLeft | ImGuiButtonFlags_MouseButtonRight | ImGuiButtonFlags_MouseButtonMiddle);

    const bool is_canvas_hovered = ImGui::IsItemHovered();
    const bool is_canvas_active = ImGui::IsItemActive();

    // Przesuwanie widoku (Pan) za pomocą PPM lub SPM
    if (is_canvas_active && (ImGui::IsMouseDragging(ImGuiMouseButton_Right, 0.0f) || ImGui::IsMouseDragging(ImGuiMouseButton_Middle, 0.0f)))
    {
        scrolling.x += io.MouseDelta.x;
        scrolling.y += io.MouseDelta.y;
    }

    // 4. Ograniczenie rysowania (ClipRect)
    draw_list->PushClipRect(canvas_p0, canvas_p1, true);

    // Rysowanie siatki tła
    const float GRID_SIZE = 64.0f;
    for (float x = fmodf(scrolling.x, GRID_SIZE); x < (canvas_p1.x - canvas_p0.x); x += GRID_SIZE)
        draw_list->AddLine(ImVec2(canvas_p0.x + x, canvas_p0.y), ImVec2(canvas_p0.x + x, canvas_p1.y), IM_COL32(200, 200, 200, 15));
    for (float y = fmodf(scrolling.y, GRID_SIZE); y < (canvas_p1.y - canvas_p0.y); y += GRID_SIZE)
        draw_list->AddLine(ImVec2(canvas_p0.x, canvas_p0.y + y), ImVec2(canvas_p1.x, canvas_p0.y + y), IM_COL32(200, 200, 200, 15));

    // Helper: Przeliczanie pozycji Świat -> Ekran
    auto WorldToScreen = [&](ImVec2 world_pos) -> ImVec2
    {
        return ImVec2(canvas_p0.x + scrolling.x + world_pos.x, canvas_p0.y + scrolling.y + world_pos.y);
    };

    // 5. Obsługa i rysowanie pojedynczego bloku CPU
    auto ProcessBlock = [&](CpuBlock &block)
    {
        ImVec2 p_min = WorldToScreen(block.pos);
        ImVec2 p_max = ImVec2(p_min.x + block.size.x, p_min.y + block.size.y);

        // Wykrywanie najechania i kliknięcia LPM w dany blok
        bool is_mouse_over = (io.MousePos.x >= p_min.x && io.MousePos.x <= p_max.x &&
                              io.MousePos.y >= p_min.y && io.MousePos.y <= p_max.y);

        if (is_canvas_hovered && is_mouse_over && ImGui::IsMouseClicked(ImGuiMouseButton_Left))
        {
            selected_block_id = block.id;
        }

        // Dobór kolorów
        ImU32 bg_color = block.isActive ? IM_COL32(35, 75, 45, 255) : IM_COL32(50, 50, 60, 255);
        ImU32 border_color = IM_COL32(140, 140, 150, 255);

        if (selected_block_id == block.id)
        {
            border_color = IM_COL32(255, 220, 0, 255); // Żółty ramka dla wybranego elementu
        }
        else if (is_canvas_hovered && is_mouse_over)
        {
            border_color = IM_COL32(255, 255, 255, 255); // Biała ramka po najechaniu
        }

        // Rysowanie bloku
        draw_list->AddRectFilled(p_min, p_max, bg_color, 6.0f);
        draw_list->AddRect(p_min, p_max, border_color, 6.0f, 0, (selected_block_id == block.id) ? 3.0f : 1.5f);

        // Rysowanie tekstów
        char val_buf[16];
        snprintf(val_buf, sizeof(val_buf), "VAL: 0x%04X", block.value);
        draw_list->AddText(ImVec2(p_min.x + 10, p_min.y + 10), IM_COL32(255, 255, 255, 255), block.name);
        draw_list->AddText(ImVec2(p_min.x + 10, p_min.y + 35), IM_COL32(180, 230, 180, 255), val_buf);

        return p_min;
    };

    // 6. Rysowanie elementów i magistrali (zależności przestrzenne)
    ImVec2 posA = ProcessBlock(regA);
    ImVec2 posB = ProcessBlock(regB);
    ImVec2 posALU = ProcessBlock(alu);

    // Linie magistrali
    ImU32 bus_color = alu.isActive ? IM_COL32(0, 255, 200, 255) : IM_COL32(90, 90, 100, 255);
    draw_list->AddLine(ImVec2(posA.x + regA.size.x, posA.y + regA.size.y / 2.0f), ImVec2(posALU.x, posALU.y + 30.0f), bus_color, 2.5f);
    draw_list->AddLine(ImVec2(posB.x + regB.size.x, posB.y + regB.size.y / 2.0f), ImVec2(posALU.x, posALU.y + alu.size.y - 30.0f), bus_color, 2.5f);

    draw_list->PopClipRect();

    // 7. Przycisk "Reset Pozycji" — umieszczony na górze canvasu, rysowany po nim
    ImGui::SetCursorScreenPos(ImVec2(canvas_p0.x + 10.0f, canvas_p0.y + 10.0f));
    if (ImGui::Button("Reset Pozycji Widoku"))
    {
        scrolling = ImVec2(0.0f, 0.0f);
    }

    // 8. Panel atrybutów na dole okna
    ImGui::SetCursorScreenPos(ImVec2(canvas_p0.x, canvas_p1.y + 10.0f));
    ImGui::Separator();
    ImGui::TextUnformatted("INSPEKTOR ATRYBUTÓW:");

    if (selected_block_id == 0)
    {
        ImGui::Text("Zaznaczono: %s", regA.name);
        ImGui::InputScalar("Wartość Rejestru A (HEX)", ImGuiDataType_U32, &regA.value, NULL, NULL, "%04X", ImGuiInputTextFlags_CharsHexadecimal);
        ImGui::Checkbox("Stan Aktywności", &regA.isActive);
    }
    else if (selected_block_id == 1)
    {
        ImGui::Text("Zaznaczono: %s", regB.name);
        ImGui::InputScalar("Wartość Rejestru B (HEX)", ImGuiDataType_U32, &regB.value, NULL, NULL, "%04X", ImGuiInputTextFlags_CharsHexadecimal);
        ImGui::Checkbox("Stan Aktywności", &regB.isActive);
    }
    else if (selected_block_id == 2)
    {
        ImGui::Text("Zaznaczono: %s", alu.name);
        ImGui::Text("Jednostka Arytmetyczno-Logiczna");
        ImGui::Checkbox("Zasymuluj cykl obliczeniowy (Aktywność)", &alu.isActive);
    }
    else
    {
        ImGui::TextColored(ImVec4(0.6f, 0.6f, 0.6f, 1.0f), "Kliknij lewym przyciskiem myszy na dowolny blok procesora, aby edytować jego parametry.");
    }

    ImGui::End();
}