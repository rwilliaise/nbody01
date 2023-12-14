
#pragma once

#include <vector>
#include "body.h"

namespace nbody {

class world {
public:

    void update();
    void render();

    inline void push(body &&b) {
        b.id = next_id++;
        bodies.push_back(b);
    }

    inline body *from_id(uint64_t id) {
        for (int i = 0; i < bodies.size(); i++) {
            body *b = &bodies[i];
            if (b->id == id) return b;
        }

        return nullptr;
    }

    double delta;

private:
    friend class body;

    std::vector<body> bodies;
    uint64_t next_id = 0;
};

}
