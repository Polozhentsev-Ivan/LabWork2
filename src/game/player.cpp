/**
 * @file player.cpp
 * @brief Реализация класса Player, представляющего игрока в игре.
 */
#include "../../include/game/player.h"
#include <algorithm>
#include <ctime>
#include <sys/time.h>

/**
 * @brief Конструктор класса Player.
 *
 * @param startX Начальная координата X игрока.
 * @param startY Начальная координата Y игрока.
 */
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

/**
 * @brief Деструктор класса Player.
 */
Player::~Player() {}

/**
 * @brief Получает текущее время в микросекундах.
 *
 * @return Текущее время в микросекундах.
 */
long long Player::getCurrentTimeMicros() const {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000000LL + tv.tv_usec);
}

/**
 * @brief Перемещает игрока на указанное смещение, если это возможно.
 *
 * @param dx Смещение по оси X.
 * @param dy Смещение по оси Y.
 * @param map Игровая карта для проверки возможности перемещения.
 * @return true, если игрок переместился, иначе false.
 */
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

/**
 * @brief Получает текущие координаты игрока.
 *
 * @param outX Ссылка для сохранения координаты X.
 * @param outY Ссылка для сохранения координаты Y.
 */
void Player::getPosition(int& outX, int& outY) const {
    outX = x;
    outY = y;
}

/**
 * @brief Устанавливает новые координаты игрока.
 *
 * @param newX Новая координата X.
 * @param newY Новая координата Y.
 */
void Player::setPosition(int newX, int newY) {
    x = newX;
    y = newY;
}

/**
 * @brief Получает задержку перед следующим возможным перемещением игрока.
 *
 * @return Задержка перемещения в микросекундах.
 */
int Player::getMoveDelay() const {
    return moveDelay;
}

/**
 * @brief Изменяет скорость передвижения игрока (задержку перемещения).
 *
 * @param delta Изменение скорости. Положительное значение уменьшает задержку (увеличивает скорость),
 *              отрицательное - увеличивает задержку (уменьшает скорость).
 */
void Player::changeSpeed(int delta) {
    if (delta > 0) {
        moveDelay = std::max(10000, moveDelay - 10000);
    } else if (delta < 0) {
        moveDelay = std::min(200000, moveDelay + 10000);
    }
}

/**
 * @brief Атакует ближайшего монстра в радиусе атаки.
 *
 * @param map Игровая карта для поиска и атаки монстра.
 * @return true, если атака была произведена, иначе false.
 */
bool Player::attack(GameMap& map) {
    int targetRow, targetCol;
    
    if (map.findMonsterInRange(y, x, attackRange, targetRow, targetCol)) {
        int damage = card.getAttack();
        int expGained = 0;
        bool killed = map.attackMonster(targetRow, targetCol, damage, expGained);
        
        // Если монстр убит, добавляем опыт игроку
        if (killed && expGained > 0) {
            card.addExperience(expGained);
        }
        
        return true;
    }
    
    return false;
}

/**
 * @brief Устанавливает радиус атаки игрока.
 *
 * @param range Новый радиус атаки.
 */
void Player::setAttackRange(int range) {
    attackRange = std::max(1, range);
}

/**
 * @brief Получает радиус атаки игрока.
 *
 * @return Радиус атаки.
 */
int Player::getAttackRange() const {
    return attackRange;
}

/**
 * @brief Получает ссылку на карту игрока (характеристики).
 *
 * @return Ссылка на объект PlayerCard.
 */
PlayerCard& Player::getCard() {
    return card;
}

/**
 * @brief Получает константную ссылку на карту игрока (характеристики).
 *
 * @return Константная ссылка на объект PlayerCard.
 */
const PlayerCard& Player::getCard() const {
    return card;
}

/**
 * @brief Устанавливает новую карту игрока (характеристики).
 *
 * @param newCard Новый объект PlayerCard.
 */
void Player::setCard(const PlayerCard& newCard) {
    card = newCard;
}

/**
 * @brief Наносит урон игроку.
 *
 * Учитывает защиту игрока при расчете фактического урона.
 * @param damage Получаемый урон.
 */
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