#ifndef INPUT_H
#define INPUT_H

#include <unistd.h>

/**
 * @brief Handles user input from the terminal.
 *
 * This class provides methods for checking for available input and reading characters.
 */
class Input {
    private:
        static char inputBuffer; /**< Static buffer to store the last read character. */
    
    public:
        /**
         * @brief Default constructor for the Input class.
         */
        Input();
        /**
         * @brief Destructor for the Input class.
         */
        ~Input();
        /**
         * @brief Checks if there is any input available to be read.
         *
         * @return True if input is available, false otherwise.
         */
        bool hasInput() const;
        /**
         * @brief Reads and returns a single character from the input.
         *
         * @return The character read from input. Returns 0 if no input is available or on error.
         */
        char getChar() const;
        /**
         * @brief Reads a sequence of characters into a buffer.
         * 
         * @param buffer Pointer to the character buffer to store the input.
         * @param bufferSize The maximum number of characters to read into the buffer.
         * @return The number of characters read, or -1 on error.
         */
        int readInput(char* buffer, int bufferSize) const;
};

#endif // INPUT_H
