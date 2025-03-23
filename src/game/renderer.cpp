#include "../../include/game/renderer.h"
#include <iostream>

Renderer::Renderer(TerminalManager& termManager)
    : terminal(termManager), termWidth(0), termHeight(0),
      targetedMonsterRow(-1), targetedMonsterCol(-1), monsterTargeted(false) {}

Renderer::~Renderer() {}

void Renderer::preallocateBuffers() {
    tempLine.reserve(termWidth + 10);
    tempSegment.reserve(termWidth + 10);
    
    buffer.resize(termHeight);
    for (auto& line : buffer) {
        line.reserve(termWidth + 10);
        line.resize(termWidth, ' ');
    }
}

void Renderer::setSize(int width, int height) {
    termWidth = width;
    termHeight = height;
    
    preallocateBuffers();
}

int Renderer::getHeight() const {
    return termHeight;
}

int Renderer::getWidth() const {
    return termWidth;
}

void Renderer::drawField(const GameMap& map, const Player& player, const Viewport& viewport) {
    int playerX, playerY;
    player.getPosition(playerX, playerY);
    
    int viewX, viewY, viewWidth, viewHeight;
    viewport.getViewArea(viewX, viewY, viewWidth, viewHeight);
    
    for (int i = 0; i < termHeight; i++) {
        tempLine.clear();
        bool lineChanged = false;
        int changeStart = -1;
        tempSegment.clear();
        
        for (int j = 0; j < termWidth; j++) {
            int worldRow = viewY + i;
            int worldCol = viewX + j;
            char displayChar = ' ';

            if (worldRow >= 0 && worldRow < map.getHeight() && 
                worldCol >= 0 && worldCol < map.getWidth()) {
                
                if (worldRow == playerY && worldCol == playerX) {
                    char cell = map.getCell(worldRow, worldCol);
                    if (cell == '\\' || cell == '/' || cell == '^') {
                        displayChar = cell;
                    } else if (cell == ' ' && map.isTreeSpace(worldRow, worldCol)) {
                        displayChar = cell;
                    } else {
                        displayChar = '@';
                    }
                } else {
                    displayChar = map.getCell(worldRow, worldCol);
                }
            }
            
            tempLine.push_back(displayChar);
            
            if (j < static_cast<int>(buffer[i].size()) && buffer[i][j] != displayChar) {
                if (changeStart == -1) {
                    changeStart = j;
                }
                tempSegment.push_back(displayChar);
                lineChanged = true;
            } else if (changeStart != -1) {
                terminal.moveCursor(i + 1, changeStart + 1);
                std::cout << tempSegment;
                changeStart = -1;
                tempSegment.clear();
            }
        }
        
        if (changeStart != -1) {
            terminal.moveCursor(i + 1, changeStart + 1);
            std::cout << tempSegment;
        } else if (lineChanged || buffer[i].size() != tempLine.size()) {
            terminal.moveCursor(i + 1, 1);
            std::cout << tempLine;
        }
        
        buffer[i] = tempLine;
    }
    
    std::cout.flush();
}

void Renderer::showPlayerStats(const Player& player) {
    const PlayerCard& card = player.getCard();
    
    int statsRow = termHeight + 1;
    
    int health = card.getHealth();
    int maxHealth = card.getMaxHealth();
    int attack = card.getAttack();
    int defense = card.getDefense();
    int speed = card.getSpeed();
    int level = card.getLevel();
    int experience = card.getExperience();
    int expToNextLevel = card.getExperienceToNextLevel();
    
    std::string statsInfo = "Player HP: " + std::to_string(health) + "/" + std::to_string(maxHealth) +
                           " | ATK: " + std::to_string(attack) +
                           " | DEF: " + std::to_string(defense) +
                           " | SPD: " + std::to_string(speed) +
                           " | LVL: " + std::to_string(level) +
                           " | EXP: " + std::to_string(experience) + "/" + std::to_string(expToNextLevel);
    
    terminal.moveCursor(statsRow, 1);
    std::cout << std::string(termWidth, ' ');
    
    terminal.moveCursor(statsRow, 1);
    std::cout << statsInfo;
}

void Renderer::showTargetedMonsterInfo(const GameMap& map) {
    if (!monsterTargeted || !map.isMonsterAt(targetedMonsterRow, targetedMonsterCol)) {
        clearTargetedMonster();
        return;
    }
    
    const MonsterCard& monster = map.getMonsterAt(targetedMonsterRow, targetedMonsterCol);
    
    int monsterInfoRow = termHeight + 2;
    
    std::string name = monster.getName();
    int health = monster.getHealth();
    int maxHealth = monster.getMaxHealth();
    int attack = monster.getAttack();
    int defense = monster.getDefense();
    int level = monster.getLevel();
    
    std::string monsterInfo = "Monster: " + name +
                             " | HP: " + std::to_string(health) + "/" + std::to_string(maxHealth) +
                             " | ATK: " + std::to_string(attack) +
                             " | DEF: " + std::to_string(defense) +
                             " | LVL: " + std::to_string(level);
    
    terminal.moveCursor(monsterInfoRow, 1);
    std::cout << std::string(termWidth, ' ');
    
    terminal.moveCursor(monsterInfoRow, 1);
    std::cout << monsterInfo;
}

void Renderer::clearTargetedMonster() {
    monsterTargeted = false;
    
    int monsterInfoRow = termHeight + 2;
    terminal.moveCursor(monsterInfoRow, 1);
    std::cout << std::string(termWidth, ' ');
}

void Renderer::setTargetedMonster(int row, int col) {
    targetedMonsterRow = row;
    targetedMonsterCol = col;
    monsterTargeted = true;
} 