#include <gtest/gtest.h>
#include "../include/card/card.h"
#include "../include/card/task.h"
#include "../include/card/quests_card.h"
#include "../include/enums.h"
#include "../include/card/character_card.h"
#include "../include/card/player_card.h"
#include "../include/card/monster_card.h"
#include "../include/card/npc_card.h"
#include "../include/card/item_card.h"
#include "../include/card/equipment_card.h"
#include "../include/card/environment_card.h"

TEST(CardTest, ConstructorGettersSetters) {
    Card card("Test Card", "Test Description");
    EXPECT_EQ(card.getName(), "Test Card");
    EXPECT_EQ(card.getDescription(), "Test Description");
    card.setName("New Test Card");
    card.setDescription("New Test Description");
    EXPECT_EQ(card.getName(), "New Test Card");
    EXPECT_EQ(card.getDescription(), "New Test Description");
}

TEST(TaskTest, ConstructorGettersSetters) {
    Task task("Test Task", 0, 10, QuestType::unknown);
    EXPECT_EQ(task.getDescription(), "Test Task");
    EXPECT_EQ(task.getCounter(), 0);
    EXPECT_EQ(task.getMaxCounter(), 10);
    EXPECT_EQ(task.getQuestType(), QuestType::unknown);
    EXPECT_EQ(task.getIsCompleted(), false);
    
    task.setDescription("New Test Task");
    task.setCounter(5);
    task.setMaxCounter(15);
    task.setQuestType(QuestType::kill);
    task.setIsCompleted(true);
    
    EXPECT_EQ(task.getDescription(), "New Test Task");
    EXPECT_EQ(task.getCounter(), 5);
    EXPECT_EQ(task.getMaxCounter(), 15);
    EXPECT_EQ(task.getQuestType(), QuestType::kill);
    EXPECT_EQ(task.getIsCompleted(), true);
    
    task.resetCounter();
    task.setIsCompleted(task.checkCompletion());
    EXPECT_EQ(task.getCounter(), 0);
    EXPECT_EQ(task.getIsCompleted(), false);
    
    task.setCounter(task.getMaxCounter());
    task.setIsCompleted(task.checkCompletion());
    EXPECT_EQ(task.checkCompletion(), true);
    EXPECT_EQ(task.getIsCompleted(), true);
    
    task.setMaxCounter(task.getMaxCounter() + 1);
    task.setIsCompleted(task.checkCompletion());
    EXPECT_EQ(task.checkCompletion(), false);
    EXPECT_EQ(task.getIsCompleted(), false);
}

TEST(TaskTest, CollectTaskGettersSetters) {
    CollectTask collectTask("Test Collect Task", 0, 10, "Test Item");
    EXPECT_EQ(collectTask.getQuestType(), QuestType::collect);
    EXPECT_EQ(collectTask.getItemName(), "Test Item");
    collectTask.setItemName("New Test Item");
    EXPECT_EQ(collectTask.getItemName(), "New Test Item");
    EXPECT_THROW(collectTask.setQuestType(QuestType::kill), std::invalid_argument);
}

TEST(TaskTest, KillTaskGettersSetters) {
    KillTask killTask("Test Kill Task", 0, 10, "Test Enemy");
    EXPECT_EQ(killTask.getQuestType(), QuestType::kill);
    EXPECT_EQ(killTask.getEnemyName(), "Test Enemy");
    killTask.setEnemyName("New Test Enemy");
    EXPECT_EQ(killTask.getEnemyName(), "New Test Enemy");
    EXPECT_THROW(killTask.setQuestType(QuestType::collect), std::invalid_argument);
}

