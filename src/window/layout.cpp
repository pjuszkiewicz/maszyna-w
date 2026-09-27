#include <iostream>
#include <string>

#include <GLFW/glfw3.h>

#include "app.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "imgui_internal.h"

#include "window/layout.h"

void Layout::Render()
{
    RenderMainMenuBar();
    RenderTopBar();
    RenderDockingContainer();
}

void Layout::RenderMainMenuBar()
{
    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("Plik"))
        {
            if (ImGui::MenuItem("Nowy projekt", "Ctrl+N"))
            {
            }
            if (ImGui::MenuItem("Otwórz...", "Ctrl+O"))
            {
            }
            if (ImGui::MenuItem("Zapisz", "Ctrl+S"))
            {
            }
            ImGui::Separator();
            if (ImGui::MenuItem("Wyjście", "Alt+F4"))
            {
            }
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Edycja"))
        {
            if (ImGui::MenuItem("Cofnij", "Ctrl+Z"))
            {
            }
            if (ImGui::MenuItem("Ponów", "Ctrl+Y"))
            {
            }
            if (ImGui::MenuItem("Resetuj stan procesora"))
            {
            }
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Widok"))
        {
            if (ImGui::MenuItem("Resetuj układ okien (Layout)"))
            {
                // Wymuszenie przebudowania węzłów w następnej klatce
                ImGuiID dockspace_id = ImGui::GetID("EngineDockSpace");
                ImGui::DockBuilderRemoveNode(dockspace_id);
            }
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Pomoc"))
        {
            if (ImGui::MenuItem("O programie Maszyna W"))
            {
            }
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }
}

void Layout::RenderDockingContainer()
{
    ImGuiViewport *viewport = ImGui::GetMainViewport();

    ImGuiID dockspace_id = ImGui::GetID("EngineDockSpace");

    if (!ImGui::DockBuilderGetNode(dockspace_id))
    {
        ImGui::DockBuilderRemoveNode(dockspace_id);
        ImGui::DockBuilderAddNode(dockspace_id, ImGuiDockNodeFlags_DockSpace);
        ImGui::DockBuilderSetNodeSize(dockspace_id, ImVec2(viewport->WorkSize.x, viewport->WorkSize.y - 38.0f));

        ImGuiID dock_id_right;
        ImGuiID dock_id_left_and_center;
        ImGui::DockBuilderSplitNode(dockspace_id, ImGuiDir_Right, 0.25f, &dock_id_right, &dock_id_left_and_center);

        ImGuiID dock_id_left;
        ImGuiID dock_id_center;
        ImGui::DockBuilderSplitNode(dock_id_left_and_center, ImGuiDir_Left, 0.25f, &dock_id_left, &dock_id_center);

        ImGui::DockBuilderDockWindow("Pliki projektu", dock_id_left);
        ImGui::DockBuilderDockWindow("Schemat Procesora", dock_id_center);
        ImGui::DockBuilderDockWindow("Inspektor Atrybutów", dock_id_right);

        ImGui::DockBuilderFinish(dockspace_id);
    }

    ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), ImGuiDockNodeFlags_None);
    ImGui::End();

    // -------------------------------------------------------------------
    // D. OKNA PODRZĘDNE
    // -------------------------------------------------------------------
    ImGui::Begin("Pliki projektu");
    ImGui::Text("Drzewo plików...");
    ImGui::End();

    // DrawCpuDiagram(); // Nazwa okna wewnątrz tej funkcji to "Schemat Procesora"

    ImGui::Begin("Inspektor Atrybutów");
    ImGui::Text("Atrybuty i parametry...");
    ImGui::End();
}

void Layout::RenderTopBar()
{
    ImGuiViewport *viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(viewport->WorkPos);
    ImGui::SetNextWindowSize(viewport->WorkSize);

    ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDocking;
    window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
    window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));

    ImGui::Begin("EngineDockSpaceWindow", nullptr, window_flags);
    ImGui::PopStyleVar(3);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(8.0f, 6.0f));
    ImGui::BeginChild("SimulationToolbar", ImVec2(0, 38.0f), false, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);

    ImGui::Button(" Play ");
    ImGui::SameLine();
    ImGui::Button(" Pause ");
    ImGui::SameLine();
    ImGui::Button(" Step ");
    ImGui::SameLine();
    ImGui::Button(" Stop ");

    ImGui::EndChild();
    ImGui::PopStyleVar();

    ImGui::Separator(); // Oddzielenie paska narzędzi od obszaru okien edytora
}