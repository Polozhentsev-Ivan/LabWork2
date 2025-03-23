#include "../../include/game/game_map.h"
#include <iostream>
#include <algorithm>
#include <chrono>

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
        if (!line.empty() && line.back() == '\r') {
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
            line[pos] = ' ';
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
    return ' ';
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
    if (!isValidPosition(row, col) || getCell(row, col) != ' ') {
        return;
    }
    
    mapData[row][col] = 'M';
    
    std::string monsterName = "Goblin";
    int health = 30 + (rand() % 20);
    int attack = 5 + (rand() % 3);
    int defense = 2 + (rand() % 2);
    int speed = 3 + (rand() % 2);
    
    MonsterCard monsterCard(
        monsterName, 
        "A wild monster", 
        health, 
        health, 
        attack, 
        defense, 
        speed, 
        Species::goblin, 
        1, 
        10, 
        5 
    );
    
    monsters[{row, col}] = monsterCard;
}

bool GameMap::isMonsterAt(int row, int col) const {
    return getCell(row, col) == 'M' && monsters.find({row, col}) != monsters.end();
}

MonsterCard& GameMap::getMonsterAt(int row, int col) {
    auto it = monsters.find({row, col});
    if (it == monsters.end()) {
        static MonsterCard defaultMonster;
        return defaultMonster;
    }
    return it->second;
}

const MonsterCard& GameMap::getMonsterAt(int row, int col) const {
    auto it = monsters.find({row, col});
    if (it == monsters.end()) {
        static const MonsterCard defaultMonster;
        return defaultMonster;
    }
    return it->second;
}

bool GameMap::attackMonster(int row, int col, int damage) {
    if (!isMonsterAt(row, col)) {
        return false;
    }
    
    MonsterCard& monster = getMonsterAt(row, col);
    int currentHealth = monster.getHealth();
    int newHealth = std::max(0, currentHealth - damage);
    monster.setHealth(newHealth);
    
    if (newHealth <= 0) {
        mapData[row][col] = ' ';
        monsters.erase({row, col});
        return true;
    }
    
    return false;
}

bool GameMap::findMonsterInRange(int startRow, int startCol, int range, int& outRow, int& outCol) const {
    for (int r = 1; r <= range; ++r) {
        for (int dy = -r; dy <= r; ++dy) {
            for (int dx = -r; dx <= r; ++dx) {
                if (std::max(std::abs(dx), std::abs(dy)) != r) {
                    continue;
                }
                
                int checkRow = startRow + dy;
                int checkCol = startCol + dx;
                
                if (isValidPosition(checkRow, checkCol) && isMonsterAt(checkRow, checkCol)) {
                    outRow = checkRow;
                    outCol = checkCol;
                    return true;
                }
            }
        }
    }
    
    return false;
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
        int startCol = box.leftCol + (box.width - 4) / 2;
        
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

void GameMap::updateMonsters(int playerRow, int playerCol, int& damageToPlayer) {
    damageToPlayer = 0;
    
    auto currentTime = std::chrono::steady_clock::now();
    
    for (auto it = monsters.begin(); it != monsters.end(); ++it) {
        int monsterRow = it->first.first;
        int monsterCol = it->first.second;
        
        if (canMonsterAttack(monsterRow, monsterCol)) {
            if (isPlayerInRange(monsterRow, monsterCol, playerRow, playerCol)) {
                MonsterCard& monster = it->second;
                int damage = monster.getAttack();
                damageToPlayer += damage;
                
                monsterLastAttackTime[getPositionHash(monsterRow, monsterCol)] = currentTime;
            }
        }
    }
}

bool GameMap::canMonsterAttack(int monsterRow, int monsterCol) const {
    auto posHash = getPositionHash(monsterRow, monsterCol);
    auto it = monsterLastAttackTime.find(posHash);
    
    if (it == monsterLastAttackTime.end()) {
        return true;
    }
    
    auto currentTime = std::chrono::steady_clock::now();
    auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - it->second).count();
    
    return elapsedTime >= 3000;
}

bool GameMap::isPlayerInRange(int monsterRow, int monsterCol, int playerRow, int playerCol, int range) const {
    int distance = std::max(std::abs(monsterRow - playerRow), std::abs(monsterCol - playerCol));
    return distance <= range;
}