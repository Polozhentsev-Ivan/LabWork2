/**
 * @file character_card.cpp
 * @brief Implements the CharacterCard class methods.
 */

#include "../../include/card/character_card.h"

/**
 * @brief Constructs a CharacterCard object with specified attributes.
 *
 * @param name The name of the character card.
 * @param description The description of the character card.
 * @param health The current health of the character.
 * @param maxHealth The maximum health of the character.
 * @param attack The attack power of the character.
 * @param defense The defense power of the character.
 * @param speed The speed of the character.
 */
CharacterCard::CharacterCard(const std::string& name, const std::string& description,
                            int health, int maxHealth, int attack, int defense, int speed)
    : Card(name, description), health(health), maxHealth(maxHealth), attack(attack), 
      defense(defense), speed(speed) {}

/**
 * @brief Default constructor for the CharacterCard class.
 *
 * Initializes with default character stats.
 */
CharacterCard::CharacterCard() : Card(), health(100), maxHealth(100), attack(10), 
                                defense(5), speed(5) {}

/**
 * @brief Gets the current health of the character.
 *
 * @return The current health.
 */
int CharacterCard::getHealth() const {
    return health;
}

/**
 * @brief Gets the attack power of the character.
 *
 * @return The attack power.
 */
int CharacterCard::getAttack() const {
    return attack;
}

/**
 * @brief Gets the defense power of the character.
 *
 * @return The defense power.
 */
int CharacterCard::getDefense() const {
    return defense;
}

/**
 * @brief Gets the speed of the character.
 *
 * @return The speed.
 */
int CharacterCard::getSpeed() const {
    return speed;
}

/**
 * @brief Sets the current health of the character.
 *
 * @param health The new health value.
 */
void CharacterCard::setHealth(int health) {
    this->health = health;
}

/**
 * @brief Sets the attack power of the character.
 *
 * @param attack The new attack power value.
 */
void CharacterCard::setAttack(int attack) {
    this->attack = attack;
}

/**
 * @brief Sets the defense power of the character.
 *
 * @param defense The new defense power value.
 */
void CharacterCard::setDefense(int defense) {
    this->defense = defense;
}

/**
 * @brief Sets the speed of the character.
 *
 * @param speed The new speed value.
 */
void CharacterCard::setSpeed(int speed) {
    this->speed = speed;
} 

/**
 * @brief Gets the maximum health of the character.
 *
 * @return The maximum health.
 */
int CharacterCard::getMaxHealth () const {
    return maxHealth;
}

/**
 * @brief Sets the maximum health of the character.
 *
 * @param maxHealth The new maximum health value.
 */
void CharacterCard::setMaxHealth (int maxHealth) {
    this->maxHealth = maxHealth;
}