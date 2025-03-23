#include "../include/game/game.h"
#include <string>
#include <cstdlib>
#include <ctime>

int main(int argc, char* argv[]) {
    std::string mapFile = "map_test.txt";
    bool devMode = false;
    
    // Обработка аргументов командной строки
    for (int i = 1; i < argc; i++) {
        std::string arg = argv[i];
        if (arg == "--dev" || arg == "-d") {
            devMode = true;
        } else {
            mapFile = arg;
        }
    }
    
    // Инициализация генератора случайных чисел (нужнр будет для генерации собираемых предметов, расчетов урона и т.д.)
    srand(time(nullptr));
    
    Game game;
    game.setDevMode(devMode);
    
    if (!game.init(mapFile, devMode)) {
        return 1;
    }
    
    game.run();
    
    return 0;
} 