/**
 * @file game_map.cpp
 * @brief Implements the GameMap class methods for managing the game world.
 */
#include "../../include/game/game_map.h"
#include <iostream>
#include <algorithm>
#include <chrono>

/**
 * @brief Default constructor for the GameMap class.
 */
GameMap::GameMap() {}

/**
 * @brief Destructor for the GameMap class.
 */
GameMap::~GameMap() {}

/**
 * @brief Normalizes the map file by ensuring all lines have the same length.
 *
 * This function reads a map file, finds the maximum line length, and pads shorter
 * lines with spaces to match this length. It also removes carriage return characters.
 *
 * @param filename The path to the map file.
 * @return True if normalization was successful, false otherwise.
 */
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

/**
 * @brief Loads the game map from a file.
 *
 * Normalizes the map file first, then reads its content to populate the mapData.
 * It also identifies the player's starting position ('@') and initializes
 * tree and monster box managers.
 *
 * @param filename The path to the map file.
 * @param playerX Reference to store the player's starting X coordinate.
 * @param playerY Reference to store the player's starting Y coordinate.
 * @return True if the map was loaded successfully, false otherwise.
 */
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

/**
 * @brief Gets the character at a specific cell in the map.
 *
 * @param row The row index of the cell.
 * @param col The column index of the cell.
 * @return The character at the specified cell, or ' ' if the position is invalid.
 */
char GameMap::getCell(int row, int col) const {
    if (isValidPosition(row, col)) {
        return mapData[row][col];
    }
    return ' ';
}

/**
 * @brief Checks if a character can move to a specific cell.
 *
 * A cell is considered movable if it's within map bounds, is not a wall ('#', '|'),
 * not occupied by a monster ('M'), and not a box location.
 *
 * @param row The row index of the target cell.
 * @param col The column index of the target cell.
 * @return True if the character can move to the cell, false otherwise.
 */
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

/**
 * @brief Gets the height of the map.
 *
 * @return The number of rows in the map.
 */
int GameMap::getHeight() const {
    return static_cast<int>(mapData.size());
}

/**
 * @brief Gets the width of the map.
 *
 * @return The number of columns in the map (assumes all rows have the same length).
 */
int GameMap::getWidth() const {
    if (mapData.empty()) {
        return 0;
    }
    return static_cast<int>(mapData[0].size());
}

/**
 * @brief Checks if a given position is within the map boundaries.
 *
 * @param row The row index.
 * @param col The column index.
 * @return True if the position is valid, false otherwise.
 */
bool GameMap::isValidPosition(int row, int col) const {
    return (row >= 0 && row < getHeight() && 
            col >= 0 && col < static_cast<int>(mapData[row].size()));
}

/**
 * @brief Checks if the specified cell is part of a tree.
 *
 * @param row The row index.
 * @param col The column index.
 * @return True if the cell is part of a tree, false otherwise.
 */
bool GameMap::isTreeSpace(int row, int col) const {
    return treeManager.isTreeSpace(row, col);
}

/**
 * @brief Initializes the cache for tree locations.
 */
void GameMap::initTreeCache() {
    treeManager.initCache();
} 

/**
 * @brief Checks if the specified cell is a monster box location.
 *
 * @param row The row index.
 * @param col The column index.
 * @return True if the cell is a box location, false otherwise.
 */
bool GameMap::isBoxLocation(int row, int col) const {
    return monsterBoxManager.isBoxLocation(row, col);
}

/**
 * @brief Checks if a monster box at the specified location is ready to be used.
 *
 * @param row The row index of the box location.
 * @param col The column index of the box location.
 * @return True if the box is ready, false otherwise.
 */
bool GameMap::isBoxReadyAt(int row, int col) const {
    return monsterBoxManager.isBoxReadyAt(row, col);
}

/**
 * @brief Activates a monster box at the specified location, putting it on cooldown.
 *
 * @param row The row index of the box location.
 * @param col The column index of the box location.
 */
