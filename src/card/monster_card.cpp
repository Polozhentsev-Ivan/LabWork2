/**
 * @file monster_card.cpp
 * @brief Implements the MonsterCard class methods.
 */

#include "../../include/card/monster_card.h"

/**
 * @brief Constructs a MonsterCard object with specified attributes.
 *
 * @param name The name of the monster.
 * @param description The description of the monster.
 * @param health Current health of the monster.
 * @param maxHealth Maximum health of the monster.
 * @param attack Attack power of the monster.
 * @param defense Defense power of the monster.
 * @param speed Speed of the monster.
 * @param species The species of the monster.
 * @param level The level of the monster.
 * @param experience Experience points awarded for defeating the monster.
 * @param silver Silver awarded for defeating the monster.
 */
MonsterCard::MonsterCard(const std::string& name, const std::string& description, 
                        int health, int maxHealth, int attack, int defense, int speed, 
                        Species species, int level, int experience, int silver)
    : CharacterCard(name, description, health, maxHealth, attack, defense, speed),
      species(species), level(level), experience(experience), silver(silver) {}

/**
 * @brief Default constructor for the MonsterCard class.
 *
 * Initializes with default character stats, unknown species, level 1, and zero experience/silver.
 */
MonsterCard::MonsterCard() : CharacterCard(), species(Species::unknown), 
                            level(1), experience(0), silver(0) {}

/**
 * @brief Gets the species of the monster.
 *
 * @return The monster's species.
 */
Species MonsterCard::getSpecies() const {
    return species;
}

/**
 * @brief Gets the level of the monster.
 *
 * @return The monster's level.
 */
int MonsterCard::getLevel() const {
    return level;
}

/**
 * @brief Gets the experience points awarded by this monster.
 *
 * @return The experience points.
 */
int MonsterCard::getExperience() const {
    return experience;
}

/**
 * @brief Gets the amount of silver awarded by this monster.
 *
 * @return The amount of silver.
 */
int MonsterCard::getSilver() const {
    return silver;
}

/**
 * @brief Sets the species of the monster.
 *
 * @param species The new species for the monster.
 */
void MonsterCard::setSpecies(Species species) {
    this->species = species;
}

/**
 * @brief Sets the level of the monster.
 *
 * @param level The new level for the monster.
 */
void MonsterCard::setLevel(int level) {
    this->level = level;
}

/**
 * @brief Sets the experience points awarded by this monster.
 *
 * @param experience The new experience points value.
 */
void MonsterCard::setExperience(int experience) {
    this->experience = experience;
}

/**
 * @brief Sets the amount of silver awarded by this monster.
 *
 * @param silver The new amount of silver.
 */
void MonsterCard::setSilver(int silver) {
    this->silver = silver;
}