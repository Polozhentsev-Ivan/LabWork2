#include "../../include/game/terminal_manager.h"

// Инициализация статической переменной
struct termios TerminalManager::oldTerminalSettings;

TerminalManager::TerminalManager() : rawModeEnabled(false) {
    // Инициализация структуры размеров терминала
    terminalSize.ws_col = 0;
    terminalSize.ws_row = 0;
}

TerminalManager::~TerminalManager() {
    // Если "сырой" режим всё еще включен, выключаем его
    if (rawModeEnabled) {
        setRawMode(false);
    }
}

void TerminalManager::setRawMode(bool enable) {
    static struct termios newSettings;
    
    if (enable && !rawModeEnabled) {
        // Сохраняем текущие настройки терминала
        tcgetattr(STDIN_FILENO, &oldTerminalSettings);
        
        // Копируем настройки в новую структуру
        newSettings = oldTerminalSettings;
        
        // Отключаем канонический режим и эхо
        newSettings.c_lflag &= ~(ICANON | ECHO);
        
        // Устанавливаем неблокирующий режим ввода
        newSettings.c_cc[VMIN] = 0;   // Неблокирующий ввод
        newSettings.c_cc[VTIME] = 0;  // Без таймаута
        
        // Применяем новые настройки
        tcsetattr(STDIN_FILENO, TCSANOW, &newSettings);
        
        rawModeEnabled = true;
    } 
    else if (!enable && rawModeEnabled) {
        // Восстанавливаем старые настройки
        tcsetattr(STDIN_FILENO, TCSANOW, &oldTerminalSettings);
        rawModeEnabled = false;
    }
}

void TerminalManager::clearScreen() {
    std::cout << "\033[2J"; // Очистка экрана
    std::cout << "\033[H";  // Перемещение курсора в верхний левый угол
}

void TerminalManager::moveCursor(int row, int col) {
    std::cout << "\033[" << row << ";" << col << "H";
}

bool TerminalManager::getTerminalSize(int& width, int& height) {
    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &terminalSize) == -1) {
        std::cerr << "Ошибка: не удалось получить размеры терминала\n";
        return false;
    }
    
    width = terminalSize.ws_col;
    height = terminalSize.ws_row;
    return true;
}

void TerminalManager::cleanup(int extraLines) {
    clearScreen();
    
    // Перемещаем курсор вниз на указанное количество строк
    if (extraLines > 0) {
        std::cout << "\033[" << extraLines << ";1H";
    }
    
    // Отключаем "сырой" режим, если он включен
    if (rawModeEnabled) {
        setRawMode(false);
    }
    
    std::cout.flush();
} 