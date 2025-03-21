#ifndef PLAYER_CARD_H
#define PLAYER_CARD_H
#include "character_card.h"

class PlayerCard : public CharacterCard
{
    private:
        Race race;
        int level;
        int experience;
        int experienceToNextLevel;
        int silver;
    public:
        PlayerCard();
        PlayerCard(const std::string& name, const std::string& description, int health, int maxHealth, int attack, int defense, int speed, Race race, int level, int experience, int experienceToNextLevel, int silver);
        Race getRace() const;
        int getLevel() const;
        int getExperience() const;
        int getExperienceToNextLevel() const;
        void setRace(const Race& race);
        void setLevel(int level);
        void setExperience(int exp);
        void addExperience(int amount);
        void levelUp();
        void setExperienceToNextLevel(int expTNL);
        int getSilver() const;
        void setSilver(int silver);
        void addSilver(int amount);
        void removeSilver(int amount);
        bool levelUpCheck();
};
#endif // PLAYER_CARD_H