TEST(QuestTest, ConstructorGettersSetters) {
    Quest quest("Test Quest", "Test Description", QuestType::unknown, 100, 5, 1000);
    EXPECT_EQ(quest.getName(), "Test Quest");
    EXPECT_EQ(quest.getDescription(), "Test Description");
    EXPECT_EQ(quest.getQuestType(), QuestType::unknown);
    EXPECT_EQ(quest.getExperienceReward(), 100);
    EXPECT_EQ(quest.getDifficulty(), 5);
    EXPECT_EQ(quest.getSilverReward(), 1000);
    
    quest.setName("New Test Quest");
    quest.setDescription("New Test Description");
    quest.setQuestType(QuestType::kill);
    quest.setExperienceReward(200);
    quest.setDifficulty(10);
    quest.setSilverReward(2000);
    
    EXPECT_EQ(quest.getName(), "New Test Quest");
    EXPECT_EQ(quest.getDescription(), "New Test Description");
    EXPECT_EQ(quest.getQuestType(), QuestType::kill);
    EXPECT_EQ(quest.getExperienceReward(), 200);
    EXPECT_EQ(quest.getDifficulty(), 10);
    EXPECT_EQ(quest.getSilverReward(), 2000);
    
    auto item = std::make_shared<Item>();
    quest.addItemToReward(item);
    EXPECT_EQ(quest.getItemReward().size(), 1);
    EXPECT_EQ(quest.getItemReward()[0]->getName(), "");
    EXPECT_EQ(quest.getItemReward()[0]->getDescription(), "");
    quest.removeItemFromReward(item);
    EXPECT_EQ(quest.getItemReward().size(), 0);
    
    auto task = std::make_shared<Task>();
    quest.addTask(task);
    EXPECT_EQ(quest.getTasks().size(), 1);
    EXPECT_EQ(quest.getTasks()[0]->getDescription(), "");
    quest.removeTask(task);
    EXPECT_EQ(quest.getTasks().size(), 0);
}

TEST(QuestTest, GatheringQuestGettersSetters) {
    GatheringQuest gatheringQuest("Test Gathering Quest", "Test Description", 100, 5, 1000);
    EXPECT_EQ(gatheringQuest.getQuestType(), QuestType::collect);
    EXPECT_EQ(gatheringQuest.getTasks().size(), 0);
    EXPECT_THROW(gatheringQuest.setQuestType(QuestType::kill), std::invalid_argument);
} 

TEST(QuestTest, HuntingQuestGettersSetters) {
    HuntingQuest huntingQuest("Test Hunting Quest", "Test Description", 100, 5, 1000);
    EXPECT_EQ(huntingQuest.getQuestType(), QuestType::kill);
    EXPECT_EQ(huntingQuest.getTasks().size(), 0);
    EXPECT_THROW(huntingQuest.setQuestType(QuestType::collect), std::invalid_argument);
}

TEST(CharacterTest, ConstructorGettersSetters) {
    CharacterCard characterCard("Test Character", "Test Description", 100, 100, 10, 5, 1);
    EXPECT_EQ(characterCard.getName(), "Test Character");
    EXPECT_EQ(characterCard.getDescription(), "Test Description");
    EXPECT_EQ(characterCard.getHealth(), 100);
    EXPECT_EQ(characterCard.getMaxHealth(), 100);
    EXPECT_EQ(characterCard.getAttack(), 10);
    EXPECT_EQ(characterCard.getDefense(), 5);
    EXPECT_EQ(characterCard.getSpeed(), 1);
    characterCard.setHealth(200);
    EXPECT_EQ(characterCard.getHealth(), 200);
    characterCard.setMaxHealth(200);
    EXPECT_EQ(characterCard.getMaxHealth(), 200);
    characterCard.setAttack(20);
    EXPECT_EQ(characterCard.getAttack(), 20);
    characterCard.setDefense(10);
    EXPECT_EQ(characterCard.getDefense(), 10);
    characterCard.setSpeed(2);
    EXPECT_EQ(characterCard.getSpeed(), 2);
}

