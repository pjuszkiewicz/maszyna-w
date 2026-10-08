#pragma once

#include "window/window.h"
#include "window/layout.h"
#include "diagram/diagram.h"
#include "cpu/cpu.h"
#include "window/code_editor.h"
#include "window/memory_editor.h"

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
    CodeEditor m_codeEditor;
    MemoryEditor m_memoryEditor;

    CPU m_cpu;
};
