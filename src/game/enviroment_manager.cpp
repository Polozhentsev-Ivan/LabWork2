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

MonsterBox::MonsterBox() : mapData(nullptr) {}

MonsterBox::~MonsterBox() {}

void MonsterBox::setMapData(const std::vector<std::string>* map) {
    mapData = map;
    monsterBoxes.clear();
}

bool MonsterBox::isBoxCharacter(char c) const {
    return c == '+' || c == '-' || c == '|' || c == '.' || c == '=' || 
           c == '*' || c == '\'' || c == '_' || c == '[' || c == ']';
}

bool MonsterBox::detectBox(int row, int col, Box& box) const {
    if (!mapData || mapData->empty() || row < 0 || row >= static_cast<int>(mapData->size()) ||
        col < 0 || col >= static_cast<int>((*mapData)[row].size())) {
        return false;
    }

    char topLeft = (*mapData)[row][col];
    if (!isBoxCharacter(topLeft)) {
        return false;
    }

    int width = 0;
    int height = 0;

    int r = row;
    int c = col;

    while (c < static_cast<int>((*mapData)[r].size()) && isBoxCharacter((*mapData)[r][c])) {
        c++;
        width++;
    }

    if (width < 5) return false;

    c = col;
    while (r < static_cast<int>(mapData->size()) && 
           c < static_cast<int>((*mapData)[r].size()) && 
           isBoxCharacter((*mapData)[r][c])) {
        r++;
        height++;
    }

    if (height < 3) return false;

    box.topRow = row;
    box.leftCol = col;
    box.width = width;
    box.height = height;
    box.isReady = true;
    box.lastUseTime = std::chrono::steady_clock::now() - std::chrono::seconds(100); 
    box.cooldownSeconds = 60;

    return true;
}

void MonsterBox::scanForBoxes() {
    if (!mapData || mapData->empty()) {
        return;
    }

    monsterBoxes.clear();

    for (int r = 0; r < static_cast<int>(mapData->size()); r++) {
        for (int c = 0; c < static_cast<int>((*mapData)[r].size()); c++) {
            Box box;
            if (detectBox(r, c, box)) {
                monsterBoxes.push_back(box);
                c += box.width - 1;
            }
        }
    }
}

bool MonsterBox::isBoxLocation(int row, int col) const {
    for (const auto& box : monsterBoxes) {
        if (row >= box.topRow && row < box.topRow + box.height &&
            col >= box.leftCol && col < box.leftCol + box.width) {
            return true;
        }
    }
    return false;
}

bool MonsterBox::isInsideBox(int row, int col) const {
    for (const auto& box : monsterBoxes) {
        if (row > box.topRow && row < box.topRow + box.height - 1 &&
            col > box.leftCol && col < box.leftCol + box.width - 1) {
            return true;
        }
    }
    return false;
}

bool MonsterBox::isBoxReadyAt(int row, int col) const {
    for (const auto& box : monsterBoxes) {
        if (row >= box.topRow && row < box.topRow + box.height &&
            col >= box.leftCol && col < box.leftCol + box.width) {
            return box.isReady;
        }
    }
    return false;
}

void MonsterBox::useBox(int row, int col) {
    for (auto& box : monsterBoxes) {
        if (row >= box.topRow && row < box.topRow + box.height &&
            col >= box.leftCol && col < box.leftCol + box.width) {
            box.isReady = false;
            box.lastUseTime = std::chrono::steady_clock::now();
            return;
        }
    }
}

void MonsterBox::updateBoxes() {
    auto currentTime = std::chrono::steady_clock::now();
    
    for (auto& box : monsterBoxes) {
        if (!box.isReady) {
            auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(
                currentTime - box.lastUseTime).count();
                
            if (elapsed >= box.cooldownSeconds) {
                box.isReady = true;
            }
        }
    }
}

std::pair<int, int> MonsterBox::getBoxCenter(int row, int col) const {
    for (const auto& box : monsterBoxes) {
        if (row >= box.topRow && row < box.topRow + box.height &&
            col >= box.leftCol && col < box.leftCol + box.width) {
            
            int centerRow = box.topRow + box.height / 2;
            int centerCol = box.leftCol + box.width / 2;
            
            return {centerRow, centerCol};
        }
    }
    
    return {-1, -1};
}

int MonsterBox::getRemainingCooldown(int row, int col) const {
    for (const auto& box : monsterBoxes) {
        if (row >= box.topRow && row < box.topRow + box.height &&
            col >= box.leftCol && col < box.leftCol + box.width) {
            
            if (box.isReady) {
                return 0;
            }
            
            auto currentTime = std::chrono::steady_clock::now();
            auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(
                currentTime - box.lastUseTime).count();
            
            int remaining = box.cooldownSeconds - elapsed;
            return remaining > 0 ? remaining : 0;
        }
    }
    
    return 0;
}

MonsterBox::Box* MonsterBox::getBoxAt(int row, int col) const {
    for (auto& box : monsterBoxes) {
        if (row >= box.topRow && row < box.topRow + box.height &&
            col >= box.leftCol && col < box.leftCol + box.width) {
            return const_cast<Box*>(&box);
        }
    }
    return nullptr;
}