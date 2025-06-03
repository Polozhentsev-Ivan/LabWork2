#ifndef VIEWPORT_H
#define VIEWPORT_H

#include "game_map.h"

/**
 * @brief Manages the visible portion of the game map.
 *
 * The viewport determines which part of the larger game world is currently
 * displayed on the screen. It supports scrolling to follow the player.
 */
class Viewport {
private:
    int x, y;             /**< Top-left x-coordinate of the viewport in world coordinates. */
    int width, height;    /**< Dimensions of the viewport in world coordinates. */
    int scrollMargin;     /**< Margin from the edge of the viewport before scrolling occurs. */
    
public:
    /**
     * @brief Constructs a Viewport object.
     *
     * @param viewportWidth The initial width of the viewport.
     * @param viewportHeight The initial height of the viewport.
     * @param margin The scroll margin.
     */
    Viewport(int viewportWidth = 0, int viewportHeight = 0, int margin = 3);
    /**
     * @brief Destructor for the Viewport class.
     */
    ~Viewport();
    
    /**
     * @brief Sets the top-left position of the viewport.
     *
     * @param newX The new x-coordinate in world space.
     * @param newY The new y-coordinate in world space.
     */
    void setPosition(int newX, int newY);  
    /**
     * @brief Gets the current view area of the viewport.
     *
     * @param outX Reference to store the viewport's top-left x-coordinate.
     * @param outY Reference to store the viewport's top-left y-coordinate.
     * @param outWidth Reference to store the viewport's width.
     * @param outHeight Reference to store the viewport's height.
     */
    void getViewArea(int& outX, int& outY, int& outWidth, int& outHeight) const;
    /**
     * @brief Updates the viewport's position based on the player's location and the map boundaries.
     *
     * Implements scrolling to keep the player within the viewport's scroll margin.
     * @param playerX The player's current x-coordinate in world space.
     * @param playerY The player's current y-coordinate in world space.
     * @param map The GameMap object, used to constrain viewport to map boundaries.
     */
    void update(int playerX, int playerY, const GameMap& map);
    /**
     * @brief Sets the size of the viewport.
     *
     * @param newWidth The new width of the viewport.
     * @param newHeight The new height of the viewport.
     */
    void setSize(int newWidth, int newHeight);
    /**
     * @brief Checks if a given world coordinate is currently visible within the viewport.
     *
     * @param worldX The x-coordinate in world space.
     * @param worldY The y-coordinate in world space.
     * @return True if the coordinate is visible, false otherwise.
     */
    bool isVisible(int worldX, int worldY) const;
    /**
     * @brief Converts world coordinates to screen coordinates relative to the viewport.
     *
     * @param worldX The x-coordinate in world space.
     * @param worldY The y-coordinate in world space.
     * @param screenX Reference to store the calculated screen x-coordinate.
     * @param screenY Reference to store the calculated screen y-coordinate.
     */
    void worldToScreen(int worldX, int worldY, int& screenX, int& screenY) const;
    /**
     * @brief Converts screen coordinates (relative to viewport) to world coordinates.
     *
     * @param screenX The x-coordinate on the screen (relative to viewport top-left).
     * @param screenY The y-coordinate on the screen (relative to viewport top-left).
     * @param worldX Reference to store the calculated world x-coordinate.
     * @param worldY Reference to store the calculated world y-coordinate.
     */
    void screenToWorld(int screenX, int screenY, int& worldX, int& worldY) const;
};

#endif // VIEWPORT_H