void GameMap::useBox(int row, int col) {
    monsterBoxManager.useBox(row, col);
}

/**
 * @brief Updates the state of all monster boxes (e.g., cooldowns).
 */
void GameMap::updateBoxes() {
    monsterBoxManager.updateBoxes();
}

/**
 * @brief Gets the center coordinates of the monster box containing the given cell.
 *
 * @param row The row index of a cell within or near a box.
 * @param col The column index of a cell within or near a box.
 * @return A pair of (row, col) for the box center, or (-1, -1) if not part of a box.
 */
std::pair<int, int> GameMap::getBoxCenter(int row, int col) const {
    return monsterBoxManager.getBoxCenter(row, col);
}

/**
 * @brief Checks if the specified cell is inside any monster box area.
 *
 * @param row The row index.
 * @param col The column index.
 * @return True if the cell is inside a box, false otherwise.
 */
bool GameMap::isInsideBox(int row, int col) const {
    return monsterBoxManager.isInsideBox(row, col);
}

/**
 * @brief Gets the remaining cooldown time for a monster box at the specified location.
 *
 * @param row The row index of the box location.
 * @param col The column index of the box location.
 * @return The remaining cooldown in seconds, or 0 if ready or not a box.
 */
int GameMap::getRemainingCooldown(int row, int col) const {
    return monsterBoxManager.getRemainingCooldown(row, col);
}

/**
 * @brief Spawns a monster at the specified location on the map.
 *
 * If the cell is valid and empty, a monster ('M') is placed. The monster's
 * type and stats are determined, potentially based on the provided level.
 *
 * @param row The row index for spawning.
 * @param col The column index for spawning.
 * @param level The level of the monster to spawn (0 or less for random level).
 */
void GameMap::spawnMonster(int row, int col, int level) {
    if (!isValidPosition(row, col) || getCell(row, col) != ' ') {
        return;
    }
    
    mapData[row][col] = 'M';
    
    // Если уровень не указан (0), генерируем случайный уровень (1-3)
    if (level <= 0) {
        level = 1 + (rand() % 3);
    }
    
    // Имя монстра в зависимости от вида
    std::string monsterName;
    Species species;
    int monsterType = rand() % 3;
    
    switch (monsterType) {
        case 0:
            monsterName = "Goblin";
            species = Species::goblin;
            break;
        case 1:
            monsterName = "Orc";
            species = Species::orc;
            break;
        case 2:
            monsterName = "Troll";
            species = Species::troll;
            break;
        default:
            monsterName = "Goblin";
            species = Species::goblin;
    }
    
    // Характеристики зависят от уровня
    int health = 20 + (level * 10) + (rand() % 20);
    int attack = 3 + (level * 2) + (rand() % 3);
    int defense = 1 + level + (rand() % 2);
    int speed = 2 + level + (rand() % 2);
    
    // Опыт и серебро зависят от уровня
    int experience = 150 * level;
    int silver = 3 * level + (rand() % 5);
    
    // Для финальной волны (уровень 3) увеличиваем характеристики
    if (level >= 3) {
        health += 20;
        attack += 3;
        defense += 2;
        experience += 15;
        silver += 10;
    }
    
    MonsterCard monsterCard(
        monsterName, 
        "A wild monster", 
        health, 
        health, 
        attack, 
        defense, 
        speed, 
        species, 
        level, 
        experience, 
        silver 
    );
    
    monsters[{row, col}] = monsterCard;
}

/**
 * @brief Checks if there is a monster at the specified cell.
 *
 * @param row The row index.
 * @param col The column index.
 * @return True if a monster is at the cell, false otherwise.
 */
bool GameMap::isMonsterAt(int row, int col) const {
    return getCell(row, col) == 'M' && monsters.find({row, col}) != monsters.end();
}

/**
 * @brief Gets a reference to the MonsterCard at the specified cell.
 *
 * @param row The row index.
 * @param col The column index.
 * @return A reference to the MonsterCard. If no monster is present, a static default MonsterCard is returned.
 */
