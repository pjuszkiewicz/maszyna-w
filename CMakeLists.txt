cmake_minimum_required(VERSION 3.15)
project(MaszynaW CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenGL REQUIRED)

# ==========================================
# ZALEŻNOŚCI (GLFW)
# ==========================================
include(FetchContent)
FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG 3.3.9
)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(glfw)

# ==========================================
# PLIKI ŹRÓDŁOWE
# ==========================================
# ImGui
set(IMGUI_DIR ${CMAKE_CURRENT_SOURCE_DIR}/vendor/imgui)
set(IMGUI_SOURCES
    ${IMGUI_DIR}/imgui.cpp
    ${IMGUI_DIR}/imgui_demo.cpp
    ${IMGUI_DIR}/imgui_draw.cpp
    ${IMGUI_DIR}/imgui_tables.cpp
    ${IMGUI_DIR}/imgui_widgets.cpp
    ${IMGUI_DIR}/backends/imgui_impl_glfw.cpp
    ${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp
)

# ImGuiColorTextEdit
set(TEXT_EDITOR_SOURCES 
    ${CMAKE_CURRENT_SOURCE_DIR}/vendor/ImGuiColorTextEdit/TextEditor.cpp
)

# Pliki Twojej aplikacji
file(GLOB_RECURSE APP_SOURCES CONFIGURE_DEPENDS "src/*.cpp")


# ==========================================
# TWORZENIE CELU (PLIKU WYKONYWALNEGO)
# ==========================================
# Najpierw tworzymy target, łącząc wszystkie źródła
add_executable(${PROJECT_NAME} 
    ${APP_SOURCES} 
    ${IMGUI_SOURCES}
    ${TEXT_EDITOR_SOURCES}
)

# ==========================================
# KONFIGURACJA CELU (INCLUDE I BIBLIOTEKI)
# ==========================================
# Ścieżki nagłówkowe (zgrupowane w jednym miejscu)
target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${IMGUI_DIR}
    ${IMGUI_DIR}/backends
    ${CMAKE_CURRENT_SOURCE_DIR}/vendor/ImGuiColorTextEdit
)

# Linkowanie bibliotek
target_link_libraries(${PROJECT_NAME} PRIVATE 
    glfw 
    OpenGL::GL
)

# Kopiuje cały katalog assets do folderu, w którym powstaje plik wykonywalny
add_custom_command(
    TARGET MaszynaW POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${CMAKE_CURRENT_SOURCE_DIR}/assets"
            "$<TARGET_FILE_DIR:MaszynaW>/assets"
)