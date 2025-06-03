#ifndef NPC_CARD_H
#define NPC_CARD_H
#include "character_card.h"
#include <vector>
#include "quests_card.h"
#include "../enums.h"
/**
 * @brief Represents a Non-Player Character (NPC) card in the game.
 * 
 * This class inherits from CharacterCard and adds attributes specific to NPCs,
 * such as hostility level, race, and a list of quests they might offer.
 */
class NPCCard : public CharacterCard
{
    private:
        Hostility hostility;        /**< The hostility level of the NPC towards the player. */
        Race race;                  /**< The race of the NPC. */
        std::vector<Quest> quests;  /**< A list of quests associated with this NPC. */
    public:
        /**
         * @brief Constructs an NPCCard with specified attributes.
         *
         * @param name The name of the NPC.
         * @param description A description of the NPC.
         * @param health The current health of the NPC.
         * @param maxHealth The maximum health of the NPC.
         * @param attack The attack power of the NPC.
         * @param defense The defense power of the NPC.
         * @param speed The speed of the NPC.
         * @param hostility The hostility level of the NPC.
         * @param race The race of the NPC.
         */
        NPCCard(const std::string& name, const std::string& description, int health, int maxHealth, int attack, int defense, int speed, Hostility hostility, Race race);
        /**
         * @brief Default constructor for NPCCard.
         */
        NPCCard();
        /**
         * @brief Gets the hostility level of the NPC.
         * @return The hostility level.
         */
        Hostility getHostility() const;
        /**
         * @brief Gets the race of the NPC.
         * @return The race of the NPC.
         */
        Race getRace() const;
        /**
         * @brief Gets the list of quests associated with this NPC.
         * @return A vector of Quest objects.
         */
        std::vector<Quest> getQuests() const;
        /**
         * @brief Adds a quest to the NPC's list of quests.
         * @param quest The Quest object to add.
         */
        void addQuest(Quest quest);
        /**
         * @brief Removes a quest from the NPC's list of quests.
         * @param quest The Quest object to remove.
         */
        void removeQuest(Quest quest);
        /**
         * @brief Sets the hostility level of the NPC.
         * @param hostility The new hostility level.
         */
        void setHostility(Hostility hostility);
        /**
         * @brief Sets the race of the NPC.
         * @param race The new race for the NPC.
         */
        void setRace(Race race);
};

#endif // NPC_CARD_H
