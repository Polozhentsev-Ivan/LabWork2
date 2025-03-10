#ifndef QUEST_CARD_H
#define QUEST_CARD_H
#include "card.h"
#include "enums.h"
#include "item_card.h"
#include "task.h"
#include <vector>
#include <memory>
#include <algorithm>

class Quest: public Card
{
    protected:
        QuestType questType;
        int experienceReward;
        int difficulty;
        int silverReward;
        std::vector<std::shared_ptr<Item>> itemReward;
        std::vector<std::shared_ptr<Task>> tasks;
    public:
        Quest(std::string name, std::string description, QuestType questType, int experienceReward, int difficulty, int silverReward);
        Quest();
        QuestType getQuestType() const;
        int getExperienceReward() const;
        int getDifficulty() const;
        int getSilverReward() const;
        std::vector<std::shared_ptr<Item>> getItemReward() const;
        void setQuestType(QuestType questType);
        void setExperienceReward(int experienceReward);
        void setDifficulty(int difficulty);
        void setSilverReward(int silverReward);
        void addItemToReward(std::shared_ptr<Item> item);
        void removeItemFromReward(std::shared_ptr<Item> item);
        void addTask(std::shared_ptr<Task> task);
        void removeTask(std::shared_ptr<Task> task);
        std::vector<std::shared_ptr<Task>> getTasks() const;
        bool operator==(const Quest& other) const;
};
class HuntingQuest : public Quest {
public:
    HuntingQuest(std::string name, std::string description, int exp, int diff, int silver);
    HuntingQuest();
    void addTask(std::shared_ptr<KillTask> task);
    void removeTask(std::shared_ptr<KillTask> task);
    void setQuestType(QuestType questType);
};

class GatheringQuest : public Quest {
public:
    GatheringQuest(std::string name, std::string description, int exp, int diff, int silver);
    GatheringQuest();
    void addTask(std::shared_ptr<CollectTask> task);
    void removeTask(std::shared_ptr<CollectTask> task);
    void setQuestType(QuestType questType);
};



#endif // QUEST_CARD_H
