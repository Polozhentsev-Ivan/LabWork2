#ifndef INPUT_H
#define INPUT_H

#include <unistd.h>

class Input {
    private:
        static char inputBuffer;
    
    public:
        Input();
        ~Input();
        bool hasInput() const;
        char getChar() const;
        int readInput(char* buffer, int bufferSize) const;
};

#endif // INPUT_H
