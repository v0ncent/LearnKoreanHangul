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

void Painter::shouldShowOptions(const bool show) {
    showOptions = show;
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

    if (shouldPrepareQuestion) {
        Util::prepareQuestion();
    }

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

    ImGui::Image(textureID, ImVec2(200, 200));
    ImGui::Separator();

    // Start a new horizontal group
    ImGui::BeginGroup();
    ImGui::Text("What is this Hangul's Name?");
    ImGui::Separator();

    for (int i = 0; i < 4; i++) {
        if (i > 0) ImGui::Separator(); // put buttons on the same row

        if (ImGui::Button(nameOptions[i].c_str(), ImVec2(200, 40))) {

            if (nameOptions[i] == currentHangul.name) {
                nameAnswerd = true;

                std::printf("cock1");

            } else {
                // make button appear red
            }

        }
    }

    ImGui::EndGroup();

    // Add horizontal spacing between groups
    ImGui::SameLine();
    ImGui::Dummy(ImVec2(50, 0)); // 50 pixels of empty horizontal space
    ImGui::SameLine();

    ImGui::BeginGroup();
    ImGui::Text("What is this Hangul's Start Pronunciation?");
    ImGui::Separator();

    for (int i = 0; i < 4; i++) {
        if (i > 0) ImGui::Separator(); // put buttons on the same row

        if (ImGui::Button(startPronunciationOptions[i].c_str(), ImVec2(200, 40))) {

            if (startPronunciationOptions[i] == currentHangul.startPronunciation) {
                startPronunciationAnswerd = true;

                std::printf("cock2");

            } else {
                // make button appear red
            }

        }
    }

    ImGui::EndGroup();

    ImGui::BeginGroup();
    ImGui::Text("What is this Hangul's Middle Pronunciation?");
    ImGui::Separator();

    for (int i = 0; i < 4; i++) {
        if (i > 0) ImGui::Separator(); // put buttons on the same row

        if (ImGui::Button(middlePronunciationOptions[i].c_str(), ImVec2(200, 40))) {

            if (middlePronunciationOptions[i] == currentHangul.middlePronunciation) {
                middlePronunciationAnswerd = true;

                std::printf("cock3");
            } else {
                // make button appear red
            }

        }
    }

    ImGui::EndGroup();

    // Add horizontal spacing between groups
    ImGui::SameLine();
    ImGui::Dummy(ImVec2(50, 0)); // 50 pixels of empty horizontal space
    ImGui::SameLine();

    ImGui::BeginGroup();
    ImGui::Text("What is this Hangul's End Pronunciation?");
    ImGui::Separator();

    for (int i = 0; i < 4; i++) {
        if (i > 0) ImGui::Separator(); // put buttons on the same row

        if (ImGui::Button(endPronunciationsOptions[i].c_str(), ImVec2(200, 40))) {

            if (endPronunciationsOptions[i] == currentHangul.endPronunciation) {
                endPronunciationAnswerd = true;

                std::printf("cock4");
            } else {
                // make button appear red
            }

        }
    }

    ImGui::EndGroup();

    ImGui::Separator();

    ImGui::BeginGroup();

    // if the questions have been answered successfully
    if (nameAnswerd && startPronunciationAnswerd && middlePronunciationAnswerd && endPronunciationAnswerd) {
        std::printf("YAY UR DONE!");
    }

    ImGui::EndGroup();

    ImGui::End();
}


