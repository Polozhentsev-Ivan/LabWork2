#include "../../include/game/game.h"
#include <iostream>
#include <unistd.h>
#include <cstdlib>
#include <chrono>
#include <ctime>   // для time()

Game::Game() 
    : renderer(terminal), 
      devMode(false), 
      gameRunning(false) {}

Game::~Game() {}

bool Game::init(const std::string& mapFile, bool devModeEnabled) {
    devMode = devModeEnabled;
    
    // Установка режима разработчика для рендерера
    renderer.setDevMode(devMode);
    
    // Получение размеров терминала
    int termWidth, termHeight;
    if (!terminal.getTerminalSize(termWidth, termHeight)) {
        return false;
    }
    
    // Установка размеров для рендерера
    renderer.setSize(termWidth, termHeight);
    
    // Загрузка карты
    int playerX, playerY;
    if (!map.loadFromFile(mapFile, playerX, playerY)) {
        return false;
    }
    
    // Установка позиции игрока
    player.setPosition(playerX, playerY);
    
    // Инициализация области просмотра
    viewport.setSize(termWidth, renderer.getHeight());
    viewport.setPosition(playerX - termWidth / 2, playerY - renderer.getHeight() / 2);
    viewport.update(playerX, playerY, map);
    
    gameRunning = true;
    
    return true;
}

void Game::run() {
    // Включаем "сырой" режим терминала
    terminal.setRawMode(true);
    
    // Очищаем экран
    terminal.clearScreen();
    
    // Для оптимизации обновления коробок
    long long lastBoxUpdate = 0;
    auto getCurrentTime = []() -> long long {
        return std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::steady_clock::now().time_since_epoch()
        ).count();
    };
    
    // Основной игровой цикл
    while (gameRunning) {
        // Обрабатываем ввод
        if (!processInput()) {
            break;
        }
        
        // Текущее время
        long long currentTime = getCurrentTime();
        
        // Обновляем состояние коробок монстров и индикаторы только каждые 200 мс
        // Это делает обновление таймера более стабильным, так как оно не зависит от скорости передвижения игрока
        if (currentTime - lastBoxUpdate > 200) {
            map.updateBoxes();
            updateBoxIndicators();
            lastBoxUpdate = currentTime;
        }
        
        // Отображаем игровое поле
        renderer.drawField(map, player, viewport);
        
        // Задержка для управления скоростью игры
        usleep(player.getMoveDelay() / 2); // Делаем задержку меньше для более плавной анимации таймера
    }
    
    // Очищаем терминал и восстанавливаем его настройки
    terminal.cleanup(renderer.getHeight());
}

