#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include <filesystem>

#include <stb_image.h>

#include "Constants.h"
#include "Painter.h"
#include "Util.h"

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

    // load hangul images
    Painter::hanguls = Util::loadHanguls();

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

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();

    // clean up on close
    for (int i = 0; i < Painter::hanguls.size(); ++i) {
        stbi_image_free(Painter::hanguls[i].image.data);
    }

    return 0;
}
