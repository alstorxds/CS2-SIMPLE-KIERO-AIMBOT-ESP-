#include "visuals.h"
#include <imgui.h>
#include <Windows.h>

bool menu = false;

void Visuals::RenderMenu() {
    if (GetAsyncKeyState(VK_INSERT) & 1)
    {
        menu = !menu;
    }

    if (menu)
    {
        ImGui::Begin("DAYN CHEATER");

        ImGui::BeginTabBar("MainTabs");

        if (ImGui::BeginTabItem("ESP")) {
            ImGui::Checkbox("Enable ESP", &Config::espEnabled);
            ImGui::Checkbox("Show Teammates", &Config::espShowTeammates);
            ImGui::SliderFloat("Thickness", &Config::espThickness, 1.0f, 5.0f);
            ImGui::ColorEdit4("Visible Color", (float*)&Config::espVisibleColor);
            ImGui::ColorEdit4("Default Color", (float*)&Config::espDefaultColor);
            ImGui::Separator();
            ImGui::Checkbox("Enable Health Bar", &Config::healthBarEnabled);
            ImGui::SliderFloat("Health Bar Width", &Config::healthBarWidth, 2.0f, 10.0f);
            ImGui::Checkbox("Dynamic Color", &Config::healthBarDynamicColor);
            ImGui::EndTabItem();
        }

        if (ImGui::BeginTabItem("Aimbot")) {
            ImGui::Checkbox("Enable Aimbot", &Config::aimbotEnabled);
            ImGui::SliderFloat("FOV", &Config::aimbotFOV, 50.0f, 500.0f);
            ImGui::SliderFloat("Smoothness", &Config::aimbotSmoothness, 1.0f, 10.0f);
            ImGui::Checkbox("Height Correction", &Config::aimbotHeightCorrection);
            ImGui::EndTabItem();
        }

        ImGui::EndTabBar();
        ImGui::End();

    }
}
void Visuals::RenderFOV() {
    if (!Config::aimbotEnabled || !Config::drawFOV) return;

    ImDrawList* drawList = ImGui::GetBackgroundDrawList();
    const ImVec2 center(
        ImGui::GetIO().DisplaySize.x / 2,
        ImGui::GetIO().DisplaySize.y / 2
    );
    drawList->AddCircle(center, Config::aimbotFOV, ImColor(255, 255, 255, 80), 64, 1.5f);
}