#ifndef PLAYER_H
#define PLAYER_H

#include <ctime>
#include "game_map.h"

class Player {
    private:
        int x,y;
        int moveDelay; //микросекунды
        long long lastMoveTime;

        long long getCurrentTimeMicros() const;

    public:
        Player(int startX = 0, int startY = 0);
        ~Player();
        
        bool move(int dx, int dy, const GameMap& map);
        void getPosition(int& outX, int& outY) const;
        void setPosition(int newX, int newY);
        int getMoveDelay() const;
        void changeSpeed(int delta);
         

};

#endif // PLAYER_H
