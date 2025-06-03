#ifndef TERMINAL_MANAGER_H
#define TERMINAL_MANAGER_H

#include <iostream>
#include <termios.h>
#include <unistd.h>
#include <sys/ioctl.h>

/**
 * @brief Manages terminal settings and operations.
 *
 * This class provides functionalities to switch between raw and canonical terminal modes,
 * clear the screen, move the cursor, and get terminal dimensions.
 */
class TerminalManager {
private:
    static struct termios oldTerminalSettings; /**< Stores the original terminal settings to restore them on exit. */
    struct winsize terminalSize;               /**< Stores the current dimensions of the terminal window. */
    bool rawModeEnabled;                       /**< Flag indicating whether raw mode is currently enabled. */

public:
    /**
     * @brief Constructs a TerminalManager object.
     *
     * Initializes terminal settings and attempts to get the initial terminal size.
     */
    TerminalManager();
    /**
     * @brief Destructor for the TerminalManager class.
     *
     * Restores original terminal settings if raw mode was enabled.
     */
    ~TerminalManager();

    /**
     * @brief Enables or disables raw mode for the terminal.
     *
     * @param enable True to enable raw mode, false to disable and restore canonical mode.
     */
    void setRawMode(bool enable);
    /**
     * @brief Clears the terminal screen.
     */
    void clearScreen();
    /**
     * @brief Moves the terminal cursor to a specified row and column.
     *
     * @param row The target row (1-indexed).
     * @param col The target column (1-indexed).
     */
    void moveCursor(int row, int col);
    /**
     * @brief Gets the current size of the terminal window.
     *
     * @param width Reference to an integer to store the terminal width.
     * @param height Reference to an integer to store the terminal height.
     * @return True if the size was successfully retrieved, false otherwise.
     */
    bool getTerminalSize(int& width, int& height);
    /**
     * @brief Performs cleanup operations, such as restoring terminal settings and clearing lines.
     *
     * @param extraLines Number of extra lines to clear at the bottom of the screen.
     */
    void cleanup(int extraLines = 0);
};

#endif // TERMINAL_MANAGER_H