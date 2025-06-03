#ifndef PLAYER_CARD_H
#define PLAYER_CARD_H
#include "character_card.h"

/**
 * @brief Represents the player's character card in the game.
 * 
 * This class inherits from CharacterCard and adds attributes specific to the player,
 * such as race, level, experience, experience needed for the next level, and silver.
 */
class PlayerCard : public CharacterCard
{
    private:
        Race race;                      /**< The race of the player. */
        int level;                      /**< The current level of the player. */
        int experience;                 /**< The current experience points of the player. */
        int experienceToNextLevel;      /**< The experience points needed to reach the next level. */
        int silver;                     /**< The amount of silver the player has. */
    public:
        /**
         * @brief Default constructor for PlayerCard.
         */
        PlayerCard();
        /**
         * @brief Constructs a PlayerCard with specified attributes.
         *
         * @param name The name of the card.
         * @param description A description of the card.
         * @param health The current health of the player.
         * @param maxHealth The maximum health of the player.
         * @param attack The attack power of the player.
         * @param defense The defense power of the player.
         * @param speed The speed of the player.
         * @param race The race of the player.
         * @param level The current level of the player.
         * @param experience The current experience points of the player.
         * @param experienceToNextLevel The experience points needed for the next level.
         * @param silver The amount of silver the player has.
         */
        PlayerCard(const std::string& name, const std::string& description, int health, int maxHealth, int attack, int defense, int speed, Race race, int level, int experience, int experienceToNextLevel, int silver);
        /**
         * @brief Gets the race of the player.
         * @return The race of the player.
         */
        Race getRace() const;
        /**
         * @brief Gets the current level of the player.
         * @return The current level.
         */
        int getLevel() const;
        /**
         * @brief Gets the current experience points of the player.
         * @return The current experience points.
         */
        int getExperience() const;
        /**
         * @brief Gets the experience points needed to reach the next level.
         * @return The experience points needed for the next level.
         */
        int getExperienceToNextLevel() const;
        /**
         * @brief Sets the race of the player.
         * @param race The new race value.
         */
        void setRace(const Race& race);
        /**
         * @brief Sets the current level of the player.
         * @param level The new level value.
         */
        void setLevel(int level);
        /**
         * @brief Sets the current experience points of the player.
         * @param exp The new experience points value.
         */
        void setExperience(int exp);
        /**
         * @brief Adds experience points to the player's current experience.
         * @param amount The amount of experience to add.
         */
        void addExperience(int amount);
        /**
         * @brief Levels up the player, increasing stats and resetting experience for the next level.
         */
        void levelUp();
        /**
         * @brief Sets the experience points needed to reach the next level.
         * @param expTNL The new value for experience to next level.
         */
        void setExperienceToNextLevel(int expTNL);
        /**
         * @brief Gets the amount of silver the player has.
         * @return The amount of silver.
         */
        int getSilver() const;
        /**
         * @brief Sets the amount of silver the player has.
         * @param silver The new amount of silver.
         */
        void setSilver(int silver);
        /**
         * @brief Adds silver to the player's current amount.
         * @param amount The amount of silver to add.
         */
        void addSilver(int amount);
        /**
         * @brief Removes silver from the player's current amount.
         * @param amount The amount of silver to remove.
         */
        void removeSilver(int amount);
        /**
         * @brief Checks if the player has enough experience to level up.
         * @return True if the player can level up, false otherwise.
         */
        bool levelUpCheck();
};
#endif // PLAYER_CARD_H
