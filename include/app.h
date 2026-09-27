#pragma once

#include "window/window.h"
#include "window/layout.h"
#include "diagram/diagram.h"
#include "cpu/cpu.h"

class App
{
public:
    App() = default;

    bool Init();
    void Run();

    void Render();

private:
    Window m_window;
    Layout m_layout;
    Diagram m_diagram;
    CPU m_cpu;
};
