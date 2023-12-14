
#include <raylib.h>

#include "globals.h"
#include "world.h"
#include "body.h"

using namespace nbody;

int main(int argc, char *argv[]) {
    InitWindow(1024, 1024, "");

    world world;

    {
        body earth(EARTH_RADIUS, EARTH_MASS, BLUE);
        body moon(MOON_RADIUS, MOON_MASS, WHITE);
        moon.encircle(earth, MOON_DIST);
        world.push(std::move(earth));
        world.push(std::move(moon));
    }

    while (!WindowShouldClose()) {
        world.update();

        BeginDrawing();
            ClearBackground(BLACK);

            BeginMode3D((Camera3D) {
                .position = (Vector3) { 0, 20, 1 },
                // .target = vec_convert(vec_muls(world.bodies[1].pos, R_SCALE)),
                .target = (Vector3) { 0, 0, 0 },
                .up = (Vector3) { 0, 1, 0 },
                .fovy = 90,
                .projection = CAMERA_ORTHOGRAPHIC,
            });

            world.render();

            EndMode3D();

        EndDrawing();
    }
    
    return 0;
}
