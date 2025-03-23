#ifndef GAME_H
#define GAME_H

#include <string>
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

        bool devMode;
        bool gameRunning;

        void updateBoxIndicators();
        void activateMonsterBox();
        void initAllBoxIndicators();

    public:
        Game();
        ~Game();
        bool init(const std::string& mapFile, bool devModeEnabled = false);
        void run();
        bool processInput();
        void setDevMode(bool enabled);
        int getMoveDelay() const;
        int getTermHeight() const;
};

#endif // GAME_H
