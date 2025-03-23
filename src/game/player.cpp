#include "../../include/game/player.h"
#include <algorithm>
#include <ctime>
#include <sys/time.h>

Player::Player(int startX, int startY) 
    : x(startX), y(startY), moveDelay(50000), lastMoveTime(0), attackRange(3) {
    lastMoveTime = getCurrentTimeMicros();
    
    card = PlayerCard(
        "Hero", 
        "The main character", 
        100,
        100,
        15,
        10,
        5,
        Race::human,
        1,
        0,
        100,
        0
    );
}

Player::~Player() {}

long long Player::getCurrentTimeMicros() const {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000000LL + tv.tv_usec);
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

bool Player::attack(GameMap& map) {
    int targetRow, targetCol;
    
    if (map.findMonsterInRange(y, x, attackRange, targetRow, targetCol)) {
        int damage = card.getAttack();
        map.attackMonster(targetRow, targetCol, damage);
        
        return true;
    }
    
    return false;
}

void Player::setAttackRange(int range) {
    attackRange = std::max(1, range);
}

int Player::getAttackRange() const {
    return attackRange;
}

PlayerCard& Player::getCard() {
    return card;
}

const PlayerCard& Player::getCard() const {
    return card;
}

void Player::setCard(const PlayerCard& newCard) {
    card = newCard;
}

void Player::takeDamage(int damage) {
    if (damage <= 0) {
        return;
    }
    
    int defense = card.getDefense();
    int actualDamage = std::max(1, damage - defense / 2);
    
    int currentHealth = card.getHealth();
    int newHealth = std::max(0, currentHealth - actualDamage);
    card.setHealth(newHealth);
} 