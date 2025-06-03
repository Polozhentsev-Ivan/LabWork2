#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include <string>
#include "terminal_manager.h"
#include "game_map.h"
#include "player.h"
#include "viewport.h"

/**
 * @brief Handles rendering the game state to the terminal.
 *
 * This class is responsible for drawing the game map, player, viewport,
 * and other UI elements like player stats and monster information.
 */
class Renderer {
private:
    TerminalManager& terminal;            /**< Reference to the TerminalManager for terminal operations. */
    std::vector<std::string> buffer;    /**< Buffer to store the frame before drawing to the terminal. */
    std::string tempLine;               /**< Temporary string for line construction. */
    std::string tempSegment;            /**< Temporary string for segment construction. */
    int termWidth, termHeight;          /**< Dimensions of the terminal window. */
    
    /**
     * @brief Preallocates memory for internal buffers based on terminal size.
     */
    void preallocateBuffers();
    
    int targetedMonsterRow;             /**< Row of the currently targeted monster for display. */
    int targetedMonsterCol;             /**< Column of the currently targeted monster for display. */
    bool monsterTargeted;               /**< Flag indicating if a monster is currently targeted for display. */
    
public:
    /**
     * @brief Constructs a Renderer object.
     *
     * @param termManager Reference to the TerminalManager to be used for rendering.
     */
    Renderer(TerminalManager& termManager);
    /**
     * @brief Destructor for the Renderer class.
     */
    ~Renderer();
    /**
     * @brief Sets the size of the rendering area (terminal dimensions).
     *
     * @param width The width of the terminal.
     * @param height The height of the terminal.
     */
    void setSize(int width, int height);
    /**
     * @brief Gets the height of the rendering area.
     *
     * @return The height in characters.
     */
    int getHeight() const;
    /**
     * @brief Gets the width of the rendering area.
     *
     * @return The width in characters.
     */
    int getWidth() const;
    /**
     * @brief Draws the main game field, including the map, player, and viewport.
     *
     * @param map The GameMap object to render.
     * @param player The Player object to render.
     * @param viewport The Viewport object defining the visible area.
     */
    void drawField(const GameMap& map, const Player& player, const Viewport& viewport);
    
    /**
     * @brief Displays the player's statistics on the screen.
     *
     * @param player The Player object whose stats are to be displayed.
     */
    void showPlayerStats(const Player& player);
    /**
     * @brief Displays information about the currently targeted monster.
     *
     * @param map The GameMap object to retrieve monster information from.
     */
    void showTargetedMonsterInfo(const GameMap& map);
    /**
     * @brief Sets a monster at a specific location as the target for information display.
     *
     * @param row The row of the monster to target.
     * @param col The column of the monster to target.
     */
    void setTargetedMonster(int row, int col);
    /**
     * @brief Clears the currently targeted monster, so no monster info is displayed.
     */
    void clearTargetedMonster();
};

#endif // RENDERER_H