
#pragma once

#include <cstdint>
#include <raylib.h>
#include "vec3.h"

namespace nbody {

class world;
class body {
public:

    body(const char *name, float radius, double mass, Color color) : radius(radius), mass(mass), color(color), name(name) {} 

    void update(world &W);
    void render();

    // start circular orbit around this body
    void encircle(body &other, double dist);

    vec3 pos { 0, 0, 0 };
    vec3 vel { 0, 0, 0 };

private:
    friend class world;

    float radius;
    Color color;
    double mass;
    uint64_t id;
    const char *name;
};

}

