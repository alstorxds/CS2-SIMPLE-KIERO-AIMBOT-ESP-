#pragma once
#include <imgui.h>

namespace Config {
    // ESP
    inline bool espEnabled = true;
    inline bool espShowTeammates = false;
    inline float espThickness = 2.0f;
    inline ImColor espVisibleColor = ImColor(255, 0, 0);   // ������� ��� �������
    inline ImColor espDefaultColor = ImColor(150, 150, 150); // ����� ��� ���������
    inline bool healthBarEnabled = true;
    inline float healthBarWidth = 5.0f;   // ������ Health Bar
    inline float healthBarHeight = 30.0f; // ������ Health Bar (�����������)
    inline bool healthBarDynamicColor = true;

    // Aimbot
    inline bool aimbotEnabled = false;
    inline bool aimbotHeightCorrection = true; // �������� ����������� ��������
    inline float aimbotFOV = 150.0f;
    inline float aimbotSmoothness = 3.5f;
    inline bool drawFOV = true;
}