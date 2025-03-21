#pragma once
#include "../config.h"
#include "../../core/Entity.h"
#include "../../core/math/math.h"

class ESP {
public:
    static void Initialize(uintptr_t client, uintptr_t server);
    static void Render();

private:
    static uintptr_t s_client;
    static uintptr_t s_server;
    static float(*s_viewMatrix)[4][4];
};