#include "../../include/game/game.h"
#include <iostream>
#include <unistd.h>
#include <cstdlib>
#include <chrono>
#include <ctime>   // для time()

Game::Game() 
    : renderer(terminal), 
      gameRunning(false),
      targetedMonsterRow(-1),
      targetedMonsterCol(-1),
      targetedMonster(false),
      playerStatsChanged(true),  // Сначала отобразим статистику
      lastHealth(0),
      lastMaxHealth(0),
      lastAttack(0),
      lastDefense(0),
      lastSpeed(0),
      lastLevel(0),
      lastExperience(0),
      lastExpToNextLevel(0) {}

Game::~Game() {}

bool Game::init(const std::string& mapFile) {
    int termWidth, termHeight;
    if (!terminal.getTerminalSize(termWidth, termHeight)) {
        return false;
    }
    
    renderer.setSize(termWidth, termHeight);
    
    int playerX, playerY;
    if (!map.loadFromFile(mapFile, playerX, playerY)) {
        return false;
    }
    
    player.setPosition(playerX, playerY);
    
    viewport.setSize(termWidth, renderer.getHeight());
    viewport.setPosition(playerX - termWidth / 2, playerY - renderer.getHeight() / 2);
    viewport.update(playerX, playerY, map);
    
    const PlayerCard& card = player.getCard();
    lastHealth = card.getHealth();
    lastMaxHealth = card.getMaxHealth();
    lastAttack = card.getAttack();
    lastDefense = card.getDefense();
    lastSpeed = card.getSpeed();
    lastLevel = card.getLevel();
    lastExperience = card.getExperience();
    lastExpToNextLevel = card.getExperienceToNextLevel();
    
    gameRunning = true;
    
    return true;
}

void Game::run() {
    terminal.setRawMode(true);
    
    terminal.clearScreen();
    
    long long lastBoxUpdate = 0;
    long long lastMonsterUpdate = 0;
    auto getCurrentTime = []() -> long long {
        return std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::steady_clock::now().time_since_epoch()
        ).count();
    };
    
    while (gameRunning) {
        if (!processInput()) {
            break;
        }
        
        long long currentTime = getCurrentTime();
        
        int playerX, playerY;
        player.getPosition(playerX, playerY);
        
        if (currentTime - lastBoxUpdate > 200) {
            map.updateBoxes();
            updateBoxIndicators();
            lastBoxUpdate = currentTime;
        }
        
        if (currentTime - lastMonsterUpdate > 500) {
            int damageToPlayer = 0;
            map.updateMonsters(playerY, playerX, damageToPlayer);
            
            if (damageToPlayer > 0) {
                player.takeDamage(damageToPlayer);
                playerStatsChanged = true;
            }
            
            lastMonsterUpdate = currentTime;
        }
        
        checkPlayerStats();
        
        renderer.drawField(map, player, viewport);
        
        if (playerStatsChanged) {
            showPlayerStats();
            playerStatsChanged = false;
        }
        
        if (targetedMonster) {
            showMonsterInfo();
        }
        
        usleep(player.getMoveDelay() / 2);
    }
    
    terminal.cleanup(renderer.getHeight());
}

