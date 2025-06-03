/**
 * @file game.cpp
 * @brief Реализация основного класса игры.
 */
#include "../../include/game/game.h"
#include <iostream>
#include <unistd.h>
#include <cstdlib>
#include <chrono>
#include <ctime>   // для time()
#include <cmath>

/**
 * @brief Конструктор класса Game.
 *
 * Инициализирует члены класса значениями по умолчанию.
 */
Game::Game() 
    : renderer(terminal), 
      gameRunning(false),
      targetedMonsterRow(-1),
      targetedMonsterCol(-1),
      targetedMonster(false),
      playerStatsChanged(true),  // Сначала отобразим статистику
      lastHealth(0),
      lastMaxHealth(0),
      lastAttack(0),
      lastDefense(0),
      lastSpeed(0),
      lastLevel(0),
      lastExperience(0),
      lastExpToNextLevel(0),
      finalWaveSpawned(false),
      finalWaveTimeSeconds(180), // 3 минуты (180 секунд)
      gameCompleted(false) {}

/**
 * @brief Деструктор класса Game.
 */
Game::~Game() {}

/**
 * @brief Инициализирует игру.
 *
 * Загружает карту, устанавливает размеры терминала и рендерера,
 * инициализирует позицию игрока и область просмотра.
 *
 * @param mapFile Путь к файлу карты.
 * @return True, если инициализация прошла успешно, false в противном случае.
 */
bool Game::init(const std::string& mapFile) {
    int termWidth, termHeight;
    if (!terminal.getTerminalSize(termWidth, termHeight)) {
        return false;
    }
    
    renderer.setSize(termWidth, termHeight);
    
    int playerX, playerY;
    if (!map.loadFromFile(mapFile, playerX, playerY)) {
        return false;
    }
    
    player.setPosition(playerX, playerY);
    
    viewport.setSize(termWidth, renderer.getHeight());
    viewport.setPosition(playerX - termWidth / 2, playerY - renderer.getHeight() / 2);
    viewport.update(playerX, playerY, map);
    
    const PlayerCard& card = player.getCard();
    lastHealth = card.getHealth();
    lastMaxHealth = card.getMaxHealth();
    lastAttack = card.getAttack();
    lastDefense = card.getDefense();
    lastSpeed = card.getSpeed();
    lastLevel = card.getLevel();
    lastExperience = card.getExperience();
    lastExpToNextLevel = card.getExperienceToNextLevel();
    
    gameRunning = true;
    
    return true;
}

/**
 * @brief Запускает основной игровой цикл.
 *
 * Обрабатывает ввод пользователя, обновляет состояние игры и отрисовывает игровой мир.
 */
void Game::run() {
    terminal.setRawMode(true);
    
    terminal.clearScreen();
    
    long long lastBoxUpdate = 0;
    long long lastMonsterUpdate = 0;
    auto getCurrentTime = []() -> long long {
        return std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::steady_clock::now().time_since_epoch()
        ).count();
    };
    
    gameStartTime = std::chrono::steady_clock::now(); // Запускаем таймер игры
    
    while (gameRunning) {
        // Проверяем, завершена ли игра
        checkGameCompletion();
        
        // Если игра завершена, показываем сообщение о завершении
        if (gameCompleted) {
            showGameCompletionMessage();
            break;
        }
        
        if (!processInput()) {
            break;
        }
        
        long long currentTime = getCurrentTime();
        
        int playerX, playerY;
        player.getPosition(playerX, playerY);
        
        if (currentTime - lastBoxUpdate > 200) {
            map.updateBoxes();
            updateBoxIndicators();
            lastBoxUpdate = currentTime;
        }
        
        // Проверяем, не пора ли запустить финальную волну
        if (!finalWaveSpawned) {
            auto currentTimePoint = std::chrono::steady_clock::now();
            auto elapsedSeconds = std::chrono::duration_cast<std::chrono::seconds>(currentTimePoint - gameStartTime).count();
            
            if (elapsedSeconds >= finalWaveTimeSeconds) {
                spawnFinalWave();
                finalWaveSpawned = true;
            }
        } else {
            // Обновляем движение монстров финальной волны
            updateFinalWaveMonsters();
        }
        
        if (currentTime - lastMonsterUpdate > 500) {
            int damageToPlayer = 0;
            map.updateMonsters(playerY, playerX, damageToPlayer);
            
            if (damageToPlayer > 0) {
                player.takeDamage(damageToPlayer);
                playerStatsChanged = true;
            }
            
            lastMonsterUpdate = currentTime;
        }
        
        checkPlayerStats();
        
        renderer.drawField(map, player, viewport);
        
        if (playerStatsChanged) {
            showPlayerStats();
            playerStatsChanged = false;
        }
        
        // Показываем таймер финальной волны
        showFinalWaveTimer();
        
        if (targetedMonster) {
            showMonsterInfo();
        }
        
        usleep(player.getMoveDelay() / 2);
    }
    
    terminal.cleanup(renderer.getHeight());
}