MonsterCard& GameMap::getMonsterAt(int row, int col) {
    auto it = monsters.find({row, col});
    if (it == monsters.end()) {
        static MonsterCard defaultMonster;
        return defaultMonster;
    }
    return it->second;
}

/**
 * @brief Gets a constant reference to the MonsterCard at the specified cell.
 *
 * @param row The row index.
 * @param col The column index.
 * @return A constant reference to the MonsterCard. If no monster is present, a static default MonsterCard is returned.
 */
const MonsterCard& GameMap::getMonsterAt(int row, int col) const {
    auto it = monsters.find({row, col});
    if (it == monsters.end()) {
        static const MonsterCard defaultMonster;
        return defaultMonster;
    }
    return it->second;
}

/**
 * @brief Attacks a monster at the specified cell.
 *
 * Reduces the monster's health by the given damage. If the monster's health
 * drops to 0 or below, it is removed from the map, and experience is gained.
 *
 * @param row The row index of the monster.
 * @param col The column index of the monster.
 * @param damage The amount of damage to inflict.
 * @param expGained Reference to store the experience gained if the monster is defeated.
 * @return True if the monster was attacked (and potentially killed), false if no monster was at the location.
 */
bool GameMap::attackMonster(int row, int col, int damage, int& expGained) {
    if (!isMonsterAt(row, col)) {
        expGained = 0;
        return false;
    }
    
    MonsterCard& monster = getMonsterAt(row, col);
    int currentHealth = monster.getHealth();
    int newHealth = std::max(0, currentHealth - damage);
    monster.setHealth(newHealth);
    
    if (newHealth <= 0) {
        // Монстр убит, возвращаем опыт
        expGained = monster.getExperience();
        mapData[row][col] = ' ';
        monsters.erase({row, col});
        return true;
    }
    
    expGained = 0;
    return false;
}

/**
 * @brief Finds a monster within a specified range of a starting position.
 *
 * Searches in a square area defined by the range around the start coordinates.
 * Uses Manhattan distance to check if a cell is within the actual range.
 *
 * @param startRow The starting row for the search.
 * @param startCol The starting column for the search.
 * @param range The search range (Manhattan distance).
 * @param outRow Reference to store the row of the found monster.
 * @param outCol Reference to store the column of the found monster.
 * @return True if a monster is found, false otherwise.
 */
