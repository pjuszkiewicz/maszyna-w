#pragma once

#include <vector>
#include "imgui.h"

struct DaneOsoby
{
    int id;
    int data;
};

class MemoryEditor
{
public:
    MemoryEditor() = default;
    std::vector<DaneOsoby> tableData;
    void Init()
    {
    }
    void Render()
    {
        tableData = {};

        for (int i = 0; i < 64; i++)
        {
            tableData.push_back({i, i * 4});
        }

        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_CellPadding, ImVec2(6.0f, 4.0f));

        ImGui::Begin("Pamięć");

        ImGuiTableFlags flagi = ImGuiTableFlags_BordersInner | ImGuiTableFlags_RowBg | ImGuiTableFlags_Resizable | ImGuiTableFlags_PadOuterX;

        if (ImGui::BeginTable("TabelaOsob", 2, flagi, ImVec2(0.0f, 0.0f)))
        {
            ImGui::TableSetupScrollFreeze(0, 2);

            ImGui::TableSetupColumn("Adres");
            ImGui::TableSetupColumn("Wartość");

            ImGui::TableHeadersRow();

            ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0.0f, 0.0f));
            ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4(0, 0, 0, 0));
            ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, ImVec4(1, 1, 1, 0.05f));
            ImGui::PushStyleColor(ImGuiCol_FrameBgActive, ImVec4(1, 1, 1, 0.1f));

            for (int row = 0; row < tableData.size(); row++)
            {
                ImGui::PushID(row);
                ImGui::TableNextRow();

                ImGui::TableSetColumnIndex(0);
                ImGui::Text("%d", tableData[row].id);

                ImGui::TableSetColumnIndex(1);
                ImGui::InputInt("##data", &tableData[row].data, 0, 0, ImGuiInputTextFlags_NoHorizontalScroll);

                ImGui::PopID();
            }

            ImGui::PopStyleColor(3);
            ImGui::PopStyleVar();

            ImGui::EndTable();
        }

        ImGui::End();

        ImGui::PopStyleVar(4);
    }
};