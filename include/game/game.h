#ifndef GAME_H
#define GAME_H

#include <string>
#include <iostream>
#include "terminal_manager.h"
#include "input.h"
#include "game_map.h"
#include "player.h"
#include "renderer.h"
#include "viewport.h"

class Game {
    private:
        TerminalManager terminal;
        Input input;
        GameMap map;
        Player player;
        Renderer renderer;
        Viewport viewport;

        bool gameRunning;
        
        int targetedMonsterRow;
        int targetedMonsterCol;
        bool targetedMonster;
        
        bool playerStatsChanged;
        int lastHealth;
        int lastMaxHealth;
        int lastAttack;
        int lastDefense;
        int lastSpeed;
        int lastLevel;
        int lastExperience;
        int lastExpToNextLevel;

        void updateBoxIndicators();
        void activateMonsterBox();
        void initAllBoxIndicators();
        
        void showPlayerStats();
        void showMonsterInfo();
        void clearMonsterInfo();
        void checkPlayerStats();

    public:
        Game();
        ~Game();
        bool init(const std::string& mapFile);
        void run();
        bool processInput();
        int getMoveDelay() const;
        int getTermHeight() const;
};

#endif
