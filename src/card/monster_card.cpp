#include "../../include/card/monster_card.h"

MonsterCard::MonsterCard(const std::string& name, const std::string& description, 
                        int health, int maxHealth, int attack, int defense, int speed, 
                        Species species, int level, int experience, int silver)
    : CharacterCard(name, description, health, maxHealth, attack, defense, speed),
      species(species), level(level), experience(experience), silver(silver) {}

MonsterCard::MonsterCard() : CharacterCard(), species(Species::unknown), 
                            level(1), experience(0), silver(0) {}

Species MonsterCard::getSpecies() const {
    return species;
}

int MonsterCard::getLevel() const {
    return level;
}

int MonsterCard::getExperience() const {
    return experience;
}

int MonsterCard::getSilver() const {
    return silver;
}

void MonsterCard::setSpecies(Species species) {
    this->species = species;
}

void MonsterCard::setLevel(int level) {
    this->level = level;
}

void MonsterCard::setExperience(int experience) {
    this->experience = experience;
}

void MonsterCard::setSilver(int silver) {
    this->silver = silver;
} 