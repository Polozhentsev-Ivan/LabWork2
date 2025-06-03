#include "../include/game/game.h"
#include <string>
#include <cstdlib>
#include <ctime>

/**
 * @brief The main function of the game.
 *
 * Initializes and runs the game. Accepts an optional command-line argument for the map file.
 * @param argc The number of command-line arguments.
 * @param argv An array of command-line arguments.
 * @return 0 if the game exits successfully, 1 otherwise.
 */
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