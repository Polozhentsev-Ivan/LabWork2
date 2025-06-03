/**
 * @file task.cpp
 * @brief Implements the Task, CollectTask, and KillTask class methods.
 */
#include "../../include/card/task.h"

/**
 * @brief Constructs a Task object with specified attributes.
 *
 * @param description The description of the task.
 * @param counter The current progress counter for the task.
 * @param maxCounter The target counter value for task completion.
 * @param questType The type of quest this task belongs to.
 */
Task::Task(std::string description, int counter, int maxCounter, QuestType questType)
    : description(description), counter(counter), maxCounter(maxCounter), questType(questType) {
        isCompleted = checkCompletion();
    }

/**
 * @brief Default constructor for the Task class.
 *
 * Initializes with empty description, zero counters, and kill quest type.
 */
Task::Task() : description(""), counter(0), maxCounter(0), questType(QuestType::kill) {
    isCompleted = checkCompletion();
}

/**
 * @brief Gets the quest type of the task.
 *
 * @return The quest type.
 */
QuestType Task::getQuestType() const {
    return questType;
}

/**
 * @brief Sets the quest type of the task.
 *
 * @param questType The new quest type.
 */
void Task::setQuestType(QuestType questType) {
    this->questType = questType;
}

/**
 * @brief Gets the description of the task.
 *
 * @return The task description.
 */
std::string Task::getDescription() const {
    return description;
}

/**
 * @brief Gets the current counter value of the task.
 *
 * @return The current counter.
 */
int Task::getCounter() const {
    return counter;
}

/**
 * @brief Gets the maximum counter value (target) of the task.
 *
 * @return The maximum counter.
 */
int Task::getMaxCounter() const {
    return maxCounter;
}

/**
 * @brief Sets the description of the task.
 *
 * @param description The new task description.
 */
void Task::setDescription(const std::string& description) {
    this->description = description;
}

/**
 * @brief Sets the current counter value of the task.
 *
 * @param counter The new counter value.
 */
void Task::setCounter(int counter) {
    this->counter = counter;
}

/**
 * @brief Sets the maximum counter value (target) of the task.
 *
 * @param maxCounter The new maximum counter value.
 */
void Task::setMaxCounter(int maxCounter) {
    this->maxCounter = maxCounter;
}

/**
 * @brief Resets the task's counter to zero.
 */
void Task::resetCounter() {
    counter = 0;
}

/**
 * @brief Checks if the task is completed.
 *
 * @return True if completed, false otherwise.
 */
bool Task::getIsCompleted() const {
    return isCompleted;
}

/**
 * @brief Sets the completion status of the task.
 *
 * @param completed The new completion status.
 */
void Task::setIsCompleted(bool completed) {
    isCompleted = completed;
}


/**
 * @brief Constructs a CollectTask object.
 *
 * @param description Description of the collect task.
 * @param counter Current item count.
 * @param maxCounter Target item count.
 * @param itemName Name of the item to collect.
 */
CollectTask::CollectTask(std::string description, int counter, int maxCounter, std::string itemName)
    : Task(description, counter, maxCounter, QuestType::collect), itemName(itemName) {}

/**
 * @brief Default constructor for CollectTask.
 */
CollectTask::CollectTask() : Task(), itemName("") {
    setQuestType(QuestType::collect);
}

/**
 * @brief Gets the name of the item to be collected.
 *
 * @return The item name.
 */
std::string CollectTask::getItemName() const {
    return itemName;
}

/**
 * @brief Sets the name of the item to be collected.
 *
 * @param itemName The new item name.
 */
void CollectTask::setItemName(const std::string& itemName) {
    this->itemName = itemName;
}

/**
 * @brief Constructs a KillTask object.
 *
 * @param description Description of the kill task.
 * @param counter Current kill count.
 * @param maxCounter Target kill count.
 * @param enemyName Name of the enemy to kill.
 */
KillTask::KillTask(std::string description, int counter, int maxCounter, std::string enemyName)
    : Task(description, counter, maxCounter, QuestType::kill), enemyName(enemyName) {}

/**
 * @brief Default constructor for KillTask.
 */
KillTask::KillTask() : Task(), enemyName("") {
    setQuestType(QuestType::kill);
}

/**
 * @brief Gets the name of the enemy to be killed.
 *
 * @return The enemy name.
 */
std::string KillTask::getEnemyName() const {
    return enemyName;
}

/**
 * @brief Sets the name of the enemy to be killed.
 *
 * @param enemyName The new enemy name.
 */
void KillTask::setEnemyName(const std::string& enemyName) {
    this->enemyName = enemyName;
}

/**
 * @brief Checks if the task's counter has reached its maximum, marking it as completed if so.
 *
 * @return True if the task is completed, false otherwise.
 */
bool Task::checkCompletion() {
    if (counter >= maxCounter) {
        isCompleted = true;
        return true;
    }
    return false;
}

/**
 * @brief Sets the quest type for a CollectTask.
 * @param questType The type of the quest.
 * @throws std::invalid_argument if questType is not QuestType::collect.
 */
void CollectTask::setQuestType(QuestType questType) {
    if (questType != QuestType::collect) {
        throw std::invalid_argument("CollectTask can only have QuestType::collect");
    }
    Task::setQuestType(questType);
}

/**
 * @brief Sets the quest type for a KillTask.
 * @param questType The type of the quest.
 * @throws std::invalid_argument if questType is not QuestType::kill.
 */
void KillTask::setQuestType(QuestType questType) {
    if (questType != QuestType::kill) {
        throw std::invalid_argument("KillTask can only have QuestType::kill");
    }
    Task::setQuestType(questType);
}

