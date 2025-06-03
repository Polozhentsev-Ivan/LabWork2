/**
 * @file terminal_manager.cpp
 * @brief Реализация класса TerminalManager для управления терминалом.
 */
#include "../../include/game/terminal_manager.h"

/**
 * @brief Статическая переменная для хранения исходных настроек терминала.
 *
 * Используется для восстановления настроек терминала при выходе из raw-режима.
 */
struct termios TerminalManager::oldTerminalSettings;

/**
 * @brief Конструктор класса TerminalManager.
 *
 * Инициализирует размеры терминала нулевыми значениями.
 */
TerminalManager::TerminalManager() : rawModeEnabled(false) {
    terminalSize.ws_col = 0;
    terminalSize.ws_row = 0;
}

/**
 * @brief Деструктор класса TerminalManager.
 *
 * Если был включен raw-режим, отключает его для восстановления нормального поведения терминала.
 */
TerminalManager::~TerminalManager() {
    if (rawModeEnabled) {
        setRawMode(false);
    }
}

/**
 * @brief Включает или отключает raw-режим терминала.
 *
 * В raw-режиме ввод символов происходит немедленно, без ожидания нажатия Enter,
 * и символы не отображаются на экране.
 * @param enable true для включения raw-режима, false для отключения.
 */
void TerminalManager::setRawMode(bool enable) {
    static struct termios newSettings;
    
    if (enable && !rawModeEnabled) {
        tcgetattr(STDIN_FILENO, &oldTerminalSettings);
        
        newSettings = oldTerminalSettings;
        
        newSettings.c_lflag &= ~(ICANON | ECHO);
        
        newSettings.c_cc[VMIN] = 0;
        newSettings.c_cc[VTIME] = 0;
        
        tcsetattr(STDIN_FILENO, TCSANOW, &newSettings);
        
        rawModeEnabled = true;
    } 
    else if (!enable && rawModeEnabled) {
        tcsetattr(STDIN_FILENO, TCSANOW, &oldTerminalSettings);
        rawModeEnabled = false;
    }
}

/**
 * @brief Очищает экран терминала и перемещает курсор в левый верхний угол.
 */
void TerminalManager::clearScreen() {
    std::cout << "\033[2J";
    std::cout << "\033[H";
}

/**
 * @brief Перемещает курсор терминала в указанную позицию.
 *
 * @param row Номер строки (начиная с 1).
 * @param col Номер колонки (начиная с 1).
 */
void TerminalManager::moveCursor(int row, int col) {
    std::cout << "\033[" << row << ";" << col << "H";
}

/**
 * @brief Получает текущие размеры окна терминала.
 *
 * @param width Ссылка для сохранения ширины терминала.
 * @param height Ссылка для сохранения высоты терминала.
 * @return true, если размеры успешно получены, иначе false (используются значения по умолчанию).
 */
bool TerminalManager::getTerminalSize(int& width, int& height) {
    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &terminalSize) == -1) {
        std::cerr << "Предупреждение: не удалось получить размеры терминала, используются значения по умолчанию\n";
        width = 80;
        height = 24;
        return true;
    }
    
    width = terminalSize.ws_col;
    height = terminalSize.ws_row;
    return true;
}

/**
 * @brief Выполняет очистку терминала перед завершением программы.
 *
 * Очищает экран, перемещает курсор (если указано) и отключает raw-режим, если он был включен.
 * @param extraLines Количество дополнительных строк, на которые нужно переместить курсор вниз.
 */
void TerminalManager::cleanup(int extraLines) {
    clearScreen();
    
    if (extraLines > 0) {
        std::cout << "\033[" << extraLines << ";1H";
    }
    
    if (rawModeEnabled) {
        setRawMode(false);
    }
    
    std::cout.flush();
}