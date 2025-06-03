/**
 * @file player_card.cpp
 * @brief Implements the PlayerCard class methods.
 */
#include "../../include/card/player_card.h"

/**
 * @brief Constructs a PlayerCard object with specified attributes.
 *
 * @param name The name of the player.
 * @param description The description of the player.
 * @param health Current health of the player.
 * @param maxHealth Maximum health of the player.
 * @param attack Attack power of the player.
 * @param defense Defense power of the player.
 * @param speed Speed of the player.
 * @param race The race of the player.
 * @param level The current level of the player.
 * @param experience The current experience points of the player.
 * @param experienceToNextLevel The experience points needed for the next level.
 * @param silver The amount of silver the player has.
 */
PlayerCard::PlayerCard(const std::string& name, const std::string& description, int health, int maxHealth, int attack, int defense, int speed, Race race, int level, int experience, int experienceToNextLevel, int silver)
    : CharacterCard(name, description, health, maxHealth, attack, defense, speed), race(race), level(level), experience(experience), experienceToNextLevel(experienceToNextLevel), silver(silver) {}

/**
 * @brief Default constructor for the PlayerCard class.
 *
 * Initializes with default character stats, unknown race, and zero level, experience, and silver.
 */
PlayerCard::PlayerCard() : CharacterCard(), race(Race::unknown), level(0), experience(0), experienceToNextLevel(0), silver(0) {}

/**
 * @brief Gets the race of the player.
 *
 * @return The player's race.
 */
Race PlayerCard::getRace() const {
    return race;
}

/**
 * @brief Gets the current level of the player.
 *
 * @return The player's level.
 */
int PlayerCard::getLevel() const {
    return level;
}

/**
 * @brief Gets the current experience points of the player.
 *
 * @return The player's experience points.
 */
int PlayerCard::getExperience() const {
    return experience;
}

/**
 * @brief Gets the experience points needed for the next level.
 *
 * @return The experience points to the next level.
 */
int PlayerCard::getExperienceToNextLevel() const {
    return experienceToNextLevel;
}


/**
 * @brief Sets the race of the player.
 *
 * @param race The new race for the player.
 */
void PlayerCard::setRace(const Race& race) {
    this->race = race;
}

/**
 * @brief Sets the level of the player.
 *
 * @param level The new level for the player.
 */
void PlayerCard::setLevel(int level) {
    this->level = level;
}

/**
 * @brief Sets the experience points of the player.
 *
 * @param exp The new experience points value.
 */
void PlayerCard::setExperience(int exp) {
    this->experience = exp;
}


/**
 * @brief Adds experience points to the player and handles leveling up.
 *
 * @param amount The amount of experience to add.
 * @throws std::invalid_argument if amount is negative.
 */
void PlayerCard::addExperience(int amount) {
    if (amount < 0) {
        throw std::invalid_argument("Experience amount cannot be negative");
    }
    
    this->experience += amount;
    
    // Проверяем, достигнут ли порог для нового уровня
    while (this->experience >= this->experienceToNextLevel) {
        int excessExperience = this->experience - this->experienceToNextLevel;
        levelUp();
        this->experience = excessExperience; // Переносим излишки опыта
    }
}

/**
 * @brief Levels up the player, increasing stats and experience requirements.
 */
void PlayerCard::levelUp() {
    // Увеличиваем уровень
    this->level++;
    
    // Сбрасываем текущий опыт (теперь это делается в addExperience)
    // this->experience -= this->experienceToNextLevel; // Удаляем эту строку
    
    // Увеличиваем требования для следующего уровня (например, на 20% больше)
    this->experienceToNextLevel = static_cast<int>(this->experienceToNextLevel * 1.2);
    
    // Увеличиваем характеристики игрока
    this->maxHealth += 10;
    this->health = this->maxHealth;  // Полное восстановление здоровья
    this->attack += 2;
    this->defense += 1;
    this->speed += 1;
}

/**
 * @brief Sets the experience points needed for the next level.
 *
 * @param expTNL The new experience points to next level value.
 */
void PlayerCard::setExperienceToNextLevel(int expTNL) {
    this->experienceToNextLevel = expTNL;
}

/**
 * @brief Gets the amount of silver the player has.
 *
 * @return The player's silver amount.
 */
int PlayerCard::getSilver() const {
    return silver;
}

/**
 * @brief Sets the amount of silver the player has.
 *
 * @param silver The new silver amount.
 */
void PlayerCard::setSilver(int silver) {
    this->silver = silver;
}

/**
 * @brief Adds silver to the player's inventory.
 *
 * @param amount The amount of silver to add.
 */
void PlayerCard::addSilver(int amount) {
    this->silver += amount;
}

/**
 * @brief Removes silver from the player's inventory.
 *
 * @param amount The amount of silver to remove.
 */
void PlayerCard::removeSilver(int amount) {
    this->silver -= amount;
}

/**
 * @brief Checks if the player has enough experience to level up and performs level up if so.
 *
 * @return True if the player leveled up, false otherwise.
 */
bool PlayerCard::levelUpCheck() {
    if (this->experience >= this->experienceToNextLevel) {
        levelUp();
        return true;
    }
    return false;
}
