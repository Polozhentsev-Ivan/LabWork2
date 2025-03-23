#include "../../include/game/game_map.h"
#include <iostream>
#include <algorithm>

GameMap::GameMap() {}

GameMap::~GameMap() {}

bool GameMap::normalizeMapFile(const std::string& filename) {
    std::ifstream inputFile(filename);
    if (!inputFile.is_open()){
        std::cerr << "Не удалось открыть файл: " << filename << std::endl;
        return false;
    }
    
    std::vector<std::string> lines;
    std::string line;
    
    while (std::getline(inputFile, line)) {
        if (!line.empty() && line.back() == '\r') { //Удаляем символ "\r" для корректной работы функции
            line.pop_back();
        }
        lines.push_back(line);
    }
    inputFile.close();
    
    size_t max_length = 0;
    for (const auto& str: lines) {
        if (str.size() > max_length) {
            max_length = str.size();
        }
    }
    
    for (auto& str: lines) {
        str.append(max_length - str.size(), ' ');
    }
    
    std::ofstream outputFile(filename);
    if (!outputFile.is_open()){
        std::cerr << "Не удалось открыть файл для записи: " << filename << std::endl;
        return false;
    }
    
    for (const auto& str: lines) {
        outputFile << str << std::endl;
    }
    outputFile.close();
    
    std::cout << "Файл карты успешно нормализован." << std::endl;
    return true;
}

bool GameMap::loadFromFile(const std::string& filename, int& playerX, int& playerY) {
    if (!normalizeMapFile(filename)) {
        return false;
    }
    
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Ошибка: не удалось открыть файл карты " << filename << std::endl;
        return false;
    }

    mapData.clear();
    std::string line;
    int y = 0;
    playerX = playerY = 0;
    
    while (std::getline(file, line)) {
        size_t pos = line.find('@');
        if (pos != std::string::npos) {
            playerX = static_cast<int>(pos);
            playerY = y;
            line[pos] = ' '; // Заменяем @ на пробел
        }
        mapData.push_back(line);
        y++;
    }
    file.close();
    
    treeManager.setMapData(&mapData);
    monsterBoxManager.setMapData(&mapData);
    
    initTreeCache();
    monsterBoxManager.scanForBoxes();
    
    return true;
}

char GameMap::getCell(int row, int col) const {
    if (isValidPosition(row, col)) {
        return mapData[row][col];
    }
    return ' '; // За пределами карты возвращаем пробел
}

bool GameMap::canMoveTo(int row, int col) const {
    if (!isValidPosition(row, col)) {
        return false;
    }
    
    char target = mapData[row][col];
    
    if (target == ' ' && !isBoxLocation(row, col)) {
        return true;
    }
    
    return (target != '#' && target != '|' && target != 'M' && !isBoxLocation(row, col));
}

int GameMap::getHeight() const {
    return static_cast<int>(mapData.size());
}

int GameMap::getWidth() const {
    if (mapData.empty()) {
        return 0;
    }
    return static_cast<int>(mapData[0].size());
}

bool GameMap::isValidPosition(int row, int col) const {
    return (row >= 0 && row < getHeight() && 
            col >= 0 && col < static_cast<int>(mapData[row].size()));
}

bool GameMap::isTreeSpace(int row, int col) const {
    return treeManager.isTreeSpace(row, col);
}

void GameMap::initTreeCache() {
    treeManager.initCache();
} 

bool GameMap::isBoxLocation(int row, int col) const {
    return monsterBoxManager.isBoxLocation(row, col);
}

bool GameMap::isBoxReadyAt(int row, int col) const {
    return monsterBoxManager.isBoxReadyAt(row, col);
}

void GameMap::useBox(int row, int col) {
    monsterBoxManager.useBox(row, col);
}

void GameMap::updateBoxes() {
    monsterBoxManager.updateBoxes();
}

std::pair<int, int> GameMap::getBoxCenter(int row, int col) const {
    return monsterBoxManager.getBoxCenter(row, col);
}

bool GameMap::isInsideBox(int row, int col) const {
    return monsterBoxManager.isInsideBox(row, col);
}

int GameMap::getRemainingCooldown(int row, int col) const {
    return monsterBoxManager.getRemainingCooldown(row, col);
}

void GameMap::spawnMonster(int row, int col) {
    if (isValidPosition(row, col) && getCell(row, col) == ' ') {
        mapData[row][col] = 'M';
    }
}

void GameMap::placeIndicator(int row, int col, bool isReady) {
    auto center = getBoxCenter(row, col);
    
    if (center.first == -1 || center.second == -1) {
        return;
    }
    
    if (isReady) {
        fillBoxWithSymbols(row, col, 'z');
    } else {
        int remaining = getRemainingCooldown(row, col);
        
        displayTimer(row, col, remaining);
    }
}

void GameMap::fillBoxWithSymbols(int row, int col, char symbol) {
    BoxInfo box;
    if (!getBoxInfo(row, col, box)) return;
    
    for (int r = box.topRow + 1; r < box.topRow + box.height - 1; r++) {
        for (int c = box.leftCol + 1; c < box.leftCol + box.width - 1; c++) {
            if (isValidPosition(r, c)) {
                mapData[r][c] = symbol;
            }
        }
    }
}

void GameMap::displayTimer(int row, int col, int seconds) {
    BoxInfo box;
    if (!getBoxInfo(row, col, box)) return;
    
    if (box.width < 5 || box.height < 3) {
        fillBoxWithSymbols(row, col, seconds > 0 ? (seconds <= 9 ? '0' + seconds : ' ') : ' ');
        return;
    }
    
    fillBoxWithSymbols(row, col, ' ');
    
    if (seconds <= 0) {
        return;
    }
    
    int minutes = seconds / 60;
    int remainingSeconds = seconds % 60;
    
    for (int r = box.topRow + 1; r < box.topRow + box.height - 1; r++) {
        int startCol = box.leftCol + (box.width - 4) / 2; // 4 символа для таймера (X:00)
        
        // Отображаем таймер в формате "1:00", где 1 - минуты, 00 - секунды
        if (isValidPosition(r, startCol)) {
            mapData[r][startCol] = '0' + minutes;
            if (isValidPosition(r, startCol + 1)) mapData[r][startCol + 1] = ':';
            if (isValidPosition(r, startCol + 2)) mapData[r][startCol + 2] = '0' + (remainingSeconds / 10);
            if (isValidPosition(r, startCol + 3)) mapData[r][startCol + 3] = '0' + (remainingSeconds % 10);
        }
    }
}

bool GameMap::getBoxInfo(int row, int col, BoxInfo& info) const {
    auto* box = monsterBoxManager.getBoxAt(row, col);
    if (!box) return false;
    
    info.topRow = box->topRow;
    info.leftCol = box->leftCol;
    info.width = box->width;
    info.height = box->height;
    
    return true;
}