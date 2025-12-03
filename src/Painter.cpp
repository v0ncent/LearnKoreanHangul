#include "Painter.h"

#include <chrono>
#include <imgui.h>
#include <iostream>
#include <thread>

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
        ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoBackground |
        ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoMove);

    if (shouldPrepareQuestion) {
        Util::prepareQuestion();
    }

    if (currentHangul.empty()) {
        ImGui::Text("No More Hanguls!");
        ImGui::End();
        return;
    }

    const GLuint textureID = Util::createTextureFromImage(currentHangul.image);

    const std::string name = currentHangul.name;
    const std::string startPronunciation = currentHangul.startPronunciation;
    const std::string middlePronunciation = currentHangul.middlePronunciation;
    const std::string endPronunciation = currentHangul.endPronunciation;

    ImGui::Image(textureID, ImVec2(200, 200));
    ImGui::Separator();

    // ----------------------------------------------------------
    auto applyAnswerColor = [](const bool wrong, const bool correct) -> int {
        int pushes = 0;

        if (correct) {
            ImGui::PushStyleColor(ImGuiCol_Button,        ImVec4(0.1f, 0.7f, 0.1f, 1.0f));
            ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.2f, 0.8f, 0.2f, 1.0f));
            ImGui::PushStyleColor(ImGuiCol_ButtonActive,  ImVec4(0.0f, 0.6f, 0.0f, 1.0f));
            pushes = 3;
        }
        else if (wrong) {
            ImGui::PushStyleColor(ImGuiCol_Button,        ImVec4(0.8f, 0.1f, 0.1f, 1.0f));
            ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.9f, 0.2f, 0.2f, 1.0f));
            ImGui::PushStyleColor(ImGuiCol_ButtonActive,  ImVec4(1.0f, 0.0f, 0.0f, 1.0f));
            pushes = 3;
        }

        return pushes;
    };
    // ----------------------------------------------------------

    // ---------------------- NAME BUTTONS ----------------------
    ImGui::BeginGroup();
    ImGui::Text("What is this Hangul's Name?");
    ImGui::Separator();

    for (int i = 0; i < 4; i++) {

        if (i > 0) ImGui::Separator();

        int pushes = applyAnswerColor(wrongName[i], correctName[i]);

        std::string id = nameOptions[i] + "##name_" + std::to_string(i);
        if (ImGui::Button(id.c_str(), ImVec2(200, 40))) {

            if (nameOptions[i] == name) {
                correctName[i] = true;
                nameAnswerd = true;
            } else {
                wrongName[i] = true;
            }
        }

        if (pushes > 0) ImGui::PopStyleColor(pushes);
    }
    ImGui::EndGroup();

    ImGui::SameLine();
    ImGui::Dummy(ImVec2(50, 0));
    ImGui::SameLine();

    // ---------------------- START BUTTONS ----------------------
    ImGui::BeginGroup();
    ImGui::Text("What is this Hangul's Start Pronunciation?");
    ImGui::Separator();

    for (int i = 0; i < 4; i++) {

        if (i > 0) ImGui::Separator();

        int pushes = applyAnswerColor(wrongStart[i], correctStart[i]);

        std::string id = startPronunciationOptions[i] + "##start_" + std::to_string(i);
        if (ImGui::Button(id.c_str(), ImVec2(200, 40))) {

            if (startPronunciationOptions[i] == startPronunciation) {
                correctStart[i] = true;
                startPronunciationAnswerd = true;
            } else {
                wrongStart[i] = true;
            }
        }

        if (pushes > 0) ImGui::PopStyleColor(pushes);
    }
    ImGui::EndGroup();

    // ---------------------- MIDDLE BUTTONS ----------------------
    ImGui::BeginGroup();
    ImGui::Text("What is this Hangul's Middle Pronunciation?");
    ImGui::Separator();

    for (int i = 0; i < 4; i++) {

        if (i > 0) ImGui::Separator();

        int pushes = applyAnswerColor(wrongMiddle[i], correctMiddle[i]);

        std::string id = middlePronunciationOptions[i] + "##middle_" + std::to_string(i);
        if (ImGui::Button(id.c_str(), ImVec2(200, 40))) {

            if (middlePronunciationOptions[i] == middlePronunciation) {
                correctMiddle[i] = true;
                middlePronunciationAnswerd = true;
            } else {
                wrongMiddle[i] = true;
            }
        }

        if (pushes > 0) ImGui::PopStyleColor(pushes);
    }
    ImGui::EndGroup();

    ImGui::SameLine();
    ImGui::Dummy(ImVec2(50, 0));
    ImGui::SameLine();

    // ---------------------- END BUTTONS ----------------------
    ImGui::BeginGroup();
    ImGui::Text("What is this Hangul's End Pronunciation?");
    ImGui::Separator();

    for (int i = 0; i < 4; i++) {

        if (i > 0) ImGui::Separator();

        int pushes = applyAnswerColor(wrongEnd[i], correctEnd[i]);

        std::string id = endPronunciationsOptions[i] + "##end_" + std::to_string(i);
        if (ImGui::Button(id.c_str(), ImVec2(200, 40))) {

            if (endPronunciationsOptions[i] == endPronunciation) {
                correctEnd[i] = true;
                endPronunciationAnswerd = true;
            } else {
                wrongEnd[i] = true;
            }
        }

        if (pushes > 0) ImGui::PopStyleColor(pushes);
    }

    ImGui::EndGroup();

    // When all 4 categories are correct → next question
    if (nameAnswerd && startPronunciationAnswerd &&
        middlePronunciationAnswerd && endPronunciationAnswerd) {

        if (!timerRunning) {
            timerRunning = true;

            auto t = std::thread(Util::delay);

            // increase the number of shown hangul when we start timer so we only increment this up upon successful answer
            // and not while imgui is rendering
            Util::shownHangul++;

            t.detach();
        }

        if (!shouldProceed) {
            ImGui::Text("Correct!!!");

            ImGui::End();
            return;
        }

        shouldPrepareQuestion = true;
    }

    ImGui::End();
}

