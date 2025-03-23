#ifndef GAME_MAP_H
#define GAME_MAP_H

#include <vector>
#include <string>
#include <fstream>
#include "enviroment_manager.h"


class GameMap {
    private:
        std::vector<std::string> mapData;
        TreeManager treeManager;

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
        void initTreeCache();
};
#endif // GAME_MAP_H