TEST(PlayerTest, ConstructorGettersSetters) {
    PlayerCard playerCard("Test Player", "Test Description", 100, 100, 10, 5, 1, Race::human, 1, 0, 100, 0);
    EXPECT_EQ(playerCard.getRace(), Race::human);
    EXPECT_EQ(playerCard.getLevel(), 1);
    EXPECT_EQ(playerCard.getExperience(), 0);
    EXPECT_EQ(playerCard.getExperienceToNextLevel(), 100);
    EXPECT_EQ(playerCard.getSilver(), 0);
    
    playerCard.setRace(Race::elf);
    EXPECT_EQ(playerCard.getRace(), Race::elf);
    
    playerCard.setLevel(2);
    EXPECT_EQ(playerCard.getLevel(), 2);
    
    playerCard.addExperience(50);
    EXPECT_EQ(playerCard.getExperience(), 50);
    
    playerCard.levelUp();
    EXPECT_EQ(playerCard.getLevel(), 3);
    
    playerCard.setExperienceToNextLevel(200);
    EXPECT_EQ(playerCard.getExperienceToNextLevel(), 200);
    
    playerCard.setSilver(100);
    EXPECT_EQ(playerCard.getSilver(), 100);
    
    playerCard.addSilver(50);
    EXPECT_EQ(playerCard.getSilver(), 150);
    
    playerCard.removeSilver(100);
    EXPECT_EQ(playerCard.getSilver(), 50);
    
    EXPECT_THROW(playerCard.addExperience(-100), std::invalid_argument);
}

TEST(MonsterTest, ConstructorGettersSetters) {   
    MonsterCard monsterCard("Test Monster", "Test Description", 100, 100, 10, 5, 1, Species::unknown, 1, 0, 100);
    EXPECT_EQ(monsterCard.getSpecies(), Species::unknown);
    EXPECT_EQ(monsterCard.getLevel(), 1);
    EXPECT_EQ(monsterCard.getExperience(), 0);
    EXPECT_EQ(monsterCard.getSilver(), 100);
    monsterCard.setSpecies(Species::zombie);
    EXPECT_EQ(monsterCard.getSpecies(), Species::zombie);
    monsterCard.setLevel(2);
    EXPECT_EQ(monsterCard.getLevel(), 2);
    monsterCard.setExperience(50);
    EXPECT_EQ(monsterCard.getExperience(), 50);
    monsterCard.setSilver(100);
    EXPECT_EQ(monsterCard.getSilver(), 100);
}

TEST(NPC, ConstructorGettersSetters) {
    NPCCard npcCard("Test NPC", "Test Description", 100, 100, 10, 5, 1, Hostility::friendly, Race::human);
    EXPECT_EQ(npcCard.getHostility(), Hostility::friendly);
    EXPECT_EQ(npcCard.getRace(), Race::human);
    npcCard.addQuest(Quest("Test Quest", "Test Description", QuestType::unknown, 100, 5, 1000));
    EXPECT_EQ(npcCard.getQuests().size(), 1);
    EXPECT_EQ(npcCard.getQuests()[0].getName(), "Test Quest");
    npcCard.removeQuest(Quest("Test Quest", "Test Description", QuestType::unknown, 100, 5, 1000));
    EXPECT_EQ(npcCard.getQuests().size(), 0);   
    npcCard.setHostility(Hostility::hostile);
    EXPECT_EQ(npcCard.getHostility(), Hostility::hostile);
    npcCard.setRace(Race::elf);
    EXPECT_EQ(npcCard.getRace(), Race::elf);
}

TEST(ItemTest, ConstructorGettersSetters) {
    Item item("Test Item", "Test Description", 100, Material::wood, 10, 1, 10);
    EXPECT_EQ(item.getName(), "Test Item");
    EXPECT_EQ(item.getDescription(), "Test Description");
    EXPECT_EQ(item.getValue(), 100);
    EXPECT_EQ(item.getMaterial(), Material::wood);
    EXPECT_EQ(item.getMaxStackSize(), 10);
    EXPECT_EQ(item.getOneItemWeight(), 1);
    EXPECT_EQ(item.getWeight(), 10);
    item.setValue(200);
    EXPECT_EQ(item.getValue(), 200);
    item.setMaterial(Material::stone);
    EXPECT_EQ(item.getMaterial(), Material::stone);
    item.setMaxStackSize(20);
    EXPECT_EQ(item.getMaxStackSize(), 20);
    item.setOneItemWeight(2);
    EXPECT_EQ(item.getOneItemWeight(), 2);
    item.setWeight(20);
    EXPECT_EQ(item.getWeight(), 20);
}

