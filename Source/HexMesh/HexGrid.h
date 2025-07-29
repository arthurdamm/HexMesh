#pragma once
#include "CoreMinimal.h"

namespace HexGrid
{
    constexpr float HEX_RADIUS = 1001.f;    // dist from center to corner
    constexpr float HEX_WIDTH = HEX_RADIUS * 2.f;
    const float HEX_HEIGHT = FMath::Sqrt(3.f) * HEX_RADIUS;

    constexpr int GRID_RADIUS = 1;

    inline FVector AxialToWorld(int32 Q, int32 R)
    {
        float X = HEX_RADIUS * 3.f / 2.f * Q;
        float Y = HEX_RADIUS * FMath::Sqrt(3.f) * (R + Q / 2.f);
        return FVector(X, Y, 0.f);
    }
}