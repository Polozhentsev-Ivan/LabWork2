#ifndef MONSTER_CARD_H
#define MONSTER_CARD_H
#include "character_card.h"
#include "../enums.h"

class MonsterCard : public CharacterCard
{
    private:
        Species species;
        int level;
        int experience;
        int silver;
    public:
        MonsterCard(const std::string& name, const std::string& description, int health, int maxHealth, int attack, int defense, int speed, Species species, int level, int experience, int silver);
        MonsterCard();
        Species getSpecies() const;
        int getLevel() const;
        int getExperience() const;
        int getSilver() const;
        void setSpecies(Species species);
        void setLevel(int level);
        void setExperience(int experience);
        void setSilver(int silver);
};
#endif // MONSTER_CARD_H

