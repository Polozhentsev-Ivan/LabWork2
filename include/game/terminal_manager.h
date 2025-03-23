#ifndef TERMINAL_MANAGER_H
#define TERMINAL_MANAGER_H

#include <iostream>
#include <termios.h>
#include <unistd.h>
#include <sys/ioctl.h>

class TerminalManager {
private:
    static struct termios oldTerminalSettings;
    struct winsize terminalSize;
    bool rawModeEnabled;

public:
    TerminalManager();
    ~TerminalManager();

    void setRawMode(bool enable);
    void clearScreen();
    void moveCursor(int row, int col);
    bool getTerminalSize(int& width, int& height);
    void cleanup(int extraLines = 0);
};

#endif // TERMINAL_MANAGER_H 