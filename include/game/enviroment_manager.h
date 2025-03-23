#ifndef ENVIROMENT_MANAGER_H
#define ENVIROMENT_MANAGER_H

#include <vector>
#include <string>
#include <chrono>


class GameMap;

class TreeManager {
private:
    const std::vector<std::string>* mapData;
    std::vector<std::vector<bool>> treeSpaceCache;
    bool cacheInitialized;
    
    bool checkTreeSpace(int row, int col) const;
    
public:
    TreeManager();
    ~TreeManager();
    
    void setMapData(const std::vector<std::string>* map);
    bool isTreeSpace(int row, int col) const;
    void initCache();
    void updateCache(int row, int col);
    bool isCacheInitialized() const;
};

class MonsterBox {
private:
    struct Box {
        int topRow;
        int leftCol;
        int width;
        int height;
        bool isReady;
        std::chrono::steady_clock::time_point lastUseTime;
        int cooldownSeconds;
    };

    std::vector<Box> monsterBoxes;
    const std::vector<std::string>* mapData;

    bool isBoxCharacter(char c) const;
    bool detectBox(int row, int col, Box& box) const;

public:

    friend class GameMap;
    
    MonsterBox();
    ~MonsterBox();

    void setMapData(const std::vector<std::string>* map);
    void scanForBoxes();
    bool isBoxLocation(int row, int col) const;
    bool isBoxReadyAt(int row, int col) const;
    void useBox(int row, int col);
    void updateBoxes();
    std::pair<int, int> getBoxCenter(int row, int col) const;
    bool isInsideBox(int row, int col) const;
    int getRemainingCooldown(int row, int col) const;
    Box* getBoxAt(int row, int col) const;
};

#endif