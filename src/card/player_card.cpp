#include "../../include/card/player_card.h"

PlayerCard::PlayerCard(const std::string& name, const std::string& description, int health, int maxHealth, int attack, int defense, int speed, Race race, int level, int experience, int experienceToNextLevel, int silver)
    : CharacterCard(name, description, health, maxHealth, attack, defense, speed), race(race), level(level), experience(experience), experienceToNextLevel(experienceToNextLevel), silver(silver) {}

PlayerCard::PlayerCard() : CharacterCard(), race(Race::unknown), level(0), experience(0), experienceToNextLevel(0), silver(0) {}

Race PlayerCard::getRace() const {
    return race;
}

int PlayerCard::getLevel() const {
    return level;
}

int PlayerCard::getExperience() const {
    return experience;
}

int PlayerCard::getExperienceToNextLevel() const {
    return experienceToNextLevel;
}


void PlayerCard::setRace(const Race& race) {
    this->race = race;
}

void PlayerCard::setLevel(int level) {
    this->level = level;
}

void PlayerCard::setExperience(int exp) {
    this->experience = exp;
}


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

void PlayerCard::setExperienceToNextLevel(int expTNL) {
    this->experienceToNextLevel = expTNL;
}

int PlayerCard::getSilver() const {
    return silver;
}

void PlayerCard::setSilver(int silver) {
    this->silver = silver;
}

void PlayerCard::addSilver(int amount) {
    this->silver += amount;
}

void PlayerCard::removeSilver(int amount) {
    this->silver -= amount;
}

bool PlayerCard::levelUpCheck() {
    if (this->experience >= this->experienceToNextLevel) {
        levelUp();
        return true;
    }
    return false;
}
