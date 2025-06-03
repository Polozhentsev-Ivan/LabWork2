#ifndef PLAYER_H
#define PLAYER_H

#include <ctime>
#include "game_map.h"
#include "../card/player_card.h"

/**
 * @brief Represents the player character in the game.
 *
 * This class manages the player's position, movement, combat actions,
 * and associated player card (stats, inventory, etc.).
 */
class Player {
    private:
        int x,y;                /**< Player's current X and Y coordinates on the map. */
        int moveDelay;          /**< Delay in microseconds between player moves, determined by speed. */
        long long lastMoveTime; /**< Timestamp of the player's last move in microseconds. */
        int attackRange;        /**< The range of the player's attacks. */
        PlayerCard card;        /**< The PlayerCard object containing player's stats and attributes. */ 

        /**
         * @brief Gets the current time in microseconds.
         *
         * @return The current time as a long long representing microseconds since epoch.
         */
        long long getCurrentTimeMicros() const;

    public:
        /**
         * @brief Constructs a Player object.
         *
         * @param startX The initial X coordinate of the player.
         * @param startY The initial Y coordinate of the player.
         */
        Player(int startX = 0, int startY = 0);
        /**
         * @brief Destructor for the Player class.
         */
        ~Player();
        
        /**
         * @brief Attempts to move the player by a given delta on the map.
         *
         * Movement is subject to map boundaries, obstacles, and move delay.
         * @param dx The change in X coordinate.
         * @param dy The change in Y coordinate.
         * @param map The game map to check for valid moves.
         * @return True if the player moved successfully, false otherwise.
         */
        bool move(int dx, int dy, const GameMap& map);
        /**
         * @brief Gets the player's current position.
         *
         * @param outX Reference to store the player's X coordinate.
         * @param outY Reference to store the player's Y coordinate.
         */
        void getPosition(int& outX, int& outY) const;
        /**
         * @brief Sets the player's position to new coordinates.
         *
         * @param newX The new X coordinate.
         * @param newY The new Y coordinate.
         */
        void setPosition(int newX, int newY);
        /**
         * @brief Gets the current move delay for the player.
         *
         * @return The move delay in microseconds.
         */
        int getMoveDelay() const;
        /**
         * @brief Changes the player's speed, which affects move delay.
         *
         * @param delta The amount to change the speed by.
         */
        void changeSpeed(int delta);
        
        /**
         * @brief Makes the player attempt to attack a monster in range.
         *
         * @param map The game map to find and attack monsters on.
         * @return True if an attack was successfully made, false otherwise.
         */
        bool attack(GameMap& map);
        /**
         * @brief Sets the player's attack range.
         *
         * @param range The new attack range.
         */
        void setAttackRange(int range);
        /**
         * @brief Gets the player's current attack range.
         *
         * @return The attack range.
         */
        int getAttackRange() const;
        /**
         * @brief Applies damage to the player.
         *
         * @param damage The amount of damage to take.
         */
        void takeDamage(int damage);
        
        /**
         * @brief Gets a reference to the player's PlayerCard.
         *
         * @return A reference to the PlayerCard object.
         */
        PlayerCard& getCard();
        /**
         * @brief Gets a constant reference to the player's PlayerCard.
         *
         * @return A constant reference to the PlayerCard object.
         */
        const PlayerCard& getCard() const;
        /**
         * @brief Sets the player's PlayerCard to a new card.
         *
         * @param newCard The PlayerCard to assign to the player.
         */
        void setCard(const PlayerCard& newCard);
};

#endif // PLAYER_H
