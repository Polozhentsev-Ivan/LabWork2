#include "../../include/game/input.h"

char Input::inputBuffer = 0;

Input::Input() {}

Input::~Input() {}

bool Input::hasInput() const {
    if (inputBuffer != 0) {
        return true;
    }
    
    char ch;
    ssize_t bytesRead = read(STDIN_FILENO, &ch, 1);
    
    if (bytesRead > 0) {
        inputBuffer = ch;
        return true;
    }
    
    return false;
}

char Input::getChar() const {
    if (inputBuffer != 0) {
        char tmp = inputBuffer;
        inputBuffer = 0;
        return tmp;
    }
    
    char ch = 0;
    if (read(STDIN_FILENO, &ch, 1) == 1) {
        return ch;
    }
    
    return 0;
}

int Input::readInput(char* buffer, int bufferSize) const {
    if (inputBuffer != 0 && bufferSize > 0) {
        buffer[0] = inputBuffer;
        inputBuffer = 0;
        
        if (bufferSize > 1) {
            ssize_t bytesRead = read(STDIN_FILENO, buffer + 1, bufferSize - 1);
            return (bytesRead > 0) ? bytesRead + 1 : 1;
        }
        return 1;
    }
    
    ssize_t bytesRead = read(STDIN_FILENO, buffer, bufferSize);
    return bytesRead > 0 ? bytesRead : 0;
} 