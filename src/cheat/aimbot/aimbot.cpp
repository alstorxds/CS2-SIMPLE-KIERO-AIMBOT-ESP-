#include "aimbot.h"
#include "../visuals/visuals.h"
#include <thread>
#include <Windows.h>

// Реализация с параметрами client и server
void Aimbot::Run(uintptr_t client, uintptr_t server) {
    while (true) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
        if (!Config::aimbotEnabled) continue;

        const auto players = Entity::GetPlayers(client, server);
        const auto viewMatrix = reinterpret_cast<float(*)[4][4]>(client + Offsets::dwViewMatrix);
        const Vec2 target = FindClosestTarget(players, viewMatrix, client, server);

        if (!target.IsZero()) {
            const Vec2 center(
                static_cast<float>(GetSystemMetrics(SM_CXSCREEN)) / 2.0f,
                static_cast<float>(GetSystemMetrics(SM_CYSCREEN)) / 2.0f
            );

            // Явное вычисление delta для Vec2
            const Vec2 delta = {
                (target.x - center.x) / Config::aimbotSmoothness,
                (target.y - center.y) / Config::aimbotSmoothness
            };

            mouse_event(MOUSEEVENTF_MOVE,
                static_cast<DWORD>(delta.x),
                static_cast<DWORD>(delta.y), 0, 0);
        }
    }
}


Vec2 Aimbot::FindClosestTarget(const std::vector<Entity::Player>& players, float(*viewMatrix)[4][4], uintptr_t client, uintptr_t server) {
    Vec2 closest{};
    float minDist = Config::aimbotFOV * Config::aimbotFOV;
    const Vec2 center(GetSystemMetrics(SM_CXSCREEN) / 2, GetSystemMetrics(SM_CYSCREEN) / 2);
    const int localTeam = Entity::GetLocalTeam(client, server);

    for (const auto& player : players) {
        // Пропустить союзников, мёртвых и невидимых
        if (player.team == localTeam || player.health <= 0 || !player.isSpotted)
            continue;

        Vec2 screenPos;
        if (player.headPos.WorldToScreen(screenPos, viewMatrix)) {
            const float dx = screenPos.x - center.x;
            const float dy = screenPos.y - center.y;
            const float dist = dx * dx + dy * dy;

            

            if (dist < minDist) {
                minDist = dist;
                closest = screenPos;
            }
        }
    }
    return closest;
}