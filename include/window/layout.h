#pragma once

class Layout{
public:
    Layout() = default;

    void Render();
    void RenderMainMenuBar();
    void RenderDockingContainer();
    void RenderTopBar();
};