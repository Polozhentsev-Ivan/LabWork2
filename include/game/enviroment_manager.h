#ifndef TREE_MANAGER_H
#define TREE_MANAGER_H

#include <vector>
#include <string>


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

#endif // TREE_MANAGER_H 