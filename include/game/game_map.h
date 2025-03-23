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
        std::map<std::pair<int, int>, MonsterCard> monsters;
        std::unordered_map<size_t, std::chrono::steady_clock::time_point> monsterLastAttackTime;

        size_t getPositionHash(int row, int col) const {
            return static_cast<size_t>(row) * 10000 + static_cast<size_t>(col);
        }

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

        bool isMonsterAt(int row, int col) const;
        MonsterCard& getMonsterAt(int row, int col);
        const MonsterCard& getMonsterAt(int row, int col) const;
        bool attackMonster(int row, int col, int damage);
        bool findMonsterInRange(int startRow, int startCol, int range, int& outRow, int& outCol) const;
        
        void updateMonsters(int playerRow, int playerCol, int& damageToPlayer);
        bool canMonsterAttack(int monsterRow, int monsterCol) const;
        bool isPlayerInRange(int monsterRow, int monsterCol, int playerRow, int playerCol, int range = 1) const;
};

#endif

