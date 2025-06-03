#ifndef ENVIROMENT_MANAGER_H
#define ENVIROMENT_MANAGER_H

#include <vector>
#include <string>
#include <chrono>


class GameMap;

/**
 * @brief Manages tree spaces on the game map.
 * 
 * This class is responsible for identifying and caching locations on the map
 * that are designated as tree spaces.
 */
class TreeManager {
private:
    const std::vector<std::string>* mapData; /**< Pointer to the raw map data. */
    std::vector<std::vector<bool>> treeSpaceCache; /**< Cache for storing tree space locations. */
    bool cacheInitialized; /**< Flag indicating if the cache has been initialized. */
    
    /**
     * @brief Checks if a specific location is a tree space based on map characters.
     *
     * @param row The row of the location.
     * @param col The column of the location.
     * @return True if the location is a tree space, false otherwise.
     */
    bool checkTreeSpace(int row, int col) const;
    
public:
    /**
     * @brief Default constructor for TreeManager.
     */
    TreeManager();
    /**
     * @brief Destructor for TreeManager.
     */
    ~TreeManager();
    
    /**
     * @brief Sets the map data for the TreeManager.
     *
     * @param map Pointer to the vector of strings representing the map.
     */
    /**
     * @brief Sets the map data for the MonsterBox.
     *
     * @param map Pointer to the vector of strings representing the map.
     */
    void setMapData(const std::vector<std::string>* map);
    /**
     * @brief Checks if a given location is a tree space using the cache.
     *
     * @param row The row of the location.
     * @param col The column of the location.
     * @return True if the location is a tree space, false otherwise.
     */
    bool isTreeSpace(int row, int col) const;
    /**
     * @brief Initializes the tree space cache based on the current map data.
     */
    void initCache();
    /**
     * @brief Updates the cache for a specific location.
     *
     * @param row The row of the location to update.
     * @param col The column of the location to update.
     */
    void updateCache(int row, int col);
    /**
     * @brief Checks if the tree space cache has been initialized.
     *
     * @return True if the cache is initialized, false otherwise.
     */
    bool isCacheInitialized() const;
};

/**
 * @brief Manages monster spawn boxes on the game map.
 * 
 * This class detects, tracks, and manages the cooldown of monster spawn boxes.
 */
class MonsterBox {
private:
    /**
     * @brief Structure representing a monster spawn box.
     */
    struct Box {
        int topRow; /**< The top row coordinate of the box. */
        int leftCol; /**< The leftmost column coordinate of the box. */
        int width; /**< The width of the box. */
        int height; /**< The height of the box. */
        bool isReady; /**< Flag indicating if the box is ready to spawn a monster. */
        std::chrono::steady_clock::time_point lastUseTime; /**< Timestamp of the last time the box was used. */
        int cooldownSeconds; /**< Cooldown duration in seconds before the box can be used again. */
    };

    std::vector<Box> monsterBoxes; /**< Vector storing all detected monster spawn boxes. */
    const std::vector<std::string>* mapData; /**< Pointer to the raw map data. */

    /**
     * @brief Checks if a character represents part of a monster box.
     *
     * @param c The character to check.
     * @return True if the character is a box character, false otherwise.
     */
    bool isBoxCharacter(char c) const;
    /**
     * @brief Detects a monster box starting from a given location.
     *
     * @param row The starting row for detection.
     * @param col The starting column for detection.
     * @param box Reference to a Box structure to store the detected box's details.
     * @return True if a box is successfully detected, false otherwise.
     */
    bool detectBox(int row, int col, Box& box) const;

public:

    friend class GameMap; /**< Allows GameMap to access MonsterBox private members. */
    
    /**
     * @brief Default constructor for MonsterBox.
     */
    MonsterBox();
    /**
     * @brief Destructor for MonsterBox.
     */
    ~MonsterBox();

    /**
     * @brief Sets the map data for the TreeManager.
     *
     * @param map Pointer to the vector of strings representing the map.
     */
    /**
     * @brief Sets the map data for the MonsterBox.
     *
     * @param map Pointer to the vector of strings representing the map.
     */
    void setMapData(const std::vector<std::string>* map);
    /**
     * @brief Scans the entire map for monster spawn boxes.
     */
    void scanForBoxes();
    /**
     * @brief Checks if a given location is part of any monster box.
     *
     * @param row The row of the location.
     * @param col The column of the location.
     * @return True if the location is part of a box, false otherwise.
     */
    bool isBoxLocation(int row, int col) const;
    /**
     * @brief Checks if the monster box at a given location is ready to be used.
     *
     * @param row The row of the location.
     * @param col The column of the location.
     * @return True if the box is ready, false otherwise.
     */
    bool isBoxReadyAt(int row, int col) const;
    /**
     * @brief Marks a monster box at a given location as used and starts its cooldown.
     *
     * @param row The row of the box location.
     * @param col The column of the box location.
     */
    void useBox(int row, int col);
    /**
     * @brief Updates the status of all monster boxes, checking cooldowns.
     */
    void updateBoxes();
    /**
     * @brief Gets the center coordinates of the monster box at a given location.
     *
     * @param row The row of any part of the box.
     * @param col The column of any part of the box.
     * @return A pair of integers representing the (row, col) of the box center.
     *         Returns (-1, -1) if no box is found at the location.
     */
    std::pair<int, int> getBoxCenter(int row, int col) const;
    /**
     * @brief Checks if a given location is inside any detected monster box.
     *
     * @param row The row of the location.
     * @param col The column of the location.
     * @return True if the location is inside a box, false otherwise.
     */
    bool isInsideBox(int row, int col) const;
    /**
     * @brief Gets the remaining cooldown time in seconds for the box at the given location.
     *
     * @param row The row of the box location.
     * @param col The column of the box location.
     * @return The remaining cooldown in seconds. Returns 0 if the box is ready or not found.
     */
    int getRemainingCooldown(int row, int col) const;
    /**
     * @brief Gets a pointer to the Box structure at the given location.
     *
     * @param row The row of the location.
     * @param col The column of the location.
     * @return A pointer to the Box if found, nullptr otherwise.
     */
    Box* getBoxAt(int row, int col) const;
};

#endif