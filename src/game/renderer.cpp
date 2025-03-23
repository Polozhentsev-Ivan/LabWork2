#include "../../include/game/renderer.h"
#include <iostream>

Renderer::Renderer(TerminalManager& termManager, bool devModeEnabled)
    : terminal(termManager), termWidth(0), termHeight(0), devMode(devModeEnabled) {}

Renderer::~Renderer() {}

void Renderer::preallocateBuffers() {
    // Предварительно выделяем память для буферов
    tempLine.reserve(termWidth + 10);
    tempSegment.reserve(termWidth + 10);
    
    // Предварительно выделяем память для буфера экрана
    buffer.resize(termHeight);
    for (auto& line : buffer) {
        line.reserve(termWidth + 10);
        line.resize(termWidth, ' ');
    }
}

void Renderer::setSize(int width, int height) {
    termWidth = width;
    termHeight = height;
    
    // Уменьшаем высоту терминала для отладочной информации
    if (devMode) {
        termHeight -= 4; // Увеличиваем отступ для дополнительной информации
    }
    
    // Перевыделяем буферы
    preallocateBuffers();
}

int Renderer::getHeight() const {
    return termHeight + (devMode ? 4 : 0);
}

int Renderer::getWidth() const {
    return termWidth;
}

void Renderer::drawField(const GameMap& map, const Player& player, const Viewport& viewport) {
    int playerX, playerY;
    player.getPosition(playerX, playerY);
    
    int viewX, viewY, viewWidth, viewHeight;
    viewport.getViewArea(viewX, viewY, viewWidth, viewHeight);
    
    for (int i = 0; i < termHeight; i++) {
        tempLine.clear();
        bool lineChanged = false;
        int changeStart = -1;
        tempSegment.clear();
        
        for (int j = 0; j < termWidth; j++) {
            int worldRow = viewY + i;
            int worldCol = viewX + j;
            char displayChar = ' ';

            if (worldRow >= 0 && worldRow < map.getHeight() && 
                worldCol >= 0 && worldCol < map.getWidth()) {
                
                if (worldRow == playerY && worldCol == playerX) {
                    char cell = map.getCell(worldRow, worldCol);
                    // Проверяем, нужно ли скрыть персонажа
                    if (cell == '\\' || cell == '/' || cell == '^') {
                        displayChar = cell; // Скрываем персонажа за листвой
                    } else if (cell == ' ' && map.isTreeSpace(worldRow, worldCol)) {
                        displayChar = cell; // Скрываем персонажа за пробелом между / и обратным слешем
                    } else {
                        displayChar = '@'; // Отображаем персонажа
                    }
                } else {
                    displayChar = map.getCell(worldRow, worldCol);
                }
            }
            
            tempLine.push_back(displayChar);
            
            // Проверяем, изменился ли символ
            if (j < static_cast<int>(buffer[i].size()) && buffer[i][j] != displayChar) {
                if (changeStart == -1) {
                    changeStart = j;
                }
                tempSegment.push_back(displayChar);
                lineChanged = true;
            } else if (changeStart != -1) {
                // Обновляем измененный сегмент
                terminal.moveCursor(i + 1, changeStart + 1);
                std::cout << tempSegment;
                changeStart = -1;
                tempSegment.clear();
            }
        }
        
        // Проверяем, остался ли необработанный измененный сегмент
        if (changeStart != -1) {
            terminal.moveCursor(i + 1, changeStart + 1);
            std::cout << tempSegment;
        } else if (lineChanged || buffer[i].size() != tempLine.size()) {
            // Если строка изменилась, но не было обработано по сегментам, обновляем всю строку
            terminal.moveCursor(i + 1, 1);
            std::cout << tempLine;
        }
        
        buffer[i] = tempLine;
    }
    
    // Отображаем отладочную информацию, если включен режим разработчика
    if (devMode) {
        showDebugInfo(player, viewport, map);
    }
    
    std::cout.flush();
}

void Renderer::showDebugInfo(const Player& player, const Viewport& viewport, const GameMap& map) {
    int playerX, playerY;
    player.getPosition(playerX, playerY);
    
    int viewX, viewY, viewWidth, viewHeight;
    viewport.getViewArea(viewX, viewY, viewWidth, viewHeight);
    
    // Вывод информации о позиции персонажа и параметрах видимой области
    terminal.moveCursor(termHeight + 1, 1);
    std::string debugInfo = "Персонаж: (" + std::to_string(playerX) + ", " + std::to_string(playerY) + 
                           ") Задержка: " + std::to_string(player.getMoveDelay() / 1000) + "мс" +
                           " | Вид: (" + std::to_string(viewX) + ", " + std::to_string(viewY) + ")";
    std::cout << debugInfo << "                          ";
    
    // Информация о клетке под персонажем
    if (map.isValidPosition(playerY, playerX)) {
        char cellChar = map.getCell(playerY, playerX);
        terminal.moveCursor(termHeight + 2, 1);
        std::string cellInfo = "Клетка: '" + std::string(1, cellChar) + 
                              "' | isTreeSpace: " + (map.isTreeSpace(playerY, playerX) ? "да" : "нет");
        std::cout << cellInfo << "                          ";
    }
    
    // Информация о скорости
    terminal.moveCursor(termHeight + 3, 1);
    std::cout << "Скорость: " << (200000 - player.getMoveDelay()) / 10000 << "/20" << "                          ";
}

void Renderer::setDevMode(bool enabled) {
    devMode = enabled;
} 