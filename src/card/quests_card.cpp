#include "../../include/card/quests_card.h"

Quest::Quest(std::string name, std::string description, QuestType questType, int experienceReward, int difficulty, 
             int silverReward)
    : Card(name, description), questType(questType), experienceReward(experienceReward),
      difficulty(difficulty), silverReward(silverReward) {}

Quest::Quest() : Card(), questType(QuestType::kill), experienceReward(0),
                 difficulty(1), silverReward(0) {}

QuestType Quest::getQuestType() const {
    return questType;
}

int Quest::getExperienceReward() const {
    return experienceReward;
}

int Quest::getDifficulty() const {
    return difficulty;
}

int Quest::getSilverReward() const {
    return silverReward;
}

std::vector<std::shared_ptr<Item>> Quest::getItemReward() const {
    return itemReward;
}

void Quest::setQuestType(QuestType questType) {
    this->questType = questType;
}

void Quest::setExperienceReward(int experienceReward) {
    this->experienceReward = experienceReward;
}

void Quest::setDifficulty(int difficulty) {
    this->difficulty = difficulty;
}

void Quest::setSilverReward(int silverReward) {
    this->silverReward = silverReward;
}

void Quest::addItemToReward(std::shared_ptr<Item> item) {
    itemReward.push_back(item);
}

void Quest::removeItemFromReward(std::shared_ptr<Item> item) {
    auto it = std::find(itemReward.begin(), itemReward.end(), item);
    if (it != itemReward.end()) {
        itemReward.erase(it);
    }
}
void Quest::addTask(std::shared_ptr<Task> task) {
    tasks.push_back(task);
}

void Quest::removeTask(std::shared_ptr<Task> task) {
    auto it = std::find(tasks.begin(), tasks.end(), task);
    if (it != tasks.end()) {
        tasks.erase(it);
    }
}

std::vector<std::shared_ptr<Task>> Quest::getTasks() const {
    return tasks;
}

HuntingQuest::HuntingQuest(std::string name, std::string description, int exp, int diff, int silver)
    : Quest(name, description, QuestType::kill, exp, diff, silver) {}

HuntingQuest::HuntingQuest() : Quest("","", QuestType::kill, 0, 0, 0) {}

void HuntingQuest::addTask(std::shared_ptr<KillTask> task) {
    tasks.push_back(task);
}

void HuntingQuest::removeTask(std::shared_ptr<KillTask> task) {
    auto it = std::find(tasks.begin(), tasks.end(), task);
    if (it != tasks.end()) {
        tasks.erase(it);
    }
}

GatheringQuest::GatheringQuest(std::string name, std::string description, int exp, int diff, int silver)
    : Quest(name, description, QuestType::collect, exp, diff, silver) {}

GatheringQuest::GatheringQuest() : Quest("","", QuestType::collect, 0, 0, 0) {}

void GatheringQuest::addTask(std::shared_ptr<CollectTask> task) {
    tasks.push_back(task);
}   

void GatheringQuest::removeTask(std::shared_ptr<CollectTask> task) {
    auto it = std::find(tasks.begin(), tasks.end(), task);
    if (it != tasks.end()) {
        tasks.erase(it);
    }
}

void GatheringQuest::setQuestType(QuestType questType) {
    if (questType != QuestType::collect) {
        throw std::invalid_argument("GatheringQuest can only have QuestType::collect");
    }
    Quest::setQuestType(questType);
}

void HuntingQuest::setQuestType(QuestType questType) {
    if (questType != QuestType::kill) {
        throw std::invalid_argument("HuntingQuest can only have QuestType::kill");
    }
    Quest::setQuestType(questType);
}

bool Quest::operator==(const Quest& other) const {
    return name == other.name &&
    description == other.description &&
    questType == other.questType &&
    experienceReward == other.experienceReward &&
    difficulty == other.difficulty &&
    silverReward == other.silverReward &&
    tasks == other.tasks &&
    itemReward == other.itemReward;
}