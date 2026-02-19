cmake_minimum_required(VERSION 3.30)
project(LearnKoreanHangul)

set(CMAKE_CXX_STANDARD 20)

# Statically link everything on Windows
if(WIN32)
    set(CMAKE_EXE_LINKER_FLAGS "-static")
endif()

# Add GLFW from submodule
add_subdirectory(lib/glfw)

# Add ImGui sources
add_library(imgui STATIC
        lib/imgui/imgui.cpp
        lib/imgui/imgui_draw.cpp
        lib/imgui/imgui_widgets.cpp
        lib/imgui/imgui_tables.cpp
        lib/imgui/imgui_demo.cpp
        lib/imgui/backends/imgui_impl_glfw.cpp
        lib/imgui/backends/imgui_impl_opengl3.cpp
)

target_include_directories(imgui PUBLIC
        lib/imgui
        lib/imgui/backends
)

target_link_libraries(imgui PUBLIC glfw)

# Main executable
add_executable(LearnKoreanHangul
        src/Main.cpp
        src/Painter.cpp
        src/Painter.h
        src/Util.cpp
        src/util.h
        src/Constants.h
)

# Link against GLFW, OpenGL, and ImGui
target_link_libraries(LearnKoreanHangul PRIVATE
        glfw
        imgui
        opengl32   # for Windows
)

# Add stb include path (header-only)
target_include_directories(LearnKoreanHangul PRIVATE
        ${CMAKE_SOURCE_DIR}/lib/stb
)

# Copy hangul assets to build directory
add_custom_command(TARGET LearnKoreanHangul POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/hangul
        $<TARGET_FILE_DIR:LearnKoreanHangul>/hangul
)
