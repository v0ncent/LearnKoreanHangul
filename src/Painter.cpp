#include "Painter.h"

#include <chrono>
#include <imgui.h>
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
    ImGui::Begin("Game", open,
        ImGuiWindowFlags_NoTitleBar |
        ImGuiWindowFlags_NoResize |
        ImGuiWindowFlags_NoBackground |
        ImGuiWindowFlags_NoMove);

    // Allow the window to fill the screen so we can center content
    const ImGuiViewport* vp = ImGui::GetMainViewport();
    ImGui::SetWindowPos(vp->Pos);
    ImGui::SetWindowSize(vp->Size);

    if (shouldPrepareQuestion) {
        Util::prepareQuestion();
    }

    if (currentHangul.empty()) {
        const ImVec2 textSize = ImGui::CalcTextSize("No More Hanguls!");

        ImGui::SetCursorPos(ImVec2(
            (vp->Size.x - textSize.x) * 0.5f,
            (vp->Size.y - textSize.y) * 0.5f
        ));

        ImGui::Text("No More Hanguls!");

        ImGui::End();

        return;
    }

    const GLuint textureID = Util::createTextureFromImage(currentHangul.image);
    const std::string name = currentHangul.name;
    const std::string startPronunciation = currentHangul.startPronunciation;
    const std::string middlePronunciation = currentHangul.middlePronunciation;
    const std::string endPronunciation = currentHangul.endPronunciation;

    // -----------------------------------------------------------
    // Helper for coloring buttons
    // -----------------------------------------------------------
    auto applyAnswerColor = [](const bool wrong, const bool correct) {
        int pushes = 0;

        if (correct) {
            ImGui::PushStyleColor(ImGuiCol_Button,        ImVec4(0.1f, 0.7f, 0.1f, 1.0f));
            ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.2f, 0.8f, 0.2f, 1.0f));
            ImGui::PushStyleColor(ImGuiCol_ButtonActive,  ImVec4(0.0f, 0.6f, 0.0f, 1.0f));

            pushes = 3;

        } else if (wrong) {
            ImGui::PushStyleColor(ImGuiCol_Button,        ImVec4(0.8f, 0.1f, 0.1f, 1.0f));
            ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.9f, 0.2f, 0.2f, 1.0f));
            ImGui::PushStyleColor(ImGuiCol_ButtonActive,  ImVec4(1.0f, 0.0f, 0.0f, 1.0f));

            pushes = 3;
        }

        return pushes;
    };

    // -----------------------------------------------------------
    // Calculate vertical centering
    // -----------------------------------------------------------
    constexpr float imageHeight = 200.0f;
    constexpr float buttonHeight = 40.0f;
    constexpr int rows = 4;
    constexpr float headerHeight = 60.0f; // approx for "Name"/"Start" etc + separators
    const float spacingY = ImGui::GetStyle().ItemSpacing.y;
    const float totalHeight = imageHeight + 20.0f + (rows * buttonHeight) + (rows - 1) * spacingY + headerHeight;

    float yOffset = (vp->Size.y - totalHeight) * 0.5f;

    if (yOffset < 0) yOffset = 0;

    ImGui::SetCursorPosY(yOffset);

    // -----------------------------------------------------------
    // Image (centered)
    // -----------------------------------------------------------
    ImGui::SetCursorPosX((vp->Size.x - imageHeight) * 0.5f);

    ImGui::Image(textureID, ImVec2(imageHeight, imageHeight));

    ImGui::Dummy(ImVec2(0, 20));

    // -----------------------------------------------------------
    // Table Layout (4 columns)
    // -----------------------------------------------------------
    constexpr int numColumns = 4;
    constexpr float columnWidth = 200.0f;
    const float spacingX = ImGui::GetStyle().ItemSpacing.x;
    const float tableWidth = numColumns * columnWidth + (numColumns - 1) * spacingX;

    ImGui::SetCursorPosX((vp->Size.x - tableWidth) * 0.5f);

    if (ImGui::BeginTable("Questions", numColumns, ImGuiTableFlags_SizingFixedFit)) {

        // Header row
        ImGui::TableNextRow();
        ImGui::TableNextColumn(); ImGui::Text("Name");
        ImGui::TableNextColumn(); ImGui::Text("Start");
        ImGui::TableNextColumn(); ImGui::Text("Middle");
        ImGui::TableNextColumn(); ImGui::Text("End");

        // Button rows
        for (int row = 0; row < 4; row++) {
            ImGui::TableNextRow();

            // Name
            ImGui::TableNextColumn();

            int pushes = applyAnswerColor(wrongName[row], correctName[row]);

            std::string id = nameOptions[row] + "##name_" + std::to_string(row);

            if (ImGui::Button(id.c_str(), ImVec2(columnWidth, buttonHeight))) {

                if (nameOptions[row] == name) {
                    correctName[row] = true; nameAnswerd = true;
                }

                else wrongName[row] = true;
            }

            if (pushes) ImGui::PopStyleColor(pushes);

            // Start
            ImGui::TableNextColumn();

            pushes = applyAnswerColor(wrongStart[row], correctStart[row]);

            id = startPronunciationOptions[row] + "##start_" + std::to_string(row);

            if (ImGui::Button(id.c_str(), ImVec2(columnWidth, buttonHeight))) {

                if (startPronunciationOptions[row] == startPronunciation) {
                    correctStart[row] = true; startPronunciationAnswerd = true;
                }

                else wrongStart[row] = true;
            }

            if (pushes) ImGui::PopStyleColor(pushes);

            // Middle
            ImGui::TableNextColumn();

            pushes = applyAnswerColor(wrongMiddle[row], correctMiddle[row]);

            id = middlePronunciationOptions[row] + "##middle_" + std::to_string(row);

            if (ImGui::Button(id.c_str(), ImVec2(columnWidth, buttonHeight))) {

                if (middlePronunciationOptions[row] == middlePronunciation) {
                    correctMiddle[row] = true; middlePronunciationAnswerd = true;
                }

                else wrongMiddle[row] = true;
            }

            if (pushes) ImGui::PopStyleColor(pushes);

            // End
            ImGui::TableNextColumn();

            pushes = applyAnswerColor(wrongEnd[row], correctEnd[row]);

            id = endPronunciationsOptions[row] + "##end_" + std::to_string(row);

            if (ImGui::Button(id.c_str(), ImVec2(columnWidth, buttonHeight))) {

                if (endPronunciationsOptions[row] == endPronunciation) {
                    correctEnd[row] = true; endPronunciationAnswerd = true;
                }

                else wrongEnd[row] = true;
            }

            if (pushes) ImGui::PopStyleColor(pushes);

        }

        ImGui::EndTable();
    }

    // -----------------------------------------------------------
    // Next question logic
    // -----------------------------------------------------------
    if (nameAnswerd && startPronunciationAnswerd &&
        middlePronunciationAnswerd && endPronunciationAnswerd) {

        if (!timerRunning) {
            timerRunning = true;

            auto t = std::thread(Util::delay);

            Util::shownHangul++;

            t.detach();
        }

        if (!shouldProceed) {
            const ImVec2 textSize = ImGui::CalcTextSize("Correct!!!");

            ImGui::SetCursorPos(ImVec2(
                (vp->Size.x - textSize.x) * 0.5f,
                (vp->Size.y - textSize.y) * 0.5f
            ));

            ImGui::Text("Correct!!!");

            ImGui::End();

            return;
        }

        shouldPrepareQuestion = true;
    }

    ImGui::End();
}



