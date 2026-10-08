#include <iostream>

#include "app.h"
#include "imgui.h"

bool App::Init()
{
    if (!m_window.Init())
    {
        std::cerr << "Couldn't  create the window" << std::endl;
        return false;
    }

    ImFont* editorFont = m_window.GetEditorFont();
    m_codeEditor.SetFont(editorFont);

    return true;
}

void App::Run()
{
    while(!m_window.IsOpen()) {
        m_window.BeginFrame();

        Render();

        m_window.EndFrame();
    }

    m_window.Shutdown();
}

void App::Render() {
    m_layout.Render();
    m_diagram.Render();
    m_codeEditor.Render();
    m_memoryEditor.Render();
}