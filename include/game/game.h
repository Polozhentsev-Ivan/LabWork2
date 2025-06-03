#ifndef GAME_H
#define GAME_H

#include <string>
#include <iostream>
#include "terminal_manager.h"
#include "input.h"
#include "game_map.h"
#include "player.h"
#include "renderer.h"
#include "viewport.h"

/**
 * @brief Main class for managing the game logic, state, and rendering.
 *
 * This class orchestrates the different components of the game, including
 * the terminal, input handling, map, player, renderer, and viewport.
 * It also manages game state transitions, such as starting, running, and ending the game.
 */
class Game {
    private:
        TerminalManager terminal; /**< Manages terminal interactions and settings. */
        Input input;             /**< Handles user input. */
        GameMap map;             /**< Represents the game map and its elements. */
        Player player;           /**< Represents the player character. */
        Renderer renderer;       /**< Handles rendering of the game state to the terminal. */
        Viewport viewport;       /**< Manages the visible portion of the game map. */

        bool gameRunning;        /**< Flag indicating if the game is currently running. */
        
        int targetedMonsterRow;  /**< Row of the currently targeted monster. */
        int targetedMonsterCol;  /**< Column of the currently targeted monster. */
        bool targetedMonster;    /**< Flag indicating if a monster is currently targeted. */
        
        bool playerStatsChanged; /**< Flag indicating if player stats have changed since the last update. */
        int lastHealth;          /**< Player's health in the previous frame. */
        int lastMaxHealth;       /**< Player's maximum health in the previous frame. */
        int lastAttack;          /**< Player's attack power in the previous frame. */
        int lastDefense;         /**< Player's defense power in the previous frame. */
        int lastSpeed;           /**< Player's speed in the previous frame. */
        int lastLevel;           /**< Player's level in the previous frame. */
        int lastExperience;      /**< Player's experience points in the previous frame. */
        int lastExpToNextLevel;  /**< Experience needed for the next level in the previous frame. */
        
        // Timer for the final wave of monsters
        std::chrono::steady_clock::time_point gameStartTime; /**< Time when the game started. */
        bool finalWaveSpawned; /**< Flag indicating if the final wave of monsters has spawned. */
        int finalWaveTimeSeconds; /**< Time in seconds until the final wave spawns. */
        
        // For game completion
        bool gameCompleted; /**< Flag indicating if the game has been completed. */
        std::chrono::steady_clock::time_point finalWaveStartTime; /**< Time when the final wave started. */
        
        /**
         * @brief Updates the visual indicators for monster spawn boxes on the map.
         */
        void updateBoxIndicators();
        /**
         * @brief Activates a monster spawn box if the player is on it and it's ready.
         */
        void activateMonsterBox();
        /**
         * @brief Initializes all monster spawn box indicators at the start of the game.
         */
        void initAllBoxIndicators();
        
        /**
         * @brief Displays the player's current statistics on the screen.
         */
        void showPlayerStats();
        /**
         * @brief Displays information about the targeted monster.
         */
        void showMonsterInfo();
        /**
         * @brief Clears the monster information display from the screen.
         */
        void clearMonsterInfo();
        /**
         * @brief Checks if player stats have changed and updates the display if necessary.
         */
        void checkPlayerStats();
        /**
         * @brief Displays the timer for the final wave of monsters.
         */
        void showFinalWaveTimer();
        /**
         * @brief Spawns the final wave of monsters.
         */
        void spawnFinalWave();
        /**
         * @brief Updates the state of monsters in the final wave.
         */
        void updateFinalWaveMonsters();
        /**
         * @brief Checks if the conditions for game completion have been met.
         */
        void checkGameCompletion();
        /**
         * @brief Displays the game completion message.
         */
        void showGameCompletionMessage();

    public:
        /**
         * @brief Default constructor for the Game class.
         */
        Game();
        /**
         * @brief Destructor for the Game class.
         */
        ~Game();
        /**
         * @brief Initializes the game with the specified map file.
         *
         * @param mapFile The path to the map file.
         * @return True if initialization is successful, false otherwise.
         */
        bool init(const std::string& mapFile);
        /**
         * @brief Starts and runs the main game loop.
         */
        void run();
        /**
         * @brief Processes user input and updates the game state accordingly.
         *
         * @return True if the game should continue running, false if the game should exit.
         */
        bool processInput();
        /**
         * @brief Gets the delay between player moves.
         *
         * @return The move delay in milliseconds.
         */
        int getMoveDelay() const;
        /**
         * @brief Gets the height of the terminal window.
         *
         * @return The terminal height in characters.
         */
        int getTermHeight() const;
};

#endif
