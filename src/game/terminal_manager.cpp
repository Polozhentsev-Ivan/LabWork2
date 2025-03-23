#include "../../include/game/terminal_manager.h"

struct termios TerminalManager::oldTerminalSettings;

TerminalManager::TerminalManager() : rawModeEnabled(false) {
    terminalSize.ws_col = 0;
    terminalSize.ws_row = 0;
}

TerminalManager::~TerminalManager() {
    if (rawModeEnabled) {
        setRawMode(false);
    }
}

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

void TerminalManager::clearScreen() {
    std::cout << "\033[2J";
    std::cout << "\033[H";
}

void TerminalManager::moveCursor(int row, int col) {
    std::cout << "\033[" << row << ";" << col << "H";
}

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