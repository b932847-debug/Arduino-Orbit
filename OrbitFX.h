#pragma once

#include <Arduino.h>

class OrbitFX {

public:

    float value;
    float target;
    float speed;

    OrbitFX(float start = 0.0f, float s = 0.15f);

    void set(float v);

    void to(float t);

    void update();

    bool finished() const;

};