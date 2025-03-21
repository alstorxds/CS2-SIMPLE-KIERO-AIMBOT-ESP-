#pragma once
#include <vector>
#include <string>
#include "math/math.h"
#include "offsets.h"

class Entity {
public:
    struct Player {
        uintptr_t pawnPtr;
        Vec3 feetPos;
        Vec3 headPos;
        int health;
        int team;
        std::string name;
        bool isSpotted;
    };

    static std::vector<Player> GetPlayers(uintptr_t client, uintptr_t server);
    static int GetLocalTeam(uintptr_t client, uintptr_t server);

private:
    static Player GetPlayerData(uintptr_t entity, uintptr_t client, uintptr_t server);
    static std::string GetPlayerName(uintptr_t entity);
    static bool IsPlayerSpotted(uintptr_t entity);
};