#include "../../include/game/enviroment_manager.h"
#include <algorithm>

TreeManager::TreeManager() : mapData(nullptr), cacheInitialized(false) {}

TreeManager::~TreeManager() {}

void TreeManager::setMapData(const std::vector<std::string>* map) {
    mapData = map;
    cacheInitialized = false; // Сбрасываем кэш при смене данных карты
}

bool TreeManager::checkTreeSpace(int row, int col) const {
    if (!mapData || mapData->empty()) {
        return false;
    }
    
    // Проверяем, находится ли позиция в пределах карты и является ли клетка пробелом
    if (row < 0 || row >= static_cast<int>(mapData->size()) || 
        col < 0 || col >= static_cast<int>((*mapData)[row].size()) || 
        (*mapData)[row][col] != ' ') {
        return false;
    }
    
    bool hasLeftSlash = false;
    
    for (int c = col - 1; c >= std::max(0, col - 3); c--) {
        if ((*mapData)[row][c] == '/') {
            hasLeftSlash = true;
            break;
        } else if ((*mapData)[row][c] != ' ') {
            break;
        }
    }
    
    if (!hasLeftSlash) return false;
    
    for (int c = col + 1; c < std::min(static_cast<int>((*mapData)[row].size()), col + 4); c++) {
        if ((*mapData)[row][c] == '\\') {
            return true;
        } else if ((*mapData)[row][c] != ' ') {
            break;
        }
    }
    
    return false;
}

bool TreeManager::isTreeSpace(int row, int col) const {
    // Используем кэш, если он инициализирован и координаты в допустимом диапазоне
    if (cacheInitialized && 
        row >= 0 && row < static_cast<int>(treeSpaceCache.size()) &&
        col >= 0 && col < static_cast<int>(treeSpaceCache[row].size())) {
        return treeSpaceCache[row][col];
    }
    
    // Если кэш не инициализирован или координаты за пределами, проверяем напрямую
    return checkTreeSpace(row, col);
}

void TreeManager::initCache() {
    if (!mapData || mapData->empty()) {
        return;
    }
    
    // Очищаем и изменяем размер кэша
    treeSpaceCache.clear();
    treeSpaceCache.resize(mapData->size());
    
    // Заполняем кэш
    for (size_t i = 0; i < mapData->size(); i++) {
        treeSpaceCache[i].resize((*mapData)[i].size(), false);
        for (size_t j = 0; j < (*mapData)[i].size(); j++) {
            if ((*mapData)[i][j] == ' ') {
                // Временно отключаем кэш для корректного вычисления
                bool oldCacheState = cacheInitialized;
                cacheInitialized = false;
                treeSpaceCache[i][j] = checkTreeSpace(i, j);
                cacheInitialized = oldCacheState;
            }
        }
    }
    
    cacheInitialized = true;
}

void TreeManager::updateCache(int row, int col) {
    if (!cacheInitialized || !mapData || mapData->empty() ||
        row < 0 || row >= static_cast<int>(treeSpaceCache.size()) ||
        col < 0 || col >= static_cast<int>(treeSpaceCache[row].size())) {
        return;
    }
    
    // Временно отключаем кэш для корректного вычисления
    bool oldCacheState = cacheInitialized;
    cacheInitialized = false;
    
    // Обновляем кэш для указанной позиции
    treeSpaceCache[row][col] = checkTreeSpace(row, col);
    
    // Обновляем соседние клетки, которые могут быть затронуты
    for (int r = std::max(0, row - 1); 
         r <= std::min(static_cast<int>(treeSpaceCache.size()) - 1, row + 1); 
         r++) {
        for (int c = std::max(0, col - 3); 
             c <= std::min(static_cast<int>(treeSpaceCache[r].size()) - 1, col + 3); 
             c++) {
            if ((*mapData)[r][c] == ' ') {
                treeSpaceCache[r][c] = checkTreeSpace(r, c);
            }
        }
    }
    
    // Восстанавливаем состояние кэша
    cacheInitialized = oldCacheState;
}

bool TreeManager::isCacheInitialized() const {
    return cacheInitialized;
} 