bool Game::processInput() {
    char inputBuffer[32];
    
    int bytesRead = input.readInput(inputBuffer, sizeof(inputBuffer));
    
    if (bytesRead <= 0) {
        return true;
    }
    
    bool eKeyPressed = false;
    bool fKeyPressed = false;
    
    for (int i = 0; i < bytesRead; i++) {
        char ch = inputBuffer[i];
        
        switch (ch) {
            case 'q': 
                gameRunning = false;
                return false;
            case '+': 
                player.changeSpeed(1);
                playerStatsChanged = true;
                break;
            case '-': 
                player.changeSpeed(-1);
                playerStatsChanged = true;
                break;
            case 'e':
                eKeyPressed = true;
                break;
            case 'f':
                fKeyPressed = true;
                break;
            case 'w': 
                if (player.move(0, -1, map)) {
                    int playerX, playerY;
                    player.getPosition(playerX, playerY);
                    viewport.update(playerX, playerY, map);
                }
                break;
            case 's': 
                if (player.move(0, 1, map)) {
                    int playerX, playerY;
                    player.getPosition(playerX, playerY);
                    viewport.update(playerX, playerY, map);
                }
                break;
            case 'a': 
                if (player.move(-1, 0, map)) {
                    int playerX, playerY;
                    player.getPosition(playerX, playerY);
                    viewport.update(playerX, playerY, map);
                }
                break;
            case 'd': 
                if (player.move(1, 0, map)) {
                    int playerX, playerY;
                    player.getPosition(playerX, playerY);
                    viewport.update(playerX, playerY, map);
                }
                break;
            default:
                break;
        }
    }
    
    if (eKeyPressed) {
        activateMonsterBox();
        map.updateBoxes();
        updateBoxIndicators();
    }
    
    if (fKeyPressed) {
        int playerX, playerY;
        player.getPosition(playerX, playerY);
        
        int targetRow, targetCol;
        if (map.findMonsterInRange(playerY, playerX, player.getAttackRange(), targetRow, targetCol)) {
            int damage = player.getCard().getAttack();
            bool killed = map.attackMonster(targetRow, targetCol, damage);
            
            if (!killed) {
                targetedMonsterRow = targetRow;
                targetedMonsterCol = targetCol;
                targetedMonster = true;
            } else {
                targetedMonster = false;
                clearMonsterInfo();
            }
        }
    }
    
    return true;
}

int Game::getMoveDelay() const {
    return player.getMoveDelay();
}

int Game::getTermHeight() const {
    return renderer.getHeight();
}

void Game::updateBoxIndicators() {
    int viewX, viewY, viewWidth, viewHeight;
    viewport.getViewArea(viewX, viewY, viewWidth, viewHeight);
    
    for (int row = viewY; row < viewY + viewHeight; row++) {
        for (int col = viewX; col < viewX + viewWidth; col++) {
            if (map.isBoxLocation(row, col)) {
                bool isReady = map.isBoxReadyAt(row, col);
                map.placeIndicator(row, col, isReady);
                
                BoxInfo boxInfo;
                if (map.getBoxInfo(row, col, boxInfo)) {
                    col = boxInfo.leftCol + boxInfo.width - 1;
                }
            }
        }
    }
}

void Game::initAllBoxIndicators() {
    for (int row = 0; row < map.getHeight(); row++) {
        for (int col = 0; col < map.getWidth(); col++) {
            if (map.isBoxLocation(row, col)) {
                bool isReady = map.isBoxReadyAt(row, col);
                map.placeIndicator(row, col, isReady);
                
                BoxInfo boxInfo;
                if (map.getBoxInfo(row, col, boxInfo)) {
                    col = boxInfo.leftCol + boxInfo.width - 1;
                }
            }
        }
    }
}

void Game::activateMonsterBox() {
    int playerX, playerY;
    player.getPosition(playerX, playerY);
    
    for (int y = playerY - 1; y <= playerY + 1; y++) {
        for (int x = playerX - 1; x <= playerX + 1; x++) {
            if (map.isBoxLocation(y, x) && map.isBoxReadyAt(y, x)) {
                map.useBox(y, x);
                
                auto center = map.getBoxCenter(y, x);
                int centerY = center.first;
                int centerX = center.second;
                
                std::vector<std::pair<int, int>> possiblePositions;
                
                for (int radius = 3; radius >= 1; radius--) {
                    for (int monsterY = centerY - radius; monsterY <= centerY + radius; monsterY++) {
                        for (int monsterX = centerX - radius; monsterX <= centerX + radius; monsterX++) {
                            if (monsterY == playerY && monsterX == playerX) {
                                continue;
                            }
                            
                            if (map.isValidPosition(monsterY, monsterX) && 
                                map.getCell(monsterY, monsterX) == ' ' &&
                                !map.isBoxLocation(monsterY, monsterX)) {
                                possiblePositions.push_back({monsterY, monsterX});
                            }
                        }
                    }
                }
                
                if (!possiblePositions.empty()) {
                    srand(static_cast<unsigned>(time(nullptr)));
                    int randomIndex = rand() % possiblePositions.size();
                    int monsterY = possiblePositions[randomIndex].first;
                    int monsterX = possiblePositions[randomIndex].second;
                    
                    map.spawnMonster(monsterY, monsterX);
                }
                
                map.placeIndicator(y, x, false);
                return;
            }
        }
    }
}

