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
}