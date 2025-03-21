#include "Entity.h"
#include <Windows.h>

std::vector<Entity::Player> Entity::GetPlayers(uintptr_t client, uintptr_t server) {
    std::vector<Player> players;
    const auto localPawn = *(uintptr_t*)(client + Offsets::dwLocalPlayerPawn);
    const auto entityList = *(uintptr_t*)(client + Offsets::dwEntityList);

    if (!entityList) return players;

    for (int i = 1; i < 64; i++) {
        const uintptr_t listEntry = *(uintptr_t*)(entityList + (8 * (i & 0x7FFF) >> 9) + 16);
        if (!listEntry) continue;

        const uintptr_t controller = *(uintptr_t*)(listEntry + 0x78 * (i & 0x1FF));
        if (!controller) continue;

        const uint32_t pawnHandle = *(uint32_t*)(controller + Offsets::m_hPlayerPawn);
        if (!pawnHandle) continue;

        const uintptr_t entityEntry = *(uintptr_t*)(entityList + 0x8 * ((pawnHandle & 0x7FFF) >> 9) + 16);
        if (!entityEntry) continue;

        const uintptr_t pawn = *(uintptr_t*)(entityEntry + 120 * (pawnHandle & 0x1FF));
        if (!pawn) continue;

        players.push_back(GetPlayerData(pawn, client, server));
    }
    return players;
}

Entity::Player Entity::GetPlayerData(uintptr_t entity, uintptr_t client, uintptr_t server) {
    Player player;
    player.pawnPtr = entity;
    player.feetPos = *(Vec3*)(entity + Offsets::m_vOldOrigin);
    player.headPos = { player.feetPos.x, player.feetPos.y, player.feetPos.z + 65.0f };
    player.health = *(int32_t*)(entity + Offsets::m_iHealth);
    player.team = *(uint8_t*)(entity + Offsets::m_iTeamNum);
    player.name = GetPlayerName(entity);
    player.isSpotted = IsPlayerSpotted(entity);
    return player;
}

std::string Entity::GetPlayerName(uintptr_t entity) {
    if (entity == 0) return "Invalid";

    
    const uintptr_t nameAddr = entity + Offsets::m_iszPlayerName;
    const std::string entityName = *reinterpret_cast<std::string*>(nameAddr);

    
    const char* charsEntityName = entityName.c_str();

    

    return entityName;
}

bool Entity::IsPlayerSpotted(uintptr_t entity) {
    const uintptr_t spottedState = entity + Offsets::m_entitySpottedState;
    if (!spottedState) return false;

    
    const bool isSpotted = *reinterpret_cast<bool*>(spottedState + 0x8);
    return isSpotted;
}

int Entity::GetLocalTeam(uintptr_t client, uintptr_t server) {
    const auto localPawn = *(uintptr_t*)(client + Offsets::dwLocalPlayerPawn);
    return (localPawn != 0) ? *(uint8_t*)(localPawn + Offsets::m_iTeamNum) : -1;
}