TEST(EquipmentTest, ConstructorGettersSetters) {
    Equipment equipment("Test Equipment", "Test Description", 100, Material::wood, 10, 1, 10, EquipmentType::unknown, 0, 0);
    EXPECT_EQ(equipment.getEquipmentType(), EquipmentType::unknown);
    EXPECT_EQ(equipment.getDurability(), 0);
    EXPECT_EQ(equipment.getMaxDurability(), 0);
    equipment.setEquipmentType(EquipmentType::weapon);
    EXPECT_EQ(equipment.getEquipmentType(), EquipmentType::weapon);
    Weapon weapon("Test Weapon", "Test Description", 100, Material::wood, 10, 1, 10, 10, 10, 100, 100);
    EXPECT_EQ(weapon.getEquipmentType(), EquipmentType::weapon);
    EXPECT_EQ(weapon.getDurability(), 100);
    EXPECT_EQ(weapon.getMaxDurability(), 100);
    weapon.setEquipmentType(EquipmentType::weapon);
    EXPECT_EQ(weapon.getEquipmentType(), EquipmentType::weapon);
    weapon.setDurability(200);
    EXPECT_EQ(weapon.getDurability(), 200);
    weapon.setMaxDurability(200);
    EXPECT_EQ(weapon.getMaxDurability(), 200);
    weapon.setDamage(10);
    EXPECT_EQ(weapon.getDamage(), 10);
    weapon.setRange(10);
    EXPECT_EQ(weapon.getRange(), 10);
    Armor armor("Test Armor", "Test Description", 100, Material::wood, 10, 1, 10, 10, 100, 100);
    EXPECT_EQ(armor.getEquipmentType(), EquipmentType::armor);
    EXPECT_EQ(armor.getDurability(), 100);
    EXPECT_EQ(armor.getMaxDurability(), 100);
    armor.setEquipmentType(EquipmentType::armor);
    EXPECT_EQ(armor.getEquipmentType(), EquipmentType::armor);
    armor.setDurability(200);
    EXPECT_EQ(armor.getDurability(), 200);
    armor.setMaxDurability(200);
    EXPECT_EQ(armor.getMaxDurability(), 200);
    armor.setDefense(10);
    EXPECT_EQ(armor.getDefense(), 10);
    Accessory accessory("Test Accessory", "Test Description", 100, Material::wood, 10, 1, 10, 10, 10, 10, 100, 100, 100);
    EXPECT_EQ(accessory.getEquipmentType(), EquipmentType::accessory);
    EXPECT_EQ(accessory.getDurability(), 100);
    EXPECT_EQ(accessory.getMaxDurability(), 100);
    accessory.setEquipmentType(EquipmentType::accessory);
    EXPECT_EQ(accessory.getEquipmentType(), EquipmentType::accessory);
    accessory.setDurability(200);
    EXPECT_EQ(accessory.getDurability(), 200);
    accessory.setMaxDurability(200);
    EXPECT_EQ(accessory.getMaxDurability(), 200);
    accessory.setBonusToHealth(10);
    EXPECT_EQ(accessory.getBonusToHealth(), 10);
    accessory.setBonusToAttack(10);
    EXPECT_EQ(accessory.getBonusToAttack(), 10);
    accessory.setBonusToDefense(10);
    EXPECT_EQ(accessory.getBonusToDefense(), 10);
    accessory.setBonusToSpeed(10);
    EXPECT_EQ(accessory.getBonusToSpeed(), 10);
}

TEST(EnvironmentTest, ConstructorGettersSetters) {
    EnvironmentCard environmentCard("Test Environment", "Test Description", Material::wood);
    EXPECT_EQ(environmentCard.getMaterial(), Material::wood);
    environmentCard.setMaterial(Material::stone);
    EXPECT_EQ(environmentCard.getMaterial(), Material::stone);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
