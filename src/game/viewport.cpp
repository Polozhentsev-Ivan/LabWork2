#include "../../include/game/viewport.h"
#include <algorithm>

Viewport::Viewport(int viewportWidth, int viewportHeight, int margin)
    : x(0), y(0), width(viewportWidth), height(viewportHeight), scrollMargin(margin) {}

Viewport::~Viewport() {}

void Viewport::setPosition(int newX, int newY) {
    x = newX;
    y = newY;
}

void Viewport::getViewArea(int& outX, int& outY, int& outWidth, int& outHeight) const {
    outX = x;
    outY = y;
    outWidth = width;
    outHeight = height;
}

void Viewport::update(int playerX, int playerY, const GameMap& map) {
    // Кэшируем размеры карты для избежания повторных вычислений
    const int mapWidth = map.getWidth();
    const int mapHeight = map.getHeight();
    
    // Вычисляем новые координаты видимой области
    int newX = x;
    int newY = y;
    
    // Проверяем необходимость прокрутки по горизонтали
    if (playerX - x < scrollMargin) {
        newX = std::max(0, playerX - scrollMargin);
    } else if (playerX - x >= width - scrollMargin) {
        newX = std::min(mapWidth - width, playerX - width + scrollMargin);
    }
    
    // Проверяем необходимость прокрутки по вертикали
    if (playerY - y < scrollMargin) {
        newY = std::max(0, playerY - scrollMargin);
    } else if (playerY - y >= height - scrollMargin) {
        newY = std::min(mapHeight - height, playerY - height + scrollMargin);
    }
    
    // Обновляем координаты видимой области
    x = newX;
    y = newY;
}

void Viewport::setSize(int newWidth, int newHeight) {
    width = newWidth;
    height = newHeight;
}

bool Viewport::isVisible(int worldX, int worldY) const {
    return (worldX >= x && worldX < x + width && 
            worldY >= y && worldY < y + height);
}

void Viewport::worldToScreen(int worldX, int worldY, int& screenX, int& screenY) const {
    screenX = worldX - x;
    screenY = worldY - y;
}

void Viewport::screenToWorld(int screenX, int screenY, int& worldX, int& worldY) const {
    worldX = screenX + x;
    worldY = screenY + y;
} 