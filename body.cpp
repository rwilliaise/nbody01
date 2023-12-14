
#include "body.h"
#include "globals.h"
#include "world.h"
#include <cmath>
#include <cstdio>

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
    vec3 render_vel_pos = render_pos + vel * RENDER_SCALE * 1.0e5;
    DrawLine3D(render_pos.convert(), render_vel_pos.convert(), color);
    DrawSphere(render_pos.convert(), radius * RENDER_SCALE, color);
}

void body::encircle(body &other, double dist) {
    double F = (GRAVITY_CONST * other.mass * mass / (dist * dist));
    double a = F / mass;
    double v = std::sqrt(a * dist);
    vel = other.vel + vec3 { v, 0, 0 };
    pos = other.pos + vec3 { 0, 0, -dist };
    dbg_vec(other.pos);
    dbg_vec(pos);
}

}
