#ifndef GAME_MAP_H
#define GAME_MAP_H

#include <vector>
#include <string>
#include <fstream>
#include <map>
#include <unordered_map>
#include <utility>
#include <chrono>
#include "../game/enviroment_manager.h"
#include "../card/monster_card.h"

/**
 * @brief Structure to hold information about a monster spawn box.
 */
struct BoxInfo {
    int topRow;  /**< The top row coordinate of the box. */
    int leftCol; /**< The leftmost column coordinate of the box. */
    int width;   /**< The width of the box. */
    int height;  /**< The height of the box. */
};

/**
 * @brief Manages the game map, including its layout, entities, and interactions.
 *
 * This class is responsible for loading the map from a file, handling player and monster
 * movement, managing environmental elements like trees and monster spawn boxes,
 * and facilitating combat interactions.
 */
class GameMap {
    private:
        std::vector<std::string> mapData; /**< 2D vector representing the raw map layout. */
        TreeManager treeManager;         /**< Manages tree spaces on the map. */
        MonsterBox monsterBoxManager;    /**< Manages monster spawn boxes on the map. */
        std::map<std::pair<int, int>, MonsterCard> monsters; /**< Stores monsters currently on the map, keyed by their coordinates. */
        std::unordered_map<size_t, std::chrono::steady_clock::time_point> monsterLastAttackTime; /**< Tracks the last attack time for each monster to manage attack cooldowns. */

        /**
         * @brief Generates a unique hash for a given map position.
         *
         * @param row The row of the position.
         * @param col The column of the position.
         * @return A unique size_t hash value for the position.
         */
        size_t getPositionHash(int row, int col) const {
            return static_cast<size_t>(row) * 10000 + static_cast<size_t>(col);
        }

    public:
        /**
         * @brief Default constructor for GameMap.
         */
        GameMap();
        /**
         * @brief Destructor for GameMap.
         */
        ~GameMap();
        /**
         * @brief Loads the map layout from a specified file.
         *
         * @param filename The path to the map file.
         * @param playerX Reference to store the player's starting X coordinate.
         * @param playerY Reference to store the player's starting Y coordinate.
         * @return True if the map is loaded successfully, false otherwise.
         */
        bool loadFromFile(const std::string& filename, int& playerX, int& playerY);
        /**
         * @brief Normalizes a map file by ensuring all lines have the same width.
         *
         * @param filename The path to the map file to normalize.
         * @return True if normalization is successful, false otherwise.
         */
        static bool normalizeMapFile(const std::string& filename);
        /**
         * @brief Gets the character at a specific cell on the map.
         *
         * @param row The row of the cell.
         * @param col The column of the cell.
         * @return The character at the specified cell. Returns a space if out of bounds.
         */
        char getCell(int row, int col) const;
        /**
         * @brief Checks if a character can move to a specific cell.
         *
         * @param row The row of the cell.
         * @param col The column of the cell.
         * @return True if the cell is traversable, false otherwise.
         */
        bool canMoveTo(int row, int col) const;
        /**
         * @brief Gets the height of the map.
         *
         * @return The height of the map in cells.
         */
        int getHeight() const;
        /**
         * @brief Gets the width of the map.
         *
         * @return The width of the map in cells.
         */
        int getWidth() const;
        /**
         * @brief Checks if a given position is within the map boundaries.
         *
         * @param row The row of the position.
         * @param col The column of the position.
         * @return True if the position is valid, false otherwise.
         */
        bool isValidPosition(int row, int col) const;
        /**
         * @brief Checks if a given position is a tree space.
         *
         * @param row The row of the position.
         * @param col The column of the position.
         * @return True if the position is a tree space, false otherwise.
         */
        bool isTreeSpace(int row, int col) const;

