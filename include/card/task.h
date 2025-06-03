#ifndef TASK_H
#define TASK_H
#include "../enums.h"
#include <string>
#include <stdexcept>

/**
 * @brief Represents a generic task within a quest.
 * 
 * This class defines the basic structure of a task, including its description,
 * progress counter, completion status, and associated quest type.
 */
class Task
{
    private:
        std::string description; /**< A description of the task. */
        int counter;             /**< The current progress counter for the task. */
        int maxCounter;          /**< The target counter value for task completion. */
        QuestType questType;     /**< The type of quest this task belongs to. */
        bool isCompleted;        /**< Flag indicating whether the task is completed. */
    public:
        /**
         * @brief Constructs a Task with specified attributes.
         *
         * @param description A description of the task.
         * @param counter The initial progress counter.
         * @param maxCounter The target counter for completion.
         * @param questType The type of quest this task belongs to.
         */
        Task(std::string description, int counter, int maxCounter, QuestType questType);
        /**
         * @brief Default constructor for Task.
         */
        Task();
        /**
         * @brief Gets the type of quest this task belongs to.
         * @return The quest type.
         */
        QuestType getQuestType() const;
        /**
         * @brief Sets the type of quest this task belongs to.
         * @param questType The new quest type.
         */
        void setQuestType(QuestType questType);
        /**
         * @brief Gets the description of the task.
         * @return The task description.
         */
        std::string getDescription() const;
        /**
         * @brief Gets the current progress counter of the task.
         * @return The current counter value.
         */
        int getCounter() const;
        /**
         * @brief Gets the target counter value for task completion.
         * @return The maximum counter value.
         */
        int getMaxCounter() const;
        /**
         * @brief Sets the description of the task.
         * @param description The new task description.
         */
        void setDescription(const std::string& description);
        /**
         * @brief Sets the current progress counter of the task.
         * @param counter The new counter value.
         */
        void setCounter(int counter);
        /**
         * @brief Sets the target counter value for task completion.
         * @param maxCounter The new maximum counter value.
         */
        void setMaxCounter(int maxCounter);
        /**
         * @brief Resets the progress counter to zero.
         */
        void resetCounter();
        /**
         * @brief Checks if the task is completed.
         * @return True if the task is completed, false otherwise.
         */
        bool getIsCompleted() const;
        /**
         * @brief Sets the completion status of the task.
         * @param completed The new completion status.
         */
        void setIsCompleted(bool completed);
        /**
         * @brief Checks if the task's completion condition (counter >= maxCounter) is met.
         * @return True if the condition is met, false otherwise.
         */
        bool checkCompletion();
};
/**
 * @brief Represents a task that involves collecting specific items.
 * 
 * This class inherits from Task and adds an attribute for the name of the item to be collected.
 */
class CollectTask : public Task
{
    private:
        std::string itemName; /**< The name of the item to be collected. */
    public:
        /**
         * @brief Constructs a CollectTask with specified attributes.
         *
         * @param description A description of the collect task.
         * @param counter The initial progress counter.
         * @param maxCounter The target counter for completion (number of items to collect).
         * @param itemName The name of the item to collect.
         */
        CollectTask(std::string description, int counter, int maxCounter, std::string itemName);
        /**
         * @brief Default constructor for CollectTask.
         */
        CollectTask();
        /**
         * @brief Gets the name of the item to be collected.
         * @return The item name.
         */
        std::string getItemName() const;
        /**
         * @brief Sets the name of the item to be collected.
         * @param itemName The new item name.
         */
        void setItemName(const std::string& itemName);
        void setQuestType(QuestType);
};
/**
 * @brief Represents a task that involves killing specific enemies.
 * 
 * This class inherits from Task and adds an attribute for the name of the enemy to be killed.
 */
class KillTask : public Task
{
    private:
        std::string enemyName; /**< The name of the enemy to be killed. */
    public:
        /**
         * @brief Constructs a KillTask with specified attributes.
         *
         * @param description A description of the kill task.
         * @param counter The initial progress counter.
         * @param maxCounter The target counter for completion (number of enemies to kill).
         * @param enemyName The name of the enemy to kill.
         */
        KillTask(std::string description, int counter, int maxCounter, std::string enemyName);
        /**
         * @brief Default constructor for KillTask.
         */
        KillTask();
        /**
         * @brief Gets the name of the enemy to be killed.
         * @return The enemy name.
         */
        std::string getEnemyName() const;
        /**
         * @brief Sets the name of the enemy to be killed.
         * @param enemyName The new enemy name.
         */
        void setEnemyName(const std::string& enemyName);
        void setQuestType(QuestType);
};

#endif // TASK_H