/**
 * @brief Обрабатывает ввод пользователя.
 *
 * Считывает символы из входного потока и выполняет соответствующие действия в игре.
 *
 * @return True, если игра должна продолжаться, false, если игра должна завершиться (например, по нажатию 'q').
 */
bool Game::processInput() {
    char inputBuffer[32];
    
    int bytesRead = input.readInput(inputBuffer, sizeof(inputBuffer));
    
    if (bytesRead <= 0) {
        return true;
    }
    
    bool eKeyPressed = false;
    bool fKeyPressed = false;
    
    for (int i = 0; i < bytesRead; i++) {
        char ch = inputBuffer[i];
        
        switch (ch) {
            case 'q': 
                gameRunning = false;
                return false;
            case '+': 
                player.changeSpeed(1);
                playerStatsChanged = true;
                break;
            case '-': 
                player.changeSpeed(-1);
                playerStatsChanged = true;
                break;
            case 'e':
                eKeyPressed = true;
                break;
            case 'f':
                fKeyPressed = true;
                break;
            case 'w': 
                if (player.move(0, -1, map)) {
                    int playerX, playerY;
                    player.getPosition(playerX, playerY);
                    viewport.update(playerX, playerY, map);
                }
                break;
            case 's': 
                if (player.move(0, 1, map)) {
                    int playerX, playerY;
                    player.getPosition(playerX, playerY);
                    viewport.update(playerX, playerY, map);
                }
                break;
            case 'a': 
                if (player.move(-1, 0, map)) {
                    int playerX, playerY;
                    player.getPosition(playerX, playerY);
                    viewport.update(playerX, playerY, map);
                }
                break;
            case 'd': 
                if (player.move(1, 0, map)) {
                    int playerX, playerY;
                    player.getPosition(playerX, playerY);
                    viewport.update(playerX, playerY, map);
                }
                break;
            default:
                break;
        }
    }
    
    if (eKeyPressed) {
        activateMonsterBox();
        map.updateBoxes();
        updateBoxIndicators();
    }
    
    if (fKeyPressed) {
        int playerX, playerY;
        player.getPosition(playerX, playerY);
        
        int targetRow, targetCol;
        if (map.findMonsterInRange(playerY, playerX, player.getAttackRange(), targetRow, targetCol)) {
            int damage = player.getCard().getAttack();
            int expGained = 0;
            bool killed = map.attackMonster(targetRow, targetCol, damage, expGained);
            
            if (!killed) {
                targetedMonsterRow = targetRow;
                targetedMonsterCol = targetCol;
                targetedMonster = true;
            } else {
                // Монстр убит, добавляем опыт игроку
                if (expGained > 0) {
                    player.getCard().addExperience(expGained);
                    playerStatsChanged = true;
                }
                targetedMonster = false;
                clearMonsterInfo();
            }
        }
    }
    
    return true;
}

/**
 * @brief Возвращает задержку перед следующим ходом игрока.
 *
 * @return Задержка в микросекундах.
 */
int Game::getMoveDelay() const {
    return player.getMoveDelay();
}

/**
 * @brief Возвращает высоту терминала.
 *
 * @return Высота терминала в строках.
 */
int Game::getTermHeight() const {
    return renderer.getHeight();
}

/**
 * @brief Обновляет индикаторы состояния ящиков монстров в видимой области.
 *
 * Обновляет символы на карте, отображающие готовность ящиков или таймер восстановления.
 */
void Game::updateBoxIndicators() {
    int viewX, viewY, viewWidth, viewHeight;
    viewport.getViewArea(viewX, viewY, viewWidth, viewHeight);
    
    for (int row = viewY; row < viewY + viewHeight; row++) {
        for (int col = viewX; col < viewX + viewWidth; col++) {
            if (map.isBoxLocation(row, col)) {
                bool isReady = map.isBoxReadyAt(row, col);
                map.placeIndicator(row, col, isReady);
                
                BoxInfo boxInfo;
                if (map.getBoxInfo(row, col, boxInfo)) {
                    col = boxInfo.leftCol + boxInfo.width - 1;
                }
            }
        }
    }
}

