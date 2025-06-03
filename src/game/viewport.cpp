/**
 * @file viewport.cpp
 * @brief Реализация класса Viewport для управления областью просмотра (камерой) в игре.
 */
#include "../../include/game/viewport.h"
#include <algorithm>

/**
 * @brief Конструктор класса Viewport.
 *
 * @param viewportWidth Ширина области просмотра.
 * @param viewportHeight Высота области просмотра.
 * @param margin Отступ от края области просмотра, при достижении которого начинается скроллинг.
 */
Viewport::Viewport(int viewportWidth, int viewportHeight, int margin)
    : x(0), y(0), width(viewportWidth), height(viewportHeight), scrollMargin(margin) {}

/**
 * @brief Деструктор класса Viewport.
 */
Viewport::~Viewport() {}

/**
 * @brief Устанавливает позицию левого верхнего угла области просмотра.
 *
 * @param newX Новая координата X.
 * @param newY Новая координата Y.
 */
void Viewport::setPosition(int newX, int newY) {
    x = newX;
    y = newY;
}

/**
 * @brief Получает текущую позицию и размеры области просмотра.
 *
 * @param outX Ссылка для сохранения координаты X левого верхнего угла.
 * @param outY Ссылка для сохранения координаты Y левого верхнего угла.
 * @param outWidth Ссылка для сохранения ширины области просмотра.
 * @param outHeight Ссылка для сохранения высоты области просмотра.
 */
void Viewport::getViewArea(int& outX, int& outY, int& outWidth, int& outHeight) const {
    outX = x;
    outY = y;
    outWidth = width;
    outHeight = height;
}

/**
 * @brief Обновляет позицию области просмотра на основе позиции игрока и границ карты.
 *
 * Реализует скроллинг камеры, когда игрок приближается к краю области просмотра.
 * @param playerX Координата X игрока.
 * @param playerY Координата Y игрока.
 * @param map Игровая карта для получения ее размеров.
 */
void Viewport::update(int playerX, int playerY, const GameMap& map) {
    const int mapWidth = map.getWidth();
    const int mapHeight = map.getHeight();
    
    int newX = x;
    int newY = y;
    
    if (playerX - x < scrollMargin) {
        newX = std::max(0, playerX - scrollMargin);
    } else if (playerX - x >= width - scrollMargin) {
        newX = std::min(mapWidth - width, playerX - width + scrollMargin);
    }
    
    if (playerY - y < scrollMargin) {
        newY = std::max(0, playerY - scrollMargin);
    } else if (playerY - y >= height - scrollMargin) {
        newY = std::min(mapHeight - height, playerY - height + scrollMargin);
    }
    
    x = newX;
    y = newY;
}

/**
 * @brief Устанавливает новые размеры области просмотра.
 *
 * @param newWidth Новая ширина.
 * @param newHeight Новая высота.
 */
void Viewport::setSize(int newWidth, int newHeight) {
    width = newWidth;
    height = newHeight;
}

/**
 * @brief Проверяет, находится ли указанная мировая координата в пределах видимой области.
 *
 * @param worldX Мировая координата X.
 * @param worldY Мировая координата Y.
 * @return true, если координата видима, иначе false.
 */
bool Viewport::isVisible(int worldX, int worldY) const {
    return (worldX >= x && worldX < x + width && 
            worldY >= y && worldY < y + height);
}

/**
 * @brief Преобразует мировые координаты в экранные (относительно области просмотра).
 *
 * @param worldX Мировая координата X.
 * @param worldY Мировая координата Y.
 * @param screenX Ссылка для сохранения экранной координаты X.
 * @param screenY Ссылка для сохранения экранной координаты Y.
 */
void Viewport::worldToScreen(int worldX, int worldY, int& screenX, int& screenY) const {
    screenX = worldX - x;
    screenY = worldY - y;
}

/**
 * @brief Преобразует экранные координаты (относительно области просмотра) в мировые.
 *
 * @param screenX Экранная координата X.
 * @param screenY Экранная координата Y.
 * @param worldX Ссылка для сохранения мировой координаты X.
 * @param worldY Ссылка для сохранения мировой координаты Y.
 */
void Viewport::screenToWorld(int screenX, int screenY, int& worldX, int& worldY) const {
    worldX = screenX + x;
    worldY = screenY + y;
}