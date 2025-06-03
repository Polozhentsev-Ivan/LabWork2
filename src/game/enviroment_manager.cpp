/**
 * @file enviroment_manager.cpp
 * @brief Реализация классов для управления деревьями и ящиками монстров на карте.
 */

#include "../../include/game/enviroment_manager.h"
#include <algorithm>
#include <chrono>

/**
 * @brief Менеджер для управления пространствами деревьев на карте.
 */
TreeManager::TreeManager() : mapData(nullptr), cacheInitialized(false) {}

/**
 * @brief Деструктор для TreeManager.
 */
TreeManager::~TreeManager() {}

/**
 * @brief Устанавливает данные карты для менеджера деревьев.
 *
 * Сбрасывает кэш инициализации.
 *
 * @param map Указатель на вектор строк, представляющий карту.
 */
void TreeManager::setMapData(const std::vector<std::string>* map) {
    mapData = map;
    cacheInitialized = false;
}

/**
 * @brief Проверяет, является ли данная позиция пространством дерева.
 *
 * Пространство дерева определяется как пустая клетка (' '), окруженная
 * символами '/' слева и '\' справа в пределах определенного диапазона.
 *
 * @param row Строка для проверки.
 * @param col Столбец для проверки.
 * @return True, если позиция является пространством дерева, false в противном случае.
 */
