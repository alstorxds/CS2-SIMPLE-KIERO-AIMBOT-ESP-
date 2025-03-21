#pragma once
#include "math/math.h"
#include <cstddef>
#include <cstdint>
#include "imgui.h"

namespace Offsets {
    // offsets - used with client.dll
    inline constexpr std::ptrdiff_t dwEntityList = 0x1A38800;
    inline constexpr std::ptrdiff_t dwLocalPlayerPawn = 0x188CF70;
    inline constexpr std::ptrdiff_t dwViewMatrix = 0x1AA45F0;
    constexpr std::ptrdiff_t m_entitySpottedState = 0x23D0;
    
    constexpr std::ptrdiff_t m_sSanitizedPlayerName = 0x770;
    constexpr ptrdiff_t m_iszPlayerName = 0x660;
    // server.dll
    inline constexpr std::ptrdiff_t m_hPlayerPawn = 0x814;
    inline constexpr std::ptrdiff_t m_iHealth = 0x344;
    inline constexpr std::ptrdiff_t m_iTeamNum = 0x3E3;

    // client.dll
    inline constexpr std::ptrdiff_t m_vOldOrigin = 0x1324;
}