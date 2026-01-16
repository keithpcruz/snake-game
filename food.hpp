// Food class: used as the "target" the bomber should hit.

#pragma once

#include <cstdlib>   // std::rand
#include "snake.hpp"

// Food class just remembers where the food is and can respawn it.
class Food {
public:
    Food() {
        position.x = 0;
        position.y = 0;
    }

    // Pick a random cell that is not on the snake.
    void spawn(int gridWidth, int gridHeight, const Snake& snake) {
        while (true) {
            Segment candidate;
            candidate.x = std::rand() % gridWidth;
            candidate.y = std::rand() % gridHeight;

            if (!snake.isOnCell(candidate.x, candidate.y)) {
                position = candidate;
                break;
            }
        }
    }

    Segment getPosition() const {
        return position;
    }

private:
    Segment position;
};
