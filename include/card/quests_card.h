#ifndef QUEST_CARD_H
#define QUEST_CARD_H
#include "card.h"
#include "../enums.h"
#include "item_card.h"
#include "task.h"
#include <vector>
#include <memory>
#include <algorithm>

/**
 * @brief Represents a quest card in the game.
 * 
 * This class inherits from Card and defines the basic structure of a quest,
 * including its type, rewards (experience, silver, items), difficulty, and tasks.
 */
class Quest: public Card
{
    protected:
        QuestType questType;                                /**< The type of the quest (e.g., Hunting, Gathering). */
        int experienceReward;                               /**< The amount of experience points rewarded upon completion. */
        int difficulty;                                     /**< The difficulty level of the quest. */
        int silverReward;                                   /**< The amount of silver rewarded upon completion. */
        std::vector<std::shared_ptr<Item>> itemReward;      /**< A list of items rewarded upon completion. */
        std::vector<std::shared_ptr<Task>> tasks;           /**< A list of tasks required to complete the quest. */
    public:
        /**
         * @brief Constructs a Quest with specified attributes.
         *
         * @param name The name of the quest.
         * @param description A description of the quest.
         * @param questType The type of the quest.
         * @param experienceReward The experience points reward.
         * @param difficulty The difficulty level.
         * @param silverReward The silver reward.
         */
        Quest(std::string name, std::string description, QuestType questType, int experienceReward, int difficulty, int silverReward);
        /**
         * @brief Default constructor for Quest.
         */
        Quest();
        /**
         * @brief Gets the type of the quest.
         * @return The quest type.
         */
        QuestType getQuestType() const;
        /**
         * @brief Gets the experience points rewarded by the quest.
         * @return The experience reward.
         */
        int getExperienceReward() const;
        /**
         * @brief Gets the difficulty level of the quest.
         * @return The difficulty level.
         */
        int getDifficulty() const;
        /**
         * @brief Gets the silver rewarded by the quest.
         * @return The silver reward.
         */
        int getSilverReward() const;
        /**
         * @brief Gets the list of items rewarded by the quest.
         * @return A vector of shared pointers to Item objects.
         */
        std::vector<std::shared_ptr<Item>> getItemReward() const;
        /**
         * @brief Sets the type of the quest.
         * @param questType The new quest type.
         */
        void setQuestType(QuestType questType);
        /**
         * @brief Sets the experience points rewarded by the quest.
         * @param experienceReward The new experience reward value.
         */
        void setExperienceReward(int experienceReward);
        /**
         * @brief Sets the difficulty level of the quest.
         * @param difficulty The new difficulty level.
         */
        void setDifficulty(int difficulty);
        /**
         * @brief Sets the silver rewarded by the quest.
         * @param silverReward The new silver reward value.
         */
        void setSilverReward(int silverReward);
        /**
         * @brief Adds an item to the quest's reward list.
         * @param item A shared pointer to the Item object to add.
         */
        void addItemToReward(std::shared_ptr<Item> item);
        /**
         * @brief Removes an item from the quest's reward list.
         * @param item A shared pointer to the Item object to remove.
         */
        void removeItemFromReward(std::shared_ptr<Item> item);
        /**
         * @brief Adds a task to the quest's list of tasks.
         * @param task A shared pointer to the Task object to add.
         */
        void addTask(std::shared_ptr<Task> task);
        /**
         * @brief Removes a task from the quest's list of tasks.
         * @param task A shared pointer to the Task object to remove.
         */
        void removeTask(std::shared_ptr<Task> task);
        /**
         * @brief Gets the list of tasks for the quest.
         * @return A vector of shared pointers to Task objects.
         */
        std::vector<std::shared_ptr<Task>> getTasks() const;
        /**
         * @brief Equality operator for comparing two Quest objects.
         * @param other The other Quest object to compare with.
         * @return True if the quests are equal, false otherwise.
         */
        bool operator==(const Quest& other) const;
};
/**
 * @brief Represents a hunting quest in the game.
 * 
 * This class inherits from Quest and is specialized for quests that involve killing monsters.
 */
class HuntingQuest : public Quest {
public:
    /**
     * @brief Constructs a HuntingQuest with specified attributes.
     *
     * @param name The name of the hunting quest.
     * @param description A description of the hunting quest.
     * @param exp The experience points reward.
     * @param diff The difficulty level.
     * @param silver The silver reward.
     */
    HuntingQuest(std::string name, std::string description, int exp, int diff, int silver);
    /**
     * @brief Default constructor for HuntingQuest.
     */
    HuntingQuest();
    /**
     * @brief Adds a kill task to the hunting quest.
     * @param task A shared pointer to the KillTask object to add.
     */
    void addTask(std::shared_ptr<KillTask> task);
    /**
     * @brief Removes a kill task from the hunting quest.
     * @param task A shared pointer to the KillTask object to remove.
     */
    void removeTask(std::shared_ptr<KillTask> task);
    void setQuestType(QuestType questType);
};

/**
 * @brief Represents a gathering quest in the game.
 * 
 * This class inherits from Quest and is specialized for quests that involve collecting items.
 */
class GatheringQuest : public Quest {
public:
    /**
     * @brief Constructs a GatheringQuest with specified attributes.
     *
     * @param name The name of the gathering quest.
     * @param description A description of the gathering quest.
     * @param exp The experience points reward.
     * @param diff The difficulty level.
     * @param silver The silver reward.
     */
    GatheringQuest(std::string name, std::string description, int exp, int diff, int silver);
    /**
     * @brief Default constructor for GatheringQuest.
     */
    GatheringQuest();
    /**
     * @brief Adds a collect task to the gathering quest.
     * @param task A shared pointer to the CollectTask object to add.
     */
    void addTask(std::shared_ptr<CollectTask> task);
    /**
     * @brief Removes a collect task from the gathering quest.
     * @param task A shared pointer to the CollectTask object to remove.
     */
    void removeTask(std::shared_ptr<CollectTask> task);
    void setQuestType(QuestType questType);
};



#endif // QUEST_CARD_H
