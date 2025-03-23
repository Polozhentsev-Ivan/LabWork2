#ifndef PLAYER_H
#define PLAYER_H

#include <ctime>
#include "game_map.h"
#include "../card/player_card.h"

class Player {
    private:
        int x,y;
        int moveDelay;
        long long lastMoveTime;
        int attackRange; 
        PlayerCard card; 

        long long getCurrentTimeMicros() const;

    public:
        Player(int startX = 0, int startY = 0);
        ~Player();
        
        bool move(int dx, int dy, const GameMap& map);
        void getPosition(int& outX, int& outY) const;
        void setPosition(int newX, int newY);
        int getMoveDelay() const;
        void changeSpeed(int delta);
        
        bool attack(GameMap& map);
        void setAttackRange(int range);
        int getAttackRange() const;
        void takeDamage(int damage);
        
        PlayerCard& getCard();
        const PlayerCard& getCard() const;
        void setCard(const PlayerCard& newCard);
};

#endif // PLAYER_H
