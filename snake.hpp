// Snake class: here it acts like the bomber's path and position.

#pragma once

#include <deque>

// A single cell on the grid.
struct Segment {
    int x;
    int y;
};

// Snake class stores the body and direction, and handles movement.
class Snake {
public:
    // Make a snake of length 3 starting at (startX, startY).
    Snake(int startX, int startY) {
        reset(startX, startY);
    }

    // Put the snake back in the center going to the right.
    void reset(int startX, int startY) {
        body.clear();
        body.push_back({startX, startY});       // head
        body.push_back({startX - 1, startY});   // middle
        body.push_back({startX - 2, startY});   // tail
        dirX = 1;
        dirY = 0;
    }

    // Change direction, but do not allow an instant 180° turn.
    void setDirection(int newDirX, int newDirY) {
        if (newDirX == -dirX && newDirY == -dirY) {
            return;
        }
        dirX = newDirX;
        dirY = newDirY;
    }

    int getDirX() const { return dirX; }
    int getDirY() const { return dirY; }

    // Current head position.
    Segment getHead() const {
        return body.front();
    }

    // Where the head will be next step.
    Segment getNextHead() const {
        Segment next = getHead();
        next.x += dirX;
        next.y += dirY;
        return next;
    }

    // True if any part of the snake is on (x, y).
    bool isOnCell(int x, int y) const {
        for (std::size_t i = 0; i < body.size(); ++i) {
            if (body[i].x == x && body[i].y == y) {
                return true;
            }
        }
        return false;
    }

    // Check if moving to nextHead would hit the snake.
    bool willHitSelf(const Segment& nextHead) const {
        for (std::size_t i = 0; i < body.size(); ++i) {
            if (body[i].x == nextHead.x && body[i].y == nextHead.y) {
                return true;
            }
        }
        return false;
    }

    // Add new head; if grow is false, remove the tail.
    void move(const Segment& nextHead, bool grow) {
        body.push_front(nextHead);
        if (!grow) {
            body.pop_back();
        }
    }

    // Used by main() for drawing.
    const std::deque<Segment>& getBody() const {
        return body;
    }

private:
    std::deque<Segment> body;
    int dirX;
    int dirY;
};
