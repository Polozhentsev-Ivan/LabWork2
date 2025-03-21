#include "../../include/card/task.h"

Task::Task(std::string description, int counter, int maxCounter, QuestType questType)
    : description(description), counter(counter), maxCounter(maxCounter), questType(questType) {
        isCompleted = checkCompletion();
    }

Task::Task() : description(""), counter(0), maxCounter(0), questType(QuestType::kill) {
    isCompleted = checkCompletion();
}

QuestType Task::getQuestType() const {
    return questType;
}

void Task::setQuestType(QuestType questType) {
    this->questType = questType;
}

std::string Task::getDescription() const {
    return description;
}

int Task::getCounter() const {
    return counter;
}

int Task::getMaxCounter() const {
    return maxCounter;
}

void Task::setDescription(const std::string& description) {
    this->description = description;
}

void Task::setCounter(int counter) {
    this->counter = counter;
}

void Task::setMaxCounter(int maxCounter) {
    this->maxCounter = maxCounter;
}

void Task::resetCounter() {
    counter = 0;
}

bool Task::getIsCompleted() const {
    return isCompleted;
}

void Task::setIsCompleted(bool completed) {
    isCompleted = completed;
}


CollectTask::CollectTask(std::string description, int counter, int maxCounter, std::string itemName)
    : Task(description, counter, maxCounter, QuestType::collect), itemName(itemName) {}

CollectTask::CollectTask() : Task(), itemName("") {
    setQuestType(QuestType::collect);
}

std::string CollectTask::getItemName() const {
    return itemName;
}

void CollectTask::setItemName(const std::string& itemName) {
    this->itemName = itemName;
}

KillTask::KillTask(std::string description, int counter, int maxCounter, std::string enemyName)
    : Task(description, counter, maxCounter, QuestType::kill), enemyName(enemyName) {}

KillTask::KillTask() : Task(), enemyName("") {
    setQuestType(QuestType::kill);
}

std::string KillTask::getEnemyName() const {
    return enemyName;
}

void KillTask::setEnemyName(const std::string& enemyName) {
    this->enemyName = enemyName;
}

bool Task::checkCompletion() {
    if (counter >= maxCounter) {
        isCompleted = true;
        return true;
    }
    return false;
}

void CollectTask::setQuestType(QuestType questType) {
    if (questType != QuestType::collect) {
        throw std::invalid_argument("CollectTask can only have QuestType::collect");
    }
    Task::setQuestType(questType);
}

void KillTask::setQuestType(QuestType questType) {
    if (questType != QuestType::kill) {
        throw std::invalid_argument("KillTask can only have QuestType::kill");
    }
    Task::setQuestType(questType);
}

