#ifndef MONSTER_CARD_H
#define MONSTER_CARD_H
#include "character_card.h"
#include "../enums.h"

/**
 * @brief Represents a monster card in the game.
 * 
 * This class inherits from CharacterCard and adds attributes specific to monsters,
 * such as species, level, experience, and silver.
 */
class MonsterCard : public CharacterCard
{
    private:
        Species species;    /**< The species of the monster. */
        int level;          /**< The level of the monster. */
        int experience;     /**< The experience points the monster gives when defeated. */
        int silver;         /**< The amount of silver the monster drops when defeated. */
    public:
        /**
         * @brief Constructs a MonsterCard with specified attributes.
         *
         * @param name The name of the card.
         * @param description A description of the card.
         * @param health The current health of the monster.
         * @param maxHealth The maximum health of the monster.
         * @param attack The attack power of the monster.
         * @param defense The defense power of the monster.
         * @param speed The speed of the monster.
         * @param species The species of the monster.
         * @param level The level of the monster.
         * @param experience The experience points the monster gives.
         * @param silver The amount of silver the monster drops.
         */
        MonsterCard(const std::string& name, const std::string& description, int health, int maxHealth, int attack, int defense, int speed, Species species, int level, int experience, int silver);
        /**
         * @brief Default constructor for MonsterCard.
         */
        MonsterCard();
        /**
         * @brief Gets the species of the monster.
         * @return The species of the monster.
         */
        Species getSpecies() const;
        /**
         * @brief Gets the level of the monster.
         * @return The level of the monster.
         */
        int getLevel() const;
        /**
         * @brief Gets the experience points the monster gives.
         * @return The experience points.
         */
        int getExperience() const;
        /**
         * @brief Gets the amount of silver the monster drops.
         * @return The amount of silver.
         */
        int getSilver() const;
        /**
         * @brief Sets the species of the monster.
         * @param species The new species value.
         */
        void setSpecies(Species species);
        /**
         * @brief Sets the level of the monster.
         * @param level The new level value.
         */
        void setLevel(int level);
        /**
         * @brief Sets the experience points the monster gives.
         * @param experience The new experience points value.
         */
        void setExperience(int experience);
        /**
         * @brief Sets the amount of silver the monster drops.
         * @param silver The new amount of silver.
         */
        void setSilver(int silver);
};
#endif // MONSTER_CARD_H

