#pragma once

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <GLFW/glfw3.h>

struct GLFWwindow;

class Window
{
public:
    Window();
    ~Window();

    bool Init();
    void LoadFonts();
    void Shutdown();

    bool IsOpen();
    void BeginFrame();
    void EndFrame();

    void ApplyTheme();

    GLFWwindow *m_handle = nullptr;
};