bool GameMap::findMonsterInRange(int startRow, int startCol, int range, int& outRow, int& outCol) const {
    // Проверяем всех монстров в пределах указанного диапазона (включая все клетки внутри диапазона)
    for (int dy = -range; dy <= range; ++dy) {
        for (int dx = -range; dx <= range; ++dx) {
            // Проверяем, что клетка находится в пределах диапазона (используем манхэттенское расстояние)
            if (std::abs(dx) + std::abs(dy) <= range) {
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

/**
 * @brief Places an indicator (timer or 'z') inside a monster box on the map.
 *
 * If the box is ready, fills it with 'z'. Otherwise, displays a cooldown timer.
 *
 * @param row Row index of a cell within the box.
 * @param col Column index of a cell within the box.
 * @param isReady True if the box is ready, false if on cooldown.
 */
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

/**
 * @brief Fills the interior of a monster box with a specified symbol.
 *
 * @param row Row index of a cell within the box.
 * @param col Column index of a cell within the box.
 * @param symbol The character to fill the box with.
 */
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

/**
 * @brief Displays a timer (MM:SS) inside a monster box.
 *
 * If the box is too small, it might display a single digit or be blank.
 *
 * @param row Row index of a cell within the box.
 * @param col Column index of a cell within the box.
 * @param seconds The total seconds to display.
 */
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

/**
 * @brief Retrieves information about the monster box at the given coordinates.
 *
 * @param row Row index of a cell within or near the box.
 * @param col Column index of a cell within or near the box.
 * @param info Reference to a BoxInfo struct to store the box details.
 * @return True if box information was found and retrieved, false otherwise.
 */
bool GameMap::getBoxInfo(int row, int col, BoxInfo& info) const {
    auto* box = monsterBoxManager.getBoxAt(row, col);
    if (!box) return false;
    
    info.topRow = box->topRow;
    info.leftCol = box->leftCol;
    info.width = box->width;
    info.height = box->height;
    
    return true;
}

/**
 * @brief Updates monster states, primarily handling their attacks on the player.
 *
 * Iterates through all monsters. If a monster can attack (based on cooldown)
 * and the player is in range, the monster attacks, and damage is added to damageToPlayer.
 *
 * @param playerRow The player's current row.
 * @param playerCol The player's current column.
 * @param damageToPlayer Reference to accumulate damage dealt to the player this update.
 */
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

/**
 * @brief Checks if a monster at the specified location can attack (based on attack cooldown).
 *
 * @param monsterRow The row of the monster.
 * @param monsterCol The column of the monster.
 * @return True if the monster can attack, false otherwise.
 */
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

/**
 * @brief Checks if the player is within a specified range of a monster.
 *
 * Uses Chebyshev distance (maximum of absolute differences in coordinates).
 *
 * @param monsterRow The monster's row.
 * @param monsterCol The monster's column.
 * @param playerRow The player's row.
 * @param playerCol The player's column.
 * @param range The attack range (defaults to 1).
 * @return True if the player is in range, false otherwise.
 */
bool GameMap::isPlayerInRange(int monsterRow, int monsterCol, int playerRow, int playerCol, int range) const {
    int distance = std::max(std::abs(monsterRow - playerRow), std::abs(monsterCol - playerCol));
    return distance <= range;
}

/**
 * @brief Moves a monster one step towards the player if possible.
 *
 * The monster will attempt to move to an adjacent cell that is closer to the player
 * and is a valid, unoccupied space. Prioritizes diagonal, then cardinal moves.
 *
 * @param monsterRow The current row of the monster.
 * @param monsterCol The current column of the monster.
 * @param playerRow The player's current row.
 * @param playerCol The player's current column.
 * @return True if the monster moved, false otherwise (e.g., no valid move, already in range, or no monster at location).
 */
bool GameMap::moveMonsterTowardsPlayer(int monsterRow, int monsterCol, int playerRow, int playerCol) {
    // Проверяем, что на указанной позиции есть монстр
    if (!isMonsterAt(monsterRow, monsterCol)) {
        return false;
    }
    
    // Если монстр уже рядом с игроком, не двигаем его
    if (isPlayerInRange(monsterRow, monsterCol, playerRow, playerCol)) {
        return false;
    }
    
    // Определяем направление движения к игроку
    int rowDiff = playerRow - monsterRow;
    int colDiff = playerCol - monsterCol;
    
    // Новые координаты монстра
    int newRow = monsterRow;
    int newCol = monsterCol;
    
    // Приоритет движения: сначала по вертикали, затем по горизонтали
    if (rowDiff != 0) {
        newRow += (rowDiff > 0) ? 1 : -1;
    } else if (colDiff != 0) {
        newCol += (colDiff > 0) ? 1 : -1;
    }
    
    // Проверяем, можно ли переместиться на новую позицию
    if (isValidPosition(newRow, newCol) && 
        getCell(newRow, newCol) == ' ' && 
        !isMonsterAt(newRow, newCol) && 
        !isBoxLocation(newRow, newCol)) {
        
        // Получаем монстра
        MonsterCard monster = monsters[{monsterRow, monsterCol}];
        
        // Удаляем монстра со старой позиции
        monsters.erase({monsterRow, monsterCol});
        
        // Обновляем символы на карте
        mapData[monsterRow][monsterCol] = ' ';
        mapData[newRow][newCol] = 'M';
        
        // Добавляем монстра на новую позицию
        monsters[{newRow, newCol}] = monster;
        
        return true;
    }
    
    return false;
}