#include "../../include/game/game.h"
#include <iostream>
#include <unistd.h>
#include <cstdlib>

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
    
    // Основной игровой цикл
    while (gameRunning) {
        // Отображаем игровое поле
        renderer.drawField(map, player, viewport);
        
        // Обрабатываем ввод
        if (!processInput()) {
            break;
        }
        
        // Задержка для управления скоростью игры
        usleep(player.getMoveDelay());
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