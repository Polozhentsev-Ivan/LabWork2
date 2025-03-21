#include "../../include/card/character_card.h"

CharacterCard::CharacterCard(const std::string& name, const std::string& description,
                            int health, int maxHealth, int attack, int defense, int speed)
    : Card(name, description), health(health), maxHealth(maxHealth), attack(attack), 
      defense(defense), speed(speed) {}

CharacterCard::CharacterCard() : Card(), health(100), attack(10), 
                                defense(5), speed(5) {}

int CharacterCard::getHealth() const {
    return health;
}

int CharacterCard::getAttack() const {
    return attack;
}

int CharacterCard::getDefense() const {
    return defense;
}

int CharacterCard::getSpeed() const {
    return speed;
}

void CharacterCard::setHealth(int health) {
    this->health = health;
}

void CharacterCard::setAttack(int attack) {
    this->attack = attack;
}

void CharacterCard::setDefense(int defense) {
    this->defense = defense;
}

void CharacterCard::setSpeed(int speed) {
    this->speed = speed;
} 

int CharacterCard::getMaxHealth () const {
    return maxHealth;
}

void CharacterCard::setMaxHealth (int maxHealth) {
    this->maxHealth = maxHealth;
}