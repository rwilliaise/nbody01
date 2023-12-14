
#include <cmath>
#include <cstdio>
#include <raylib.h>

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

#include "globals.h"
#include "world.h"
#include "body.h"

using namespace nbody;

const char *perspective_names[] = {
    "sun",
    "earth",
    NULL
};

int main(int argc, char *argv[]) {
    // SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(1024, 1024, "");

    world world;

    {
        body sun(SUN_RADIUS, SUN_MASS, YELLOW);
        body mercury(MERCURY_RADIUS * 50, MERCURY_MASS, GRAY);
        body venus(VENUS_RADIUS, VENUS_MASS, BROWN);
        body earth(EARTH_RADIUS, EARTH_MASS, BLUE);
        body moon(MOON_RADIUS, MOON_MASS, WHITE);
        mercury.encircle(sun, MERCURY_DIST);
        venus.encircle(sun, VENUS_DIST);
        earth.encircle(sun, EARTH_DIST);
        moon.encircle(earth, MOON_DIST);

        world.push(std::move(sun)); // 0
        world.push(std::move(mercury)); // 1
        world.push(std::move(venus)); // 2
        world.push(std::move(earth)); // 3
        world.push(std::move(moon)); // 4
    }
    
    body *sun = world.from_id(0);
    body *mercury = world.from_id(1);
    body *earth = world.from_id(3);

    Camera3D cam = (Camera3D) {
        .position = { 0, 50, 1 },
        .target = { 0, 0, 0 },
        .up = { 0, 1, 0 },
        .fovy = 150,
        .projection = CAMERA_ORTHOGRAPHIC,
    };
    int perspective = 0;


    double total_time = 0;
    while (!WindowShouldClose()) {
        world.update();

        int next_persp = perspective + 1;
        if (!perspective_names[next_persp]) next_persp = 0;
        
        double days = (total_time * TIME_SCALE) / (24 * 3600);
        DrawText(TextFormat("%0.0f days elapsed", std::floor(days)), 5, 35, 12, GRAY);

        if (GuiButton({ 5, 5, 50, 25 }, perspective_names[next_persp])) {
            perspective = next_persp;
            switch (perspective) {
            case 0:
                cam = (Camera3D) {
                    .position = { 0, 50, 1 },
                    .target = { 0, 0, 0 },
                    .up = { 0, 1, 0 },
                    .fovy = 150,
                    .projection = CAMERA_ORTHOGRAPHIC,
                };
                break;
            }
        }


        switch (perspective) {
        case 1:
            cam = (Camera3D) {
                .position = (earth->pos * RENDER_SCALE +  vec3 { 0, 0.5, -1 }).convert(),
                .target = (earth->pos * RENDER_SCALE).convert(),
                .up = (Vector3) { 0, 1, 0 },
                .fovy = 90,
                .projection = CAMERA_PERSPECTIVE,
            };
            break;
        default:
            break;
        };

        BeginDrawing();
            ClearBackground(BLACK);

            vec3 diff = (earth->pos - sun->pos).normalized();

            BeginMode3D(cam);
            world.render();
            EndMode3D();

        EndDrawing();
        total_time += GetFrameTime();
    }
    
    return 0;
}
