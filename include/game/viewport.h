#ifndef VIEWPORT_H
#define VIEWPORT_H

#include "game_map.h"

class Viewport {
private:
    int x, y;
    int width, height;
    int scrollMargin;
    
public:
    Viewport(int viewportWidth = 0, int viewportHeight = 0, int margin = 3);
    ~Viewport();
    
    void setPosition(int newX, int newY);  
    void getViewArea(int& outX, int& outY, int& outWidth, int& outHeight) const;
    void update(int playerX, int playerY, const GameMap& map);
    void setSize(int newWidth, int newHeight);
    bool isVisible(int worldX, int worldY) const;
    void worldToScreen(int worldX, int worldY, int& screenX, int& screenY) const;
    void screenToWorld(int screenX, int screenY, int& worldX, int& worldY) const;
};

#endif // VIEWPORT_H 