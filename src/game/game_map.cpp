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
    
    initTreeCache();
    
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
    
    if (target == ' ') {
        return true;
    }
    
    return (target != '#' && target != '|');
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