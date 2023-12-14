
#include "world.h"
#include <raylib.h>

namespace nbody {

void world::render() {
    for (body &b : bodies) {
        b.render();   
    }
}

void world::update() {
    delta = GetFrameTime() * 1.0e6;

    for (body &b : bodies) {
        b.update(*this);
    }
}

}
