#ifndef NPC_CARD_H
#define NPC_CARD_H
#include "character_card.h"
#include <vector>
#include "quests_card.h"
#include "../enums.h"
class NPCCard : public CharacterCard
{
    private:
        Hostility hostility;
        Race race;
        std::vector<Quest> quests;
    public:
        NPCCard(const std::string& name, const std::string& description, int health, int maxHealth, int attack, int defense, int speed, Hostility hostility, Race race);
        NPCCard();
        Hostility getHostility() const;
        Race getRace() const;
        std::vector<Quest> getQuests() const;
        void addQuest(Quest quest);
        void removeQuest(Quest quest);
        void setHostility(Hostility hostility);
        void setRace(Race race);
};

#endif // NPC_CARD_H
