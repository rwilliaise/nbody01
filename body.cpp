
#include "body.h"
#include "globals.h"
#include "world.h"
#include <cmath>
#include <cstdio>
#include <raylib.h>

#define dbgf(A) printf(#A ": %f\n", A);

namespace nbody {

void body::update(world &W) {
    vec3 F_net;
    for (body &other : W.bodies) {
        if (other.id == id) continue;
        vec3 diff = other.pos - pos;
        double dist = diff.length();
        // G * (M1 * M2) / r^2
        F_net += (diff / dist) * (GRAVITY_CONST * other.mass * mass / (dist * dist));
    }

    vel += F_net * W.delta / mass;
    pos += vel * W.delta;
}

void body::render() {
    vec3 render_pos = pos * RENDER_SCALE;
    DrawSphere(render_pos.convert(), radius * RENDER_SCALE, color);
    // DrawPoint3D(render_pos.convert(), color);
}

void body::encircle(body &other, double dist) {
    double F = (GRAVITY_CONST * other.mass * mass / (dist * dist));
    double a = F / mass;
    double v = std::sqrt(a * dist);
    vel = other.vel + vec3 { v, 0, 0 };
    pos = other.pos + vec3 { 0, 0, -dist };

    double w = std::sqrt(a / dist);
    double T = (2 * M_PI) / w;

    printf("expected %s period: %f s\n", name, T);
    printf("expected %s velocity: %f m/s\n", name, v);
}

}
