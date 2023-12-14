
#include "world.h"
#include "globals.h"
#include <raylib.h>

namespace nbody {

void world::render() {
    for (body &b : bodies) {
        b.render();   
    }
}

void world::update() {
    delta = GetFrameTime() * TIME_SCALE;

    for (body &b : bodies) {
        b.update(*this);
    }
}

}
