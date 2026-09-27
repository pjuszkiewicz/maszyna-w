#include "window/window.h"

Window::Window() {}

Window::~Window()
{
    Shutdown();
}

bool Window::Init()
{
    // GLFW init
    if (!glfwInit())
        return false;

    const char *glsl_version = "#version 130";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

    // Create window
    m_handle = glfwCreateWindow(1280, 720, "Maszyna W", nullptr, nullptr);
    if (m_handle == nullptr)
        return false;
    glfwMakeContextCurrent(m_handle);
    glfwSwapInterval(1); // VSync

    // ImGui init
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

    ImGui::StyleColorsDark(); // Styl okien

    // OpenGL init
    ImGui_ImplGlfw_InitForOpenGL(m_handle, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    return true;
}

bool Window::IsOpen()
{
    return glfwWindowShouldClose(m_handle);
}

void Window::BeginFrame()
{
    glfwPollEvents();

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void Window::EndFrame()
{
    ImGui::Render();
    int display_w, display_h;
    glfwGetFramebufferSize(m_handle, &display_w, &display_h);
    glViewport(0, 0, display_w, display_h);
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    glfwSwapBuffers(m_handle);
}

void Window::Shutdown()
{
    if (m_handle)
    {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
        glfwDestroyWindow(m_handle);
        glfwTerminate();
        m_handle = nullptr;
    }
}