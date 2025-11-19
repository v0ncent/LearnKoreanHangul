#include "Painter.h"
#include <imgui.h>
#include <iostream>
#include <ostream>

#include "GLFW/glfw3.h"

void Painter::shouldShowMenu(const bool show) {
    showMenu = show;
}

void Painter::shouldShowBackToMenu(const bool show) {
    showBackToMenu = show;
}

void Painter::shouldPaintGame(const bool paint) {
    showGame = paint;
}

void Painter::paintBackToMenu(bool *open) {
    const ImGuiViewport* viewPort = ImGui::GetMainViewport();

    ImVec2 workPosistion = viewPort -> WorkPos;
    ImVec2 workSize = viewPort -> WorkSize;

    constexpr ImVec2 buttonSize = ImVec2(120, 100);
    ImGui::SetNextWindowPos(ImVec2(workPosistion.x + workSize.x - buttonSize.x - 10, workPosistion.y + 10));
    ImGui::SetNextWindowSize(buttonSize);

    constexpr ImGuiWindowFlags flags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove |
                         ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoBackground;

    ImGui::Begin("BackToMenu", open, flags);

    if (ImGui::Button("Back To Menu", buttonSize)) {
        shouldPaintGame(false);
        shouldShowBackToMenu(false);

        Util::resetGame();

        shouldShowMenu(true);
    }

    ImGui::End();
}


void Painter::paintMainMenu(bool* open) {
    const ImGuiViewport* viewPort = ImGui::GetMainViewport();

    const ImVec2 center = viewPort -> GetCenter();
    constexpr ImVec2 size = ImVec2(300, 200);

    ImGui::SetNextWindowPos(center, ImGuiCond_Always, ImVec2(0.5f, 0.5f));
    ImGui::SetNextWindowSize(size);

    // Window flags: no title bar, no resizing, no move, no collapse
    constexpr ImGuiWindowFlags flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize |
                                       ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse |
                                       ImGuiWindowFlags_NoBackground; // removes default imgui window background

    ImGui::Begin("Main Menu", open, flags);

    // font scaling and spacing
    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(20, 10));
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 20));

    // Custom colors
    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.2f, 0.4f, 0.7f, 1.0f));
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.3f, 0.6f, 1.0f, 1.0f));
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.1f, 0.3f, 0.5f, 1.0f));
    ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1, 1, 1, 1));

    ImGui::Text("Lets Learn Korean Hangul!");
    ImGui::Separator();

    if (ImGui::Button("Begin", ImVec2(200, 40))) {
        shouldShowMenu(false);

        Util::initGame();

        shouldShowBackToMenu(true);
        shouldPaintGame(true);
    }

    if (ImGui::Button("Quit", ImVec2(200, 40))) {
        glfwSetWindowShouldClose(glfwGetCurrentContext(), true);
    }

    // Restore styles
    ImGui::PopStyleColor(4);
    ImGui::PopStyleVar(2);

    ImGui::End();
}

void Painter::paintGame(bool *open) {
    ImGui::Begin("Game", open, ImGuiWindowFlags_NoTitleBar |
        ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_AlwaysAutoResize
        | ImGuiWindowFlags_NoMove);

    if (currentHangul.empty()) {
        ImGui::Text("No More Hanguls!");
        ImGui::End();

        return;
    }

    // the hangul image itself
    const GLuint textureID = Util::createTextureFromImage(currentHangul.image);

    const std::string name = currentHangul.name;
    const std::string startPronunciation = currentHangul.startPronunciation;
    const std::string middlePronunciation = currentHangul.middlePronunciation;
    const std::string endPronunciation = currentHangul.endPronunciation;

    if (textureID == 0) {
        std::cerr << "Failed to load texture: " << currentHangul.name << std::endl;
        return;
    }

    if (startPronunciation.empty()) {
        std::cerr << "Failed to load texture: " << currentHangul.name << std::endl;
        return;
    }

    if (startPronunciation.empty()) {
        std::cerr << "Failed to load texture: " << currentHangul.name << std::endl;
        return;
    }

    if (startPronunciation.empty()) {
        std::cerr << "Failed to load texture: " << currentHangul.name << std::endl;
        return;
    }

    // render hangul data
    currentHangul.shown = true;

    ImGui::Image(textureID, ImVec2(200, 200));
    ImGui::Separator();

    ImGui::Text("What is this Hangul's Name? ");
    ImGui::Separator();

    if (ImGui::Button(randomNames[0].c_str(), ImVec2(200, 40))) {

    }

    if (ImGui::Button(randomNames[1].c_str(), ImVec2(200, 40))) {

    }

    if (ImGui::Button(randomNames[2].c_str(), ImVec2(200, 40))) {

    }

    ImGui::Text("Name: %s", name.c_str());
    ImGui::Separator();

    ImGui::Text("Start Pronunciation: %s", startPronunciation.c_str());
    ImGui::Separator();

    ImGui::Text("Middle Pronunciation: %s", middlePronunciation.c_str());
    ImGui::Separator();

    ImGui::Text("End Pronunciation: %s", endPronunciation.c_str());
    ImGui::Separator();

    ImGui::End();
}