void Game::showPlayerStats() {
    const PlayerCard& card = player.getCard();
    
    int width, height;
    terminal.getTerminalSize(width, height);
    
    int statsRow = height - 3;
    
    int health = card.getHealth();
    int maxHealth = card.getMaxHealth();
    int attack = card.getAttack();
    int defense = card.getDefense();
    int speed = card.getSpeed();
    int level = card.getLevel();
    int experience = card.getExperience();
    int expToNextLevel = card.getExperienceToNextLevel();
    
    std::string statsInfo = "Player HP: " + std::to_string(health) + "/" + std::to_string(maxHealth) +
                           " | ATK: " + std::to_string(attack) +
                           " | DEF: " + std::to_string(defense) +
                           " | SPD: " + std::to_string(speed) +
                           " | LVL: " + std::to_string(level) +
                           " | EXP: " + std::to_string(experience) + "/" + std::to_string(expToNextLevel);
    
    terminal.moveCursor(statsRow, 1);
    std::cout << std::string(width, ' ');
    
    terminal.moveCursor(statsRow, 1);
    std::cout << statsInfo;
}

void Game::showMonsterInfo() {
    if (!targetedMonster || !map.isMonsterAt(targetedMonsterRow, targetedMonsterCol)) {
        targetedMonster = false;
        return;
    }
    
    const MonsterCard& monster = map.getMonsterAt(targetedMonsterRow, targetedMonsterCol);
    
    int width, height;
    terminal.getTerminalSize(width, height);
    
    int monsterInfoRow = height - 2;
    
    std::string name = monster.getName();
    int health = monster.getHealth();
    int maxHealth = monster.getMaxHealth();
    int attack = monster.getAttack();
    int defense = monster.getDefense();
    int level = monster.getLevel();
    
    std::string monsterInfo = "Monster: " + name +
                             " | HP: " + std::to_string(health) + "/" + std::to_string(maxHealth) +
                             " | ATK: " + std::to_string(attack) +
                             " | DEF: " + std::to_string(defense) +
                             " | LVL: " + std::to_string(level);
    
    terminal.moveCursor(monsterInfoRow, 1);
    std::cout << std::string(width, ' ');
    
    terminal.moveCursor(monsterInfoRow, 1);
    std::cout << monsterInfo;
}

void Game::clearMonsterInfo() {
    int width, height;
    terminal.getTerminalSize(width, height);
    
    int monsterInfoRow = height - 2;
    
    terminal.moveCursor(monsterInfoRow, 1);
    std::cout << std::string(width, ' ');
}

void Game::checkPlayerStats() {
    const PlayerCard& card = player.getCard();
    
    if (lastHealth != card.getHealth() ||
        lastMaxHealth != card.getMaxHealth() ||
        lastAttack != card.getAttack() ||
        lastDefense != card.getDefense() ||
        lastSpeed != card.getSpeed() ||
        lastLevel != card.getLevel() ||
        lastExperience != card.getExperience() ||
        lastExpToNextLevel != card.getExperienceToNextLevel()) {
        
        lastHealth = card.getHealth();
        lastMaxHealth = card.getMaxHealth();
        lastAttack = card.getAttack();
        lastDefense = card.getDefense();
        lastSpeed = card.getSpeed();
        lastLevel = card.getLevel();
        lastExperience = card.getExperience();
        lastExpToNextLevel = card.getExperienceToNextLevel();
        
        playerStatsChanged = true;
    }
}