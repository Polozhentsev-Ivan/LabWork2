#include "../include/npc_card.h"

NPCCard::NPCCard(const std::string& name, const std::string& description, int health, int maxHealth, int attack, int defense, int speed, Hostility hostility, Race race)
    : CharacterCard(name, description, health, maxHealth, attack, defense, speed), hostility(hostility), race(race) {}

NPCCard::NPCCard() : CharacterCard(), hostility(Hostility::unknown), race(Race::unknown) {}

Hostility NPCCard::getHostility() const {
    return hostility;
}

Race NPCCard::getRace() const {
    return race;
}   

std::vector<Quest> NPCCard::getQuests() const {
    return quests;
}

void NPCCard::addQuest(Quest quest) {
    quests.push_back(quest);
}

void NPCCard::removeQuest(Quest quest) {
    quests.erase(std::remove(quests.begin(), quests.end(), quest), quests.end());
}

void NPCCard::setHostility(Hostility hostility) {
    this->hostility = hostility;
}

void NPCCard::setRace(Race race) {
    this->race = race;
}