/**
 * @brief Инициализирует индикаторы состояния всех ящиков монстров на карте.
 *
 * Вызывается один раз при инициализации для первоначального отображения состояния ящиков.
 */
void Game::initAllBoxIndicators() {
    for (int row = 0; row < map.getHeight(); row++) {
        for (int col = 0; col < map.getWidth(); col++) {
            if (map.isBoxLocation(row, col)) {
                bool isReady = map.isBoxReadyAt(row, col);
                map.placeIndicator(row, col, isReady);
                
                BoxInfo boxInfo;
                if (map.getBoxInfo(row, col, boxInfo)) {
                    col = boxInfo.leftCol + boxInfo.width - 1;
                }
            }
        }
    }
}

/**
 * @brief Активирует ящик монстров, если игрок находится рядом с готовым ящиком.
 *
 * При активации ящик используется, и из него появляется монстр.
 */
void Game::activateMonsterBox() {
    int playerX, playerY;
    player.getPosition(playerX, playerY);
    
    for (int y = playerY - 1; y <= playerY + 1; y++) {
        for (int x = playerX - 1; x <= playerX + 1; x++) {
            if (map.isBoxLocation(y, x) && map.isBoxReadyAt(y, x)) {
                map.useBox(y, x);
                
                auto center = map.getBoxCenter(y, x);
                int centerY = center.first;
                int centerX = center.second;
                
                std::vector<std::pair<int, int>> possiblePositions;
                
                for (int radius = 3; radius >= 1; radius--) {
                    for (int monsterY = centerY - radius; monsterY <= centerY + radius; monsterY++) {
                        for (int monsterX = centerX - radius; monsterX <= centerX + radius; monsterX++) {
                            if (monsterY == playerY && monsterX == playerX) {
                                continue;
                            }
                            
                            if (map.isValidPosition(monsterY, monsterX) && 
                                map.getCell(monsterY, monsterX) == ' ' &&
                                !map.isBoxLocation(monsterY, monsterX)) {
                                possiblePositions.push_back({monsterY, monsterX});
                            }
                        }
                    }
                }
                
                if (!possiblePositions.empty()) {
                    srand(static_cast<unsigned>(time(nullptr)));
                    int randomIndex = rand() % possiblePositions.size();
                    int monsterY = possiblePositions[randomIndex].first;
                    int monsterX = possiblePositions[randomIndex].second;
                    
                    map.spawnMonster(monsterY, monsterX);
                }
                
                map.placeIndicator(y, x, false);
                return;
            }
        }
    }
}

/**
 * @brief Отображает статистику игрока в нижней части экрана.
 *
 * Показывает текущее здоровье, атаку, защиту, скорость, уровень и опыт игрока.
 */
void Game::showPlayerStats() {
    const PlayerCard& card = player.getCard();
    
    int width, height;
    terminal.getTerminalSize(width, height);
    
    int statsRow = height - 4; // Сдвигаем статистику на строку выше, чтобы освободить место для таймера
    
    int health = card.getHealth();
    int maxHealth = card.getMaxHealth();
    int attack = card.getAttack();
    int defense = card.getDefense();
    int speed = card.getSpeed();
    int level = card.getLevel();
    int experience = card.getExperience();
    int expToNextLevel = card.getExperienceToNextLevel();
    
    std::string statsInfo = "Player HP: " + std::to_string(health) + "/" + std::to_string(maxHealth) +
                           " | ATK: " + std::to_string(attack) +
                           " | DEF: " + std::to_string(defense) +
                           " | SPD: " + std::to_string(speed) +
                           " | LVL: " + std::to_string(level) +
                           " | EXP: " + std::to_string(experience) + "/" + std::to_string(expToNextLevel);
    
    terminal.moveCursor(statsRow, 1);
    std::cout << std::string(width, ' ');
    
    terminal.moveCursor(statsRow, 1);
    std::cout << statsInfo;
}

/**
 * @brief Отображает таймер до появления финальной волны монстров или сообщение о ее появлении.
 *
 * Таймер отображается в нижней части экрана.
 */