bool Game::processInput() {
    // Буфер для чтения символов
    char inputBuffer[32];
    
    // Пробуем прочитать доступные символы
    int bytesRead = input.readInput(inputBuffer, sizeof(inputBuffer));
    
    // Если нет данных, просто продолжаем игру
    if (bytesRead <= 0) {
        return true;
    }
    
    // Флаг для отслеживания нажатия клавиши 'e'
    bool eKeyPressed = false;
    
    // Обрабатываем прочитанные символы
    for (int i = 0; i < bytesRead; i++) {
        char ch = inputBuffer[i];
        
        // Обрабатываем ввод
        switch (ch) {
            case 'q': 
                gameRunning = false; // Выход из игры
                return false;
            case '+': 
                player.changeSpeed(1); 
                break;
            case '-': 
                player.changeSpeed(-1); 
                break;
            case 'e':
                // Отмечаем, что клавиша 'e' была нажата
                eKeyPressed = true;
                break;
            case 'w': 
                if (player.move(0, -1, map)) {
                    // Обновляем видимую область, если игрок двигался
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
    
    // Обрабатываем нажатие клавиши 'e' после всех перемещений игрока
    if (eKeyPressed) {
        activateMonsterBox();
        // Сразу обновляем состояние коробок после активации
        map.updateBoxes();
        updateBoxIndicators();
    }
    
    return true;
}

void Game::setDevMode(bool enabled) {
    devMode = enabled;
    renderer.setDevMode(enabled);
}

int Game::getMoveDelay() const {
    return player.getMoveDelay();
}

int Game::getTermHeight() const {
    return renderer.getHeight();
}

void Game::updateBoxIndicators() {
    // Получаем текущую видимую область
    int viewX, viewY, viewWidth, viewHeight;
    viewport.getViewArea(viewX, viewY, viewWidth, viewHeight);
    
    // Обновляем все коробки в видимой области
    for (int row = viewY; row < viewY + viewHeight; row++) {
        for (int col = viewX; col < viewX + viewWidth; col++) {
            // Проверяем, что мы не проверяем одну и ту же коробку несколько раз
            if (map.isBoxLocation(row, col)) {
                // Обновляем индикатор для текущей коробки
                bool isReady = map.isBoxReadyAt(row, col);
                map.placeIndicator(row, col, isReady);
                
                // Пропускаем оставшиеся клетки этой коробки
                BoxInfo boxInfo;
                if (map.getBoxInfo(row, col, boxInfo)) {
                    // Пропускаем оставшиеся клетки этой коробки
                    col = boxInfo.leftCol + boxInfo.width - 1;
                }
            }
        }
    }
}

void Game::initAllBoxIndicators() {
    // Сканируем всю карту на наличие коробок и инициализируем их индикаторы
    for (int row = 0; row < map.getHeight(); row++) {
        for (int col = 0; col < map.getWidth(); col++) {
            // Если нашли коробку и она не была обработана ранее
            if (map.isBoxLocation(row, col)) {
                bool isReady = map.isBoxReadyAt(row, col);
                map.placeIndicator(row, col, isReady);
                
                // Пропускаем оставшиеся клетки текущей коробки
                BoxInfo boxInfo;
                if (map.getBoxInfo(row, col, boxInfo)) {
                    col = boxInfo.leftCol + boxInfo.width - 1;
                }
            }
        }
    }
}

void Game::activateMonsterBox() {
    int playerX, playerY;
    player.getPosition(playerX, playerY);
    
    // Проверяем все соседние клетки вокруг игрока
    for (int y = playerY - 1; y <= playerY + 1; y++) {
        for (int x = playerX - 1; x <= playerX + 1; x++) {
            if (map.isBoxLocation(y, x) && map.isBoxReadyAt(y, x)) {
                // Активируем коробку и спавним монстров
                map.useBox(y, x);
                
                auto center = map.getBoxCenter(y, x);
                int centerY = center.first;
                int centerX = center.second;
                
                // Собираем все возможные позиции для спавна монстра
                std::vector<std::pair<int, int>> possiblePositions;
                
                // Ищем в радиусе от 3 до 1 клетки от центра
                for (int radius = 3; radius >= 1; radius--) {
                    for (int monsterY = centerY - radius; monsterY <= centerY + radius; monsterY++) {
                        for (int monsterX = centerX - radius; monsterX <= centerX + radius; monsterX++) {
                            // Не спавним монстра на игроке
                            if (monsterY == playerY && monsterX == playerX) {
                                continue;
                            }
                            
                            // Добавляем позицию, если клетка свободна
                            if (map.isValidPosition(monsterY, monsterX) && 
                                map.getCell(monsterY, monsterX) == ' ' &&
                                !map.isBoxLocation(monsterY, monsterX)) {
                                possiblePositions.push_back({monsterY, monsterX});
                            }
                        }
                    }
                }
                
                // Если нашли хотя бы одну позицию для спавна
                if (!possiblePositions.empty()) {
                    // Выбираем случайную позицию из списка
                    srand(static_cast<unsigned>(time(nullptr)));
                    int randomIndex = rand() % possiblePositions.size();
                    int monsterY = possiblePositions[randomIndex].first;
                    int monsterX = possiblePositions[randomIndex].second;
                    
                    map.spawnMonster(monsterY, monsterX);
                }
                
                // Обновляем индикатор состояния коробки
                map.placeIndicator(y, x, false);
                return;
            }
        }
    }
}