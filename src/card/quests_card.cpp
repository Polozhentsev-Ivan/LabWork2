/**
 * @file quests_card.cpp
 * @brief Implements the Quest, HuntingQuest, and GatheringQuest class methods.
 */
#include "../../include/card/quests_card.h"

/**
 * @brief Constructs a Quest object with specified attributes.
 *
 * @param name The name of the quest.
 * @param description The description of the quest.
 * @param questType The type of the quest.
 * @param experienceReward Experience points awarded for completing the quest.
 * @param difficulty The difficulty level of the quest.
 * @param silverReward Silver awarded for completing the quest.
 */
Quest::Quest(std::string name, std::string description, QuestType questType, int experienceReward, int difficulty, 
             int silverReward)
    : Card(name, description), questType(questType), experienceReward(experienceReward),
      difficulty(difficulty), silverReward(silverReward) {}

/**
 * @brief Default constructor for the Quest class.
 *
 * Initializes with default card attributes, kill quest type, and zero rewards/difficulty.
 */
Quest::Quest() : Card(), questType(QuestType::kill), experienceReward(0),
                 difficulty(1), silverReward(0) {}

/**
 * @brief Gets the type of the quest.
 *
 * @return The quest type.
 */
QuestType Quest::getQuestType() const {
    return questType;
}

/**
 * @brief Gets the experience reward for the quest.
 *
 * @return The experience reward.
 */
int Quest::getExperienceReward() const {
    return experienceReward;
}

/**
 * @brief Gets the difficulty of the quest.
 *
 * @return The quest difficulty.
 */
int Quest::getDifficulty() const {
    return difficulty;
}

/**
 * @brief Gets the silver reward for the quest.
 *
 * @return The silver reward.
 */
int Quest::getSilverReward() const {
    return silverReward;
}

/**
 * @brief Gets the item rewards for the quest.
 *
 * @return A vector of shared pointers to items.
 */
std::vector<std::shared_ptr<Item>> Quest::getItemReward() const {
    return itemReward;
}

/**
 * @brief Sets the type of the quest.
 *
 * @param questType The new quest type.
 */
void Quest::setQuestType(QuestType questType) {
    this->questType = questType;
}

/**
 * @brief Sets the experience reward for the quest.
 *
 * @param experienceReward The new experience reward.
 */
void Quest::setExperienceReward(int experienceReward) {
    this->experienceReward = experienceReward;
}

/**
 * @brief Sets the difficulty of the quest.
 *
 * @param difficulty The new difficulty level.
 */
void Quest::setDifficulty(int difficulty) {
    this->difficulty = difficulty;
}

/**
 * @brief Sets the silver reward for the quest.
 *
 * @param silverReward The new silver reward.
 */
void Quest::setSilverReward(int silverReward) {
    this->silverReward = silverReward;
}

/**
 * @brief Adds an item to the quest's reward list.
 *
 * @param item A shared pointer to the item to add.
 */
void Quest::addItemToReward(std::shared_ptr<Item> item) {
    itemReward.push_back(item);
}

/**
 * @brief Removes an item from the quest's reward list.
 *
 * @param item A shared pointer to the item to remove.
 */
void Quest::removeItemFromReward(std::shared_ptr<Item> item) {
    auto it = std::find(itemReward.begin(), itemReward.end(), item);
    if (it != itemReward.end()) {
        itemReward.erase(it);
    }
}
/**
 * @brief Adds a task to the quest.
 *
 * @param task A shared pointer to the task to add.
 */
void Quest::addTask(std::shared_ptr<Task> task) {
    tasks.push_back(task);
}

/**
 * @brief Removes a task from the quest.
 *
 * @param task A shared pointer to the task to remove.
 */
void Quest::removeTask(std::shared_ptr<Task> task) {
    auto it = std::find(tasks.begin(), tasks.end(), task);
    if (it != tasks.end()) {
        tasks.erase(it);
    }
}

/**
 * @brief Gets the list of tasks for the quest.
 *
 * @return A vector of shared pointers to tasks.
 */
std::vector<std::shared_ptr<Task>> Quest::getTasks() const {
    return tasks;
}

/**
 * @brief Constructs a HuntingQuest object.
 *
 * @param name The name of the hunting quest.
 * @param description The description of the hunting quest.
 * @param exp Experience reward.
 * @param diff Difficulty level.
 * @param silver Silver reward.
 */
HuntingQuest::HuntingQuest(std::string name, std::string description, int exp, int diff, int silver)
    : Quest(name, description, QuestType::kill, exp, diff, silver) {}

/**
 * @brief Default constructor for HuntingQuest.
 */
HuntingQuest::HuntingQuest() : Quest("","", QuestType::kill, 0, 0, 0) {}

/**
 * @brief Adds a kill task to the hunting quest.
 *
 * @param task A shared pointer to the KillTask.
 */
void HuntingQuest::addTask(std::shared_ptr<KillTask> task) {
    tasks.push_back(task);
}

/**
 * @brief Removes a kill task from the hunting quest.
 *
 * @param task A shared pointer to the KillTask.
 */
void HuntingQuest::removeTask(std::shared_ptr<KillTask> task) {
    auto it = std::find(tasks.begin(), tasks.end(), task);
    if (it != tasks.end()) {
        tasks.erase(it);
    }
}

/**
 * @brief Constructs a GatheringQuest object.
 *
 * @param name The name of the gathering quest.
 * @param description The description of the gathering quest.
 * @param exp Experience reward.
 * @param diff Difficulty level.
 * @param silver Silver reward.
 */
GatheringQuest::GatheringQuest(std::string name, std::string description, int exp, int diff, int silver)
    : Quest(name, description, QuestType::collect, exp, diff, silver) {}

/**
 * @brief Default constructor for GatheringQuest.
 */
GatheringQuest::GatheringQuest() : Quest("","", QuestType::collect, 0, 0, 0) {}

/**
 * @brief Adds a collect task to the gathering quest.
 *
 * @param task A shared pointer to the CollectTask.
 */
void GatheringQuest::addTask(std::shared_ptr<CollectTask> task) {
    tasks.push_back(task);
}   

/**
 * @brief Removes a collect task from the gathering quest.
 *
 * @param task A shared pointer to the CollectTask.
 */
void GatheringQuest::removeTask(std::shared_ptr<CollectTask> task) {
    auto it = std::find(tasks.begin(), tasks.end(), task);
    if (it != tasks.end()) {
        tasks.erase(it);
    }
}

/**
 * @brief Sets the quest type for a GatheringQuest.
 * @param questType The type of the quest.
 * @throws std::invalid_argument if questType is not QuestType::collect.
 */
void GatheringQuest::setQuestType(QuestType questType) {
    if (questType != QuestType::collect) {
        throw std::invalid_argument("GatheringQuest can only have QuestType::collect");
    }
    Quest::setQuestType(questType);
}

/**
 * @brief Sets the quest type for a HuntingQuest.
 * @param questType The type of the quest.
 * @throws std::invalid_argument if questType is not QuestType::kill.
 */
void HuntingQuest::setQuestType(QuestType questType) {
    if (questType != QuestType::kill) {
        throw std::invalid_argument("HuntingQuest can only have QuestType::kill");
    }
    Quest::setQuestType(questType);
}

/**
 * @brief Compares two Quest objects for equality.
 *
 * @param other The other Quest object to compare with.
 * @return True if the quests are equal, false otherwise.
 */
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