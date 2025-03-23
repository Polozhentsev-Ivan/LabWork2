#include "../../include/game/player.h"
#include <algorithm>
#include <ctime>

Player::Player(int startX, int startY) 
    : x(startX), y(startY), moveDelay(50000), lastMoveTime(0) {
    lastMoveTime = getCurrentTimeMicros();
}

Player::~Player() {}

long long Player::getCurrentTimeMicros() const {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (ts.tv_sec * 1000000LL + ts.tv_nsec / 1000);
}

bool Player::move(int dx, int dy, const GameMap& map) {
    if (dx == 0 && dy == 0) {
        return false;
    }
    
    long long currentTime = getCurrentTimeMicros();
    if (currentTime - lastMoveTime < moveDelay) {
        return false;
    }
    
    int newX = x + dx;
    int newY = y + dy;
    
    bool moved = false;
    
    if (map.canMoveTo(newY, newX)) {
        x = newX;
        y = newY;
        moved = true;
    } else {
        if (dx != 0 && map.canMoveTo(y, x + dx)) {
            x += dx;
            moved = true;
        } else if (dy != 0 && map.canMoveTo(y + dy, x)) {
            y += dy;
            moved = true;
        }
    }
    
    if (moved) {
        lastMoveTime = currentTime;
    }
    
    return moved;
}

void Player::getPosition(int& outX, int& outY) const {
    outX = x;
    outY = y;
}

void Player::setPosition(int newX, int newY) {
    x = newX;
    y = newY;
}

int Player::getMoveDelay() const {
    return moveDelay;
}

void Player::changeSpeed(int delta) {
    if (delta > 0) {
        moveDelay = std::max(10000, moveDelay - 10000);
    } else if (delta < 0) {
        moveDelay = std::min(200000, moveDelay + 10000);
    }
} 