#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include <string>
#include "terminal_manager.h"
#include "game_map.h"
#include "player.h"
#include "viewport.h"

class Renderer {
private:
    TerminalManager& terminal;
    std::vector<std::string> buffer;
    std::string tempLine;
    std::string tempSegment;
    int termWidth, termHeight;
    bool devMode;
    
    void preallocateBuffers();
    
public:
    Renderer(TerminalManager& termManager, bool devModeEnabled = false);
    ~Renderer();
    void setSize(int width, int height);
    int getHeight() const;
    int getWidth() const;
    void drawField(const GameMap& map, const Player& player, const Viewport& viewport);
    void showDebugInfo(const Player& player, const Viewport& viewport, const GameMap& map);
    void setDevMode(bool enabled);
};

#endif // RENDERER_H 