bool TreeManager::checkTreeSpace(int row, int col) const {
    if (!mapData || mapData->empty()) {
        return false;
    }
    
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

/**
 * @brief Проверяет, является ли данная позиция пространством дерева, используя кэш, если он инициализирован.
 *
 * Если кэш инициализирован, возвращает значение из кэша. В противном случае выполняет проверку.
 *
 * @param row Строка для проверки.
 * @param col Столбец для проверки.
 * @return True, если позиция является пространством дерева, false в противном случае.
 */
bool TreeManager::isTreeSpace(int row, int col) const {
    if (cacheInitialized && 
        row >= 0 && row < static_cast<int>(treeSpaceCache.size()) &&
        col >= 0 && col < static_cast<int>(treeSpaceCache[row].size())) {
        return treeSpaceCache[row][col];
    }
    
    return checkTreeSpace(row, col);
}

/**
 * @brief Инициализирует кэш пространств деревьев.
 *
 * Сканирует всю карту и заполняет кэш информацией о пространствах деревьев.
 */
void TreeManager::initCache() {
    if (!mapData || mapData->empty()) {
        return;
    }
    
    treeSpaceCache.clear();
    treeSpaceCache.resize(mapData->size());
    
    for (size_t i = 0; i < mapData->size(); i++) {
        treeSpaceCache[i].resize((*mapData)[i].size(), false);
        for (size_t j = 0; j < (*mapData)[i].size(); j++) {
            if ((*mapData)[i][j] == ' ') {
                bool oldCacheState = cacheInitialized;
                cacheInitialized = false;
                treeSpaceCache[i][j] = checkTreeSpace(i, j);
                cacheInitialized = oldCacheState;
            }
        }
    }
    
    cacheInitialized = true;
}

/**
 * @brief Обновляет кэш пространств деревьев вокруг указанной позиции.
 *
 * Пересчитывает состояние кэша для указанной позиции и ее окрестностей.
 *
 * @param row Строка для обновления.
 * @param col Столбец для обновления.
 */
void TreeManager::updateCache(int row, int col) {
    if (!cacheInitialized || !mapData || mapData->empty() ||
        row < 0 || row >= static_cast<int>(treeSpaceCache.size()) ||
        col < 0 || col >= static_cast<int>(treeSpaceCache[row].size())) {
        return;
    }
    
    bool oldCacheState = cacheInitialized;
    cacheInitialized = false;
    
    treeSpaceCache[row][col] = checkTreeSpace(row, col);
    
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
    
    cacheInitialized = oldCacheState;
}

/**
 * @brief Проверяет, инициализирован ли кэш пространств деревьев.
 *
 * @return True, если кэш инициализирован, false в противном случае.
 */
bool TreeManager::isCacheInitialized() const {
    return cacheInitialized;
}

/**
 * @brief Менеджер для управления ящиками монстров на карте.
 */
MonsterBox::MonsterBox() : mapData(nullptr) {}

/**
 * @brief Деструктор для MonsterBox.
 */
MonsterBox::~MonsterBox() {}

/**
 * @brief Устанавливает данные карты для менеджера ящиков монстров.
 *
 * Очищает список обнаруженных ящиков монстров.
 *
 * @param map Указатель на вектор строк, представляющий карту.
 */
void MonsterBox::setMapData(const std::vector<std::string>* map) {
    mapData = map;
    monsterBoxes.clear();
}

/**
 * @brief Проверяет, является ли символ частью границы ящика монстра.
 *
 * @param c Символ для проверки.
 * @return True, если символ является частью границы ящика, false в противном случае.
 */
bool MonsterBox::isBoxCharacter(char c) const {
    return c == '+' || c == '-' || c == '|' || c == '.' || c == '=' || 
           c == '*' || c == '\'' || c == '_' || c == '[' || c == ']';
}

/**
 * @brief Пытается обнаружить ящик монстра, начиная с указанной позиции.
 *
 * Проверяет, начинается ли ящик монстра в данной позиции и определяет его размеры.
 *
 * @param row Строка начальной позиции.
 * @param col Столбец начальной позиции.
 * @param box Ссылка на структуру Box для сохранения информации об обнаруженном ящике.
 * @return True, если ящик монстра обнаружен, false в противном случае.
 */
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

/**
 * @brief Сканирует всю карту для обнаружения всех ящиков монстров.
 *
 * Заполняет внутренний список обнаруженных ящиков.
 */
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

/**
 * @brief Проверяет, находится ли данная позиция внутри какого-либо ящика монстра.
 *
 * @param row Строка для проверки.
 * @param col Столбец для проверки.
 * @return True, если позиция находится внутри ящика монстра, false в противном случае.
 */
bool MonsterBox::isBoxLocation(int row, int col) const {
    for (const auto& box : monsterBoxes) {
        if (row >= box.topRow && row < box.topRow + box.height &&
            col >= box.leftCol && col < box.leftCol + box.width) {
            return true;
        }
    }
    return false;
}

/**
 * @brief Проверяет, находится ли данная позиция строго внутри какого-либо ящика монстра (не на границе).
 *
 * @param row Строка для проверки.
 * @param col Столбец для проверки.
 * @return True, если позиция находится строго внутри ящика монстра, false в противном случае.
 */
bool MonsterBox::isInsideBox(int row, int col) const {
    for (const auto& box : monsterBoxes) {
        if (row > box.topRow && row < box.topRow + box.height - 1 &&
            col > box.leftCol && col < box.leftCol + box.width - 1) {
            return true;
        }
    }
    return false;
}

/**
 * @brief Проверяет, готов ли ящик монстра в указанной позиции к использованию.
 *
 * @param row Строка для проверки.
 * @param col Столбец для проверки.
 * @return True, если ящик готов, false в противном случае.
 */
bool MonsterBox::isBoxReadyAt(int row, int col) const {
    for (const auto& box : monsterBoxes) {
        if (row >= box.topRow && row < box.topRow + box.height &&
            col >= box.leftCol && col < box.leftCol + box.width) {
            return box.isReady;
        }
    }
    return false;
}

/**
 * @brief Использует ящик монстра в указанной позиции.
 *
 * Устанавливает флаг готовности ящика в false и обновляет время последнего использования.
 *
 * @param row Строка ящика.
 * @param col Столбец ящика.
 */
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

/**
 * @brief Обновляет состояние всех ящиков монстров.
 *
 * Проверяет время восстановления для ящиков, которые не готовы, и устанавливает их в состояние готовности, если время истекло.
 */
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

/**
 * @brief Возвращает центральные координаты ящика монстра, содержащего указанную позицию.
 *
 * @param row Строка внутри ящика.
 * @param col Столбец внутри ящика.
 * @return Пара (строка, столбец) центра ящика или (-1, -1), если позиция не в ящике.
 */
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

/**
 * @brief Возвращает оставшееся время восстановления для ящика монстра в указанной позиции.
 *
 * @param row Строка внутри ящика.
 * @param col Столбец внутри ящика.
 * @return Оставшееся время восстановления в секундах или 0, если ящик готов или позиция не в ящике.
 */
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

/**
 * @brief Возвращает указатель на структуру Box для ящика монстра в указанной позиции.
 *
 * @param row Строка внутри ящика.
 * @param col Столбец внутри ящика.
 * @return Указатель на Box или nullptr, если позиция не в ящике.
 */
MonsterBox::Box* MonsterBox::getBoxAt(int row, int col) const {
    for (auto& box : monsterBoxes) {
        if (row >= box.topRow && row < box.topRow + box.height &&
            col >= box.leftCol && col < box.leftCol + box.width) {
            return const_cast<Box*>(&box);
        }
    }
    return nullptr;
}