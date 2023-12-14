
#include <cstdio>
#include <raylib.h>

#include "globals.h"
#include "world.h"
#include "body.h"

using namespace nbody;

int main(int argc, char *argv[]) {
    InitWindow(1024, 1024, "");

    world world;

    {
        body sun(SUN_RADIUS, SUN_MASS, YELLOW);
        body earth(EARTH_RADIUS, EARTH_MASS, BLUE);
        body moon(MOON_RADIUS, MOON_MASS, WHITE);
        earth.encircle(sun, EARTH_DIST);
        moon.encircle(earth, MOON_DIST);

        world.push(std::move(sun));
        world.push(std::move(earth));
        world.push(std::move(moon));
    }
    
    body *sun = world.from_id(0);
    body *earth = world.from_id(1);

    while (!WindowShouldClose()) {
        world.update();

        BeginDrawing();
            ClearBackground(BLACK);

            DrawGrid(100, SUN_RADIUS * RENDER_SCALE);

            vec3 diff = (earth->pos - sun->pos).normalized();

            BeginMode3D((Camera3D) {
                .position = (earth->pos * RENDER_SCALE + diff * 2 + vec3 { 0, 1, 0 }).convert(),
                // .target = vec_convert(vec_muls(world.bodies[1].pos, R_SCALE)),
                .target = (Vector3) { 0, 0, 0 },
                .up = (Vector3) { 0, 1, 0 },
                .fovy = 90,
                .projection = CAMERA_PERSPECTIVE,
            });

            world.render();

            EndMode3D();

        EndDrawing();
    }
    
    return 0;
}
