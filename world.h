
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

    double delta;

private:
    friend class body;

    std::vector<body> bodies;
    uint64_t next_id = 0;
};

}
