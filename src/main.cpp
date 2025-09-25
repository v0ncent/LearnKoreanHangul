#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>
#include <iostream>

#include "Painter.h"

#define WINDOW_HEIGHT 1200
#define WINDOW_WIDTH 1200

#define WINDOW_TITLE "Learn Korean Hangul!"

GLFWwindow* init() {
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return nullptr;
    }

    GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, nullptr, nullptr);

    if (!window) {
        std::cerr << "Failed to open GLFW window" << std::endl;
        glfwTerminate();
        return nullptr;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // VSYNC

    IMGUI_CHECKVERSION();

    ImGui::CreateContext();

    ImGui::StyleColorsClassic();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 130");

    return window;
}

int main() {
    GLFWwindow* window = init();

    if (window == nullptr) {
        std::cerr << "Failed to initialize GLFW Window!" << std::endl;
        return -1;
    }

    Painter::shouldShowMenu(true);

    // run window loop
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        if (Painter::showMenu) {
            Painter::paintMainMenu(&Painter::showMenu);
        }

        if (Painter::showBackToMenu) {
            Painter::paintBackToMenu(&Painter::showBackToMenu);
        }

        if (Painter::showGame) {
            Painter::paintGame(&Painter::showGame);
        }

        ImGui::Render();

        int displayWidth, displayHeight;
        glfwGetFramebufferSize(window, &displayWidth, &displayHeight);
        glViewport(0, 0, displayWidth, displayHeight);

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }

    // clean up on close
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}