        /**
         * @brief Checks if a given location is part of a monster spawn box.
         *
         * @param row The row of the location.
         * @param col The column of the location.
         * @return True if the location is part of a box, false otherwise.
         */
        bool isBoxLocation(int row, int col) const;
        /**
         * @brief Checks if the monster spawn box at a given location is ready.
         *
         * @param row The row of the location.
         * @param col The column of the location.
         * @return True if the box is ready, false otherwise.
         */
        bool isBoxReadyAt(int row, int col) const;
        /**
         * @brief Marks a monster spawn box at a given location as used and starts its cooldown.
         *
         * @param row The row of the box location.
         * @param col The column of the box location.
         */
        void useBox(int row, int col);
        /**
         * @brief Updates the status of all monster spawn boxes (e.g., cooldowns).
         */
        void updateBoxes();
        /**
         * @brief Gets the center coordinates of the monster spawn box at a given location.
         *
         * @param row The row of any part of the box.
         * @param col The column of any part of the box.
         * @return A pair of (row, col) for the box center. Returns (-1, -1) if no box found.
         */
        std::pair<int, int> getBoxCenter(int row, int col) const;
        /**
         * @brief Checks if a given location is inside any monster spawn box.
         *
         * @param row The row of the location.
         * @param col The column of the location.
         * @return True if inside a box, false otherwise.
         */
        bool isInsideBox(int row, int col) const;
        /**
         * @brief Gets the remaining cooldown time for the box at the given location.
         *
         * @param row The row of the box location.
         * @param col The column of the box location.
         * @return Remaining cooldown in seconds. 0 if ready or not found.
         */
        int getRemainingCooldown(int row, int col) const;
        /**
         * @brief Spawns a monster at a specified location.
         *
         * @param row The row to spawn the monster.
         * @param col The column to spawn the monster.
         * @param level The level of the monster to spawn (0 for default based on box).
         */
        void spawnMonster(int row, int col, int level = 0);
        /**
         * @brief Places a visual indicator on the map for a monster spawn box.
         *
         * @param row The row of the indicator.
         * @param col The column of the indicator.
         * @param isReady True if the box is ready, false if on cooldown.
         */
        void placeIndicator(int row, int col, bool isReady);
        /**
         * @brief Fills a monster spawn box area with a specified symbol.
         *
         * @param row The row of a corner of the box.
         * @param col The column of a corner of the box.
         * @param symbol The character symbol to fill the box with.
         */
        void fillBoxWithSymbols(int row, int col, char symbol);
        /**
         * @brief Displays a timer (e.g., cooldown) within a monster spawn box.
         *
         * @param row The row for displaying the timer (usually box center).
         * @param col The column for displaying the timer (usually box center).
         * @param seconds The number of seconds to display.
         */
        void displayTimer(int row, int col, int seconds);
        /**
         * @brief Retrieves information about the monster spawn box at a given location.
         *
         * @param row The row of the location.
         * @param col The column of the location.
         * @param info Reference to a BoxInfo struct to store the box details.
         * @return True if box information is found and retrieved, false otherwise.
         */
        bool getBoxInfo(int row, int col, BoxInfo& info) const;
        
        /**
         * @brief Initializes the cache for tree spaces on the map.
         */
        void initTreeCache();

        /**
         * @brief Checks if there is a monster at a specific location.
         *
         * @param row The row of the location.
         * @param col The column of the location.
         * @return True if a monster is present, false otherwise.
         */
        bool isMonsterAt(int row, int col) const;
        /**
         * @brief Gets a reference to the monster at a specific location.
         *
         * @param row The row of the monster.
         * @param col The column of the monster.
         * @return A reference to the MonsterCard at the location.
         * @throws std::out_of_range if no monster is at the location.
         */
        MonsterCard& getMonsterAt(int row, int col);
        /**
         * @brief Gets a constant reference to the monster at a specific location.
         *
         * @param row The row of the monster.
         * @param col The column of the monster.
         * @return A constant reference to the MonsterCard at the location.
         * @throws std::out_of_range if no monster is at the location.
         */
        const MonsterCard& getMonsterAt(int row, int col) const;
        /**
         * @brief Attacks a monster at a specific location.
         *
         * @param row The row of the monster.
         * @param col The column of the monster.
         * @param damage The amount of damage to inflict.
         * @param expGained Reference to store the experience gained if the monster is defeated.
         * @return True if the monster is defeated, false otherwise.
         */
        bool attackMonster(int row, int col, int damage, int& expGained);
        /**
         * @brief Finds the closest monster within a specified range of a location.
         *
         * @param startRow The starting row for the search.
         * @param startCol The starting column for the search.
         * @param range The maximum search range.
         * @param outRow Reference to store the row of the found monster.
         * @param outCol Reference to store the column of the found monster.
         * @return True if a monster is found in range, false otherwise.
         */
        bool findMonsterInRange(int startRow, int startCol, int range, int& outRow, int& outCol) const;
        
        /**
         * @brief Updates the state of all monsters on the map (e.g., movement, attacks).
         *
         * @param playerRow The player's current row.
         * @param playerCol The player's current column.
         * @param damageToPlayer Reference to accumulate damage dealt to the player by monsters.
         */
        void updateMonsters(int playerRow, int playerCol, int& damageToPlayer);
        /**
         * @brief Checks if a monster at a specific location can attack (e.g., cooldown).
         *
         * @param monsterRow The row of the monster.
         * @param monsterCol The column of the monster.
         * @return True if the monster can attack, false otherwise.
         */
        bool canMonsterAttack(int monsterRow, int monsterCol) const;
        /**
         * @brief Checks if the player is within a monster's attack range.
         *
         * @param monsterRow The monster's row.
         * @param monsterCol The monster's column.
         * @param playerRow The player's row.
         * @param playerCol The player's column.
         * @param range The attack range of the monster.
         * @return True if the player is in range, false otherwise.
         */
        bool isPlayerInRange(int monsterRow, int monsterCol, int playerRow, int playerCol, int range = 1) const;
        /**
         * @brief Moves a monster one step towards the player.
         *
         * @param monsterRow The monster's current row.
         * @param monsterCol The monster's current column.
         * @param playerRow The player's current row.
         * @param playerCol The player's current column.
         * @return True if the monster moved, false otherwise (e.g., blocked or already adjacent).
         */
        bool moveMonsterTowardsPlayer(int monsterRow, int monsterCol, int playerRow, int playerCol);
};

#endif

