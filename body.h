
#pragma once

#include <cstdint>
#include <raylib.h>
#include "vec3.h"

namespace nbody {

class world;
class body {
public:

    body(float radius, double mass, Color color) : radius(radius), mass(mass), color(color) {} 

    void update(world &W);
    void render();

    // start circular orbit around this body
    void encircle(body &other, double dist);

    inline void set_pos(vec3 new_pos) {
        pos = new_pos;
    }

private:
    friend class world;

    float radius;
    Color color;
    double mass;
    uint64_t id;
    vec3 pos { 0, 0, 0 };
    vec3 vel { 0, 0, 0 };
};

}