void Game::showFinalWaveTimer() {
    int width, height;
    terminal.getTerminalSize(width, height);
    
    int timerRow = height - 3;
    
    // Очищаем строку
    terminal.moveCursor(timerRow, 1);
    std::cout << std::string(width, ' ');
    
    // Если финальная волна уже появилась, показываем сообщение
    if (finalWaveSpawned) {
        terminal.moveCursor(timerRow, 1);
        std::cout << "ВНИМАНИЕ! Финальная волна монстров атакует!";
        return;
    }
    
    // Вычисляем оставшееся время
    auto currentTime = std::chrono::steady_clock::now();
    auto elapsedSeconds = std::chrono::duration_cast<std::chrono::seconds>(currentTime - gameStartTime).count();
    int remainingSeconds = finalWaveTimeSeconds - elapsedSeconds;
    
    if (remainingSeconds < 0) remainingSeconds = 0;
    
    int minutes = remainingSeconds / 60;
    int seconds = remainingSeconds % 60;
    
    std::string timerInfo = "До финальной волны монстров: ";
    timerInfo += (minutes < 10 ? "0" : "");
    timerInfo += std::to_string(minutes);
    timerInfo += ":";
    timerInfo += (seconds < 10 ? "0" : "");
    timerInfo += std::to_string(seconds);
    
    terminal.moveCursor(timerRow, 1);
    std::cout << timerInfo;
}

/**
 * @brief Отображает информацию о целевом монстре.
 *
 * Показывает имя, здоровье, атаку, защиту и уровень монстра.
 */
void Game::showMonsterInfo() {
    if (!targetedMonster || !map.isMonsterAt(targetedMonsterRow, targetedMonsterCol)) {
        targetedMonster = false;
        return;
    }
    
    const MonsterCard& monster = map.getMonsterAt(targetedMonsterRow, targetedMonsterCol);
    
    int width, height;
    terminal.getTerminalSize(width, height);
    
    int monsterInfoRow = height - 2;
    
    std::string name = monster.getName();
    int health = monster.getHealth();
    int maxHealth = monster.getMaxHealth();
    int attack = monster.getAttack();
    int defense = monster.getDefense();
    int level = monster.getLevel();
    
    std::string monsterInfo = "Monster: " + name +
                             " | HP: " + std::to_string(health) + "/" + std::to_string(maxHealth) +
                             " | ATK: " + std::to_string(attack) +
                             " | DEF: " + std::to_string(defense) +
                             " | LVL: " + std::to_string(level);
    
    terminal.moveCursor(monsterInfoRow, 1);
    std::cout << std::string(width, ' ');
    
    terminal.moveCursor(monsterInfoRow, 1);
    std::cout << monsterInfo;
}

/**
 * @brief Очищает информацию о монстре с экрана.
 */
void Game::clearMonsterInfo() {
    int width, height;
    terminal.getTerminalSize(width, height);
    
    int monsterInfoRow = height - 2;
    
    terminal.moveCursor(monsterInfoRow, 1);
    std::cout << std::string(width, ' ');
}

/**
 * @brief Запускает финальную волну монстров.
 *
 * Создает определенное количество сильных монстров вокруг игрока.
 */
void Game::spawnFinalWave() {
    // Получаем позицию игрока
    int playerX, playerY;
    player.getPosition(playerX, playerY);
    
    // Количество монстров в финальной волне
    const int numMonsters = 15;
    
    // Минимальное расстояние от игрока для появления монстров
    const int minDistance = 5;
    // Максимальное расстояние от игрока для появления монстров
    const int maxDistance = 15;
    
    // Создаем монстров вокруг игрока на определенном расстоянии
    for (int i = 0; i < numMonsters; i++) {
        // Пытаемся найти подходящую позицию для монстра
        for (int attempts = 0; attempts < 50; attempts++) {
            // Генерируем случайное расстояние от игрока
            int distance = minDistance + rand() % (maxDistance - minDistance + 1);
            
            // Генерируем случайный угол
            double angle = (rand() % 360) * 3.14159 / 180.0;
            
            // Вычисляем координаты монстра
            int monsterY = playerY + static_cast<int>(distance * sin(angle));
            int monsterX = playerX + static_cast<int>(distance * cos(angle));
            
            // Проверяем, что позиция валидна и на ней нет препятствий
            if (map.isValidPosition(monsterY, monsterX) && 
                map.getCell(monsterY, monsterX) == ' ' && 
                !map.isMonsterAt(monsterY, monsterX) && 
                !map.isBoxLocation(monsterY, monsterX)) {
                
                // Создаем монстра с более высоким уровнем для финальной волны
                map.spawnMonster(monsterY, monsterX, 3); // Уровень 3 - самый сильный
                break;
            }
        }
    }
    
    // Запоминаем время начала финальной волны
    finalWaveStartTime = std::chrono::steady_clock::now();
}

