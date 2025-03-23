#include "../include/game/game.h"
#include <string>
#include <cstdlib>
#include <ctime>

int main(int argc, char* argv[]) {
    std::string mapFile = "map_test.txt";
    
    if (argc > 1) {
        mapFile = argv[1];
    }
    
    srand(time(nullptr));
    
    Game game;
    
    if (!game.init(mapFile)) {
        return 1;
    }
    
    game.run();
    
    return 0;
} 