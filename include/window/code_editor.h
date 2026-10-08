#pragma once

#include "TextEditor.h"
#include "imgui.h"

class CodeEditor
{
public:
    CodeEditor() = default;

    void Init()
    {
        m_editor.SetPalette(TextEditor::GetLightPalette());
    }

    void SetFont(ImFont *font) { m_font = font; }

    void Render()
    {
        ImGui::Begin("Edytor kodu");

        if (m_font != nullptr)
            ImGui::PushFont(m_font);

        m_editor.Render("Editor");

        if (m_font != nullptr)
            ImGui::PopFont();

        ImGui::End();
    }

private:
    TextEditor m_editor;
    ImFont *m_font = nullptr;
};