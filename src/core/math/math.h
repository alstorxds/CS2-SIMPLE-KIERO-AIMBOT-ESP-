#pragma once
#include <Windows.h>

struct Vec2 {
    float x, y;
    Vec2(float x = 0, float y = 0) : x(x), y(y) {}
    bool IsZero() const { return x == 0 && y == 0; }
};

struct Vec3 {
    float x, y, z;
    Vec3(float x = 0, float y = 0, float z = 0) : x(x), y(y), z(z) {}
    bool WorldToScreen(Vec2& out, float(*viewMatrix)[4][4]) const;
};