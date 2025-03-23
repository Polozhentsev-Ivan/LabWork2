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
    
    void preallocateBuffers();
    
    int targetedMonsterRow;
    int targetedMonsterCol;
    bool monsterTargeted;
    
public:
    Renderer(TerminalManager& termManager);
    ~Renderer();
    void setSize(int width, int height);
    int getHeight() const;
    int getWidth() const;
    void drawField(const GameMap& map, const Player& player, const Viewport& viewport);
    
    void showPlayerStats(const Player& player);
    void showTargetedMonsterInfo(const GameMap& map);
    void setTargetedMonster(int row, int col);
    void clearTargetedMonster();
};

#endif // RENDERER_H 