#ifndef GAME_MAP_H
#define GAME_MAP_H

#include <vector>
#include <string>
#include <fstream>
#include "../game/enviroment_manager.h"

struct BoxInfo {
    int topRow;
    int leftCol;
    int width;
    int height;
};

class GameMap {
    private:
        std::vector<std::string> mapData;
        TreeManager treeManager;
        MonsterBox monsterBoxManager;

    public:
        GameMap();
        ~GameMap();
        bool loadFromFile(const std::string& filename, int& playerX, int& playerY);
        static bool normalizeMapFile(const std::string& filename);
        char getCell(int row, int col) const;
        bool canMoveTo(int row, int col) const;
        int getHeight() const;
        int getWidth() const;
        bool isValidPosition(int row, int col) const;
        bool isTreeSpace(int row, int col) const;

        bool isBoxLocation(int row, int col) const;
        bool isBoxReadyAt(int row, int col) const;
        void useBox(int row, int col);
        void updateBoxes();
        std::pair<int, int> getBoxCenter(int row, int col) const;
        bool isInsideBox(int row, int col) const;
        int getRemainingCooldown(int row, int col) const;
        void spawnMonster(int row, int col);
        void placeIndicator(int row, int col, bool isReady);
        void fillBoxWithSymbols(int row, int col, char symbol);
        void displayTimer(int row, int col, int seconds);
        bool getBoxInfo(int row, int col, BoxInfo& info) const;
        
        void initTreeCache();
};

#endif // GAME_MAP_H

