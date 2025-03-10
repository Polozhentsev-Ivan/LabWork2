#ifndef TASK_H
#define TASK_H
#include "enums.h"
#include <string>
#include <stdexcept>

class Task
{
    private:
        std::string description;
        int counter;
        int maxCounter;
        QuestType questType;
        bool isCompleted;
    public:
        Task(std::string description, int counter, int maxCounter, QuestType questType);
        Task();
        QuestType getQuestType() const;
        void setQuestType(QuestType questType);
        std::string getDescription() const;
        int getCounter() const;
        int getMaxCounter() const;
        void setDescription(const std::string& description);
        void setCounter(int counter);
        void setMaxCounter(int maxCounter);
        void resetCounter();
        bool getIsCompleted() const;
        void setIsCompleted(bool completed);
        bool checkCompletion();
};
class CollectTask : public Task
{
    private:
        std::string itemName;
    public:
        CollectTask(std::string description, int counter, int maxCounter, std::string itemName);
        CollectTask();
        std::string getItemName() const;
        void setItemName(const std::string& itemName);
        void setQuestType(QuestType);
};
class KillTask : public Task
{
    private:
        std::string enemyName;
    public:
        KillTask(std::string description, int counter, int maxCounter, std::string enemyName);
        KillTask();
        std::string getEnemyName() const;
        void setEnemyName(const std::string& enemyName);
        void setQuestType(QuestType);
};

#endif // TASK_H

