#include <iostream>
#include "../include/card/card.h"
#include "../include/card/task.h"
#include "../include/card/quests_card.h"
#include "../include/enums.h"
#include "../include/card/character_card.h"
#include "../include/card/player_card.h"
#include "../include/card/monster_card.h"
#include "../include/card/npc_card.h"
#include "../include/card/item_card.h"
#include "../include/card/equipment_card.h"
#include "../include/card/environment_card.h"

int main() {
    // Пример работы с картой
    Card basicCard("Basic Card", "Simple card example");
    std::cout << "Card Name: " << basicCard.getName() << "\n";
    std::cout << "Card Description: " << basicCard.getDescription() << "\n\n";

    // Пример работы с персонажем
    CharacterCard character("Hero", "Main character", 100, 100, 10, 5, 1);
    std::cout << "Character Name: " << character.getName() << "\n";
    std::cout << "Character Health: " << character.getHealth() << "/" << character.getMaxHealth() << "\n\n";

    // Пример работы с квестом
    Quest mainQuest("Main Quest", "Save the world", QuestType::kill, 1000, 5, 500);
    std::cout << "Quest Name: " << mainQuest.getName() << "\n";
    std::cout << "Quest Type: " << static_cast<int>(mainQuest.getQuestType()) << "\n";
    std::cout << "Experience Reward: " << mainQuest.getExperienceReward() << "\n\n";

    // Пример работы с предметом
    Item sword("Sword", "Basic weapon", 50, Material::iron, 1, 5, 5);
    std::cout << "Item Name: " << sword.getName() << "\n";
    std::cout << "Item Material: " << static_cast<int>(sword.getMaterial()) << "\n";
    std::cout << "Item Weight: " << sword.getWeight() << "\n";

    return 0;
} 