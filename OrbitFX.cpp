#include "OrbitFX.h"

OrbitFX::OrbitFX(float start, float s)
{
    value = start;
    target = start;
    speed = s;
}

void OrbitFX::set(float v)
{
    value = v;
    target = v;
}

void OrbitFX::to(float t)
{
    target = t;
}

void OrbitFX::update()
{
    value += (target - value) * speed;

    if (fabs(value - target) < 0.05f)
        value = target;
}

bool OrbitFX::finished() const
{
    return value == target;
}