/**
 * @brief Обновляет позиции монстров финальной волны.
 *
 * Монстры финальной волны постоянно движутся в сторону игрока.
 */
void Game::updateFinalWaveMonsters() {
    static auto lastMoveTime = std::chrono::steady_clock::now();
    auto currentTime = std::chrono::steady_clock::now();
    
    // Обновляем позиции монстров каждые 500 мс
    if (std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - lastMoveTime).count() < 500) {
        return;
    }
    
    lastMoveTime = currentTime;
    
    // Получаем позицию игрока
    int playerX, playerY;
    player.getPosition(playerX, playerY);
    
    // Проходим по всей карте и ищем монстров
    for (int row = 0; row < map.getHeight(); row++) {
        for (int col = 0; col < map.getWidth(); col++) {
            if (map.isMonsterAt(row, col)) {
                // Перемещаем монстра в направлении игрока
                map.moveMonsterTowardsPlayer(row, col, playerY, playerX);
            }
        }
    }
}

/**
 * @brief Проверяет, изменились ли характеристики игрока, и устанавливает флаг playerStatsChanged.
 *
 * Если какие-либо характеристики игрока изменились с момента последней проверки,
 * устанавливает playerStatsChanged в true для последующего обновления отображения.
 */
void Game::checkPlayerStats() {
    const PlayerCard& card = player.getCard();
    
    if (lastHealth != card.getHealth() ||
        lastMaxHealth != card.getMaxHealth() ||
        lastAttack != card.getAttack() ||
        lastDefense != card.getDefense() ||
        lastSpeed != card.getSpeed() ||
        lastLevel != card.getLevel() ||
        lastExperience != card.getExperience() ||
        lastExpToNextLevel != card.getExperienceToNextLevel()) {
        
        lastHealth = card.getHealth();
        lastMaxHealth = card.getMaxHealth();
        lastAttack = card.getAttack();
        lastDefense = card.getDefense();
        lastSpeed = card.getSpeed();
        lastLevel = card.getLevel();
        lastExperience = card.getExperience();
        lastExpToNextLevel = card.getExperienceToNextLevel();
        
        playerStatsChanged = true;
    }
}

/**
 * @brief Проверяет, завершена ли игра.
 *
 * Игра считается завершенной, если финальная волна была запущена и на карте не осталось монстров.
 */
void Game::checkGameCompletion() {
    // Если игра уже завершена, ничего не делаем
    if (gameCompleted) {
        return;
    }
    
    // Если финальная волна еще не появилась, ничего не делаем
    if (!finalWaveSpawned) {
        return;
    }
    
    // Проверяем, остались ли монстры на карте
    bool monstersRemain = false;
    for (int row = 0; row < map.getHeight(); row++) {
        for (int col = 0; col < map.getWidth(); col++) {
            if (map.isMonsterAt(row, col)) {
                monstersRemain = true;
                break;
            }
        }
        if (monstersRemain) {
            break;
        }
    }
    
    // Если монстров не осталось, игра завершена
    if (!monstersRemain) {
        gameCompleted = true;
    }
}

/**
 * @brief Отображает сообщение о завершении игры.
 *
 * Сообщение выводится по центру экрана и предлагает нажать 'q' для выхода.
 */
void Game::showGameCompletionMessage() {
    if (!gameCompleted) {
        return;
    }
    
    int width, height;
    terminal.getTerminalSize(width, height);
    
    // Очищаем экран
    terminal.clearScreen();
    
    // Выводим сообщение о завершении игры
    terminal.moveCursor(height / 2 - 1, width / 2 - 15);
    std::cout << "=============================";
    
    terminal.moveCursor(height / 2, width / 2 - 15);
    std::cout << "Поздравляем! Вы прошли игру!";
    
    terminal.moveCursor(height / 2 + 1, width / 2 - 15);
    std::cout << "=============================";
    
    terminal.moveCursor(height / 2 + 3, width / 2 - 15);
    std::cout << "Нажмите 'q' для выхода";
    
    // Ожидаем нажатия клавиши 'q' для выхода
    while (true) {
        char inputBuffer[32];
        int bytesRead = input.readInput(inputBuffer, sizeof(inputBuffer));
        
        if (bytesRead > 0) {
            for (int i = 0; i < bytesRead; i++) {
                if (inputBuffer[i] == 'q') {
                    gameRunning = false;
                    return;
                }
            }
        }
        
        usleep(100000); // Небольшая задержка
    }
}