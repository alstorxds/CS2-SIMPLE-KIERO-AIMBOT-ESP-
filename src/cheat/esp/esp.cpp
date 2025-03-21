#include "esp.h"
#include "../config.h"
#include "../../core/Entity.h"
#include "../../core/math/math.h"
#include <imgui.h>

uintptr_t ESP::s_client = 0;
uintptr_t ESP::s_server = 0;
float(*ESP::s_viewMatrix)[4][4] = nullptr;

void ESP::Initialize(uintptr_t client, uintptr_t server) {
    s_client = client;
    s_server = server;
    s_viewMatrix = reinterpret_cast<float(*)[4][4]>(s_client + Offsets::dwViewMatrix);
}

void ESP::Render() {
    if (!Config::espEnabled) return;

    const auto players = Entity::GetPlayers(s_client, s_server);
    const auto localTeam = Entity::GetLocalTeam(s_client, s_server);
    ImDrawList* drawList = ImGui::GetBackgroundDrawList();

    for (const auto& player : players) {
        if (!Config::espShowTeammates && player.team == localTeam) continue;
        if (player.health <= 0) continue;

        Vec2 feet, head;
        if (player.feetPos.WorldToScreen(feet, s_viewMatrix) &&
            player.headPos.WorldToScreen(head, s_viewMatrix))
        {
            
            const float height = feet.y - head.y;
            const float width = height * 0.4f;
            const ImColor color = player.isSpotted
                ? Config::espVisibleColor
                : Config::espDefaultColor;

            
            drawList->AddRect(
                { head.x - width / 2, head.y },
                { head.x + width / 2, feet.y },
                color,
                0, 0,
                Config::espThickness
            );

            
            if (Config::healthBarEnabled) {
                
                const float barX = head.x - width / 2 - Config::healthBarWidth - 2;
                const float barY = head.y;
                const float barHeight = feet.y - head.y;

                
                const float healthPercent = static_cast<float>(player.health) / 100.0f;
                const float filledHeight = barHeight * healthPercent;

                
                ImColor barColor = Config::healthBarDynamicColor
                    ? ImColor(
                        static_cast<int>(255 * (1 - healthPercent)),
                        static_cast<int>(255 * healthPercent),
                        0,
                        255
                    )
                    : ImColor(0, 255, 0);

                
                drawList->AddRectFilled(
                    ImVec2(barX, barY),
                    ImVec2(barX + Config::healthBarWidth, barY + barHeight),
                    ImColor(50, 50, 50, 100)
                );

                
                drawList->AddRectFilled(
                    ImVec2(barX, barY + (barHeight - filledHeight)),
                    ImVec2(barX + Config::healthBarWidth, barY + barHeight),
                    barColor
                );
            }

        }
    }
}