#pragma once
#include "../config.h"
#include "../../core/Entity.h"

class Aimbot {
public:
    static void Run(uintptr_t client, uintptr_t server); // Объявление с параметрами

private:
    static Vec2 FindClosestTarget(
        const std::vector<Entity::Player>& players,
        float(*viewMatrix)[4][4],
        uintptr_t client,
        uintptr_t server
    );
};