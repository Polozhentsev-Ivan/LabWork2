#ifndef CHARACTER_CARD_H
#define CHARACTER_CARD_H
#include "card.h"
#include "../enums.h"

/**
 * @brief Represents a character card in the game.
 * 
 * This class inherits from the Card class and adds attributes specific to characters,
 * such as health, attack, defense, and speed.
 */
class CharacterCard : public Card
{
    protected:
        int health;       /**< The current health of the character. */
        int maxHealth;    /**< The maximum health of the character. */
        int attack;       /**< The attack power of the character. */
        int defense;      /**< The defense power of the character. */
        int speed;        /**< The speed of the character. */
    public:
        /**
         * @brief Default constructor for CharacterCard.
         */
        CharacterCard();
        /**
         * @brief Constructs a CharacterCard with specified attributes.
         * 
         * @param name The name of the card.
         * @param description A description of the card.
         * @param health The current health of the character.
         * @param maxHealth The maximum health of the character.
         * @param attack The attack power of the character.
         * @param defense The defense power of the character.
         * @param speed The speed of the character.
         */
        CharacterCard(const std::string& name, const std::string& description, int health, int maxHealth, int attack, int defense, int speed);
        /**
         * @brief Gets the current health of the character.
         * @return The current health.
         */
        int getHealth() const;
        /**
         * @brief Gets the maximum health of the character.
         * @return The maximum health.
         */
        int getMaxHealth() const;
        /**
         * @brief Gets the attack power of the character.
         * @return The attack power.
         */
        int getAttack() const;
        /**
         * @brief Gets the defense power of the character.
         * @return The defense power.
         */
        int getDefense() const;
        /**
         * @brief Gets the speed of the character.
         * @return The speed.
         */
        int getSpeed() const;
        /**
         * @brief Sets the current health of the character.
         * @param health The new health value.
         */
        void setHealth(int health);
        /**
         * @brief Sets the maximum health of the character.
         * @param maxHealth The new maximum health value.
         */
        void setMaxHealth(int maxHealth);
        /**
         * @brief Sets the attack power of the character.
         * @param attack The new attack power value.
         */
        void setAttack(int attack);
        /**
         * @brief Sets the defense power of the character.
         * @param defense The new defense power value.
         */
        void setDefense(int defense);
        /**
         * @brief Sets the speed of the character.
         * @param speed The new speed value.
         */
        void setSpeed(int speed);
};
#endif // CHARACTER_CARD_H
