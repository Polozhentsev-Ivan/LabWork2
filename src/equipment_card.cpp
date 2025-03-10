#include "../include/equipment_card.h"

Equipment::Equipment(const std::string& name, const std::string& description, int value, Material material, int maxStackSize, int oneItemWeight, int weight, EquipmentType equipmentType, int durability, int maxDurability)
    : Item(name, description, value, material, maxStackSize, oneItemWeight, weight), equipmentType(equipmentType), durability(durability), maxDurability(maxDurability) {}

Equipment::Equipment() : Item(), equipmentType(EquipmentType::unknown), durability(0), maxDurability(0) {}

EquipmentType Equipment::getEquipmentType() const {
    return equipmentType;
}

int Equipment::getDurability() const {
    return durability;
}

int Equipment::getMaxDurability() const {
    return maxDurability;
}

void Equipment::setEquipmentType(EquipmentType equipmentType) {
    this->equipmentType = equipmentType;
}

void Equipment::setDurability(int durability) {
    this->durability = durability;
}

void Equipment::setMaxDurability(int maxDurability) {
    this->maxDurability = maxDurability;
}

Weapon::Weapon(const std::string& name, const std::string& description, int value, Material material, int maxStackSize, int oneItemWeight, int weight, int damage, int range, int durability, int maxDurability)
    : Equipment(name, description, value, material, maxStackSize, oneItemWeight, weight, EquipmentType::weapon, durability, maxDurability), damage(damage), range(range) {} 

Weapon::Weapon() : Equipment("","",1,Material::unknown,1,1,1,EquipmentType::weapon,0,0), damage(0), range(0) {}

void Weapon::setEquipmentType(EquipmentType equipmentType) {
    if (equipmentType != EquipmentType::weapon) {
        throw std::invalid_argument("Weapon can only have EquipmentType::weapon");
    }
    Equipment::setEquipmentType(equipmentType);
}

int Weapon::getDamage() const {
    return damage;
}

int Weapon::getRange() const {
    return range;
}

void Weapon::setDamage(int damage) {
    this->damage = damage;
}

void Weapon::setRange(int range) {
    this->range = range;
}

Armor::Armor(const std::string& name, const std::string& description, int value, Material material, int maxStackSize, int oneItemWeight, int weight, int defense, int durability, int maxDurability)
    : Equipment(name, description, value, material, maxStackSize, oneItemWeight, weight, EquipmentType::armor, durability, maxDurability), defense(defense) {}

Armor::Armor() : Equipment("","",1,Material::unknown,1,1,1,EquipmentType::armor,0,0), defense(0) {}

void Armor::setEquipmentType(EquipmentType equipmentType) {
    if (equipmentType != EquipmentType::armor) {
        throw std::invalid_argument("Armor can only have EquipmentType::armor");
    }
    Equipment::setEquipmentType(equipmentType);
}

int Armor::getDefense() const {
    return defense;
}   

void Armor::setDefense(int defense) {
    this->defense = defense;
}   

Accessory::Accessory(const std::string& name, const std::string& description, int value, Material material, int maxStackSize, int oneItemWeight, int weight, int bonusToHealth, int bonusToAttack, int bonusToDefense, int bonusToSpeed, int durability, int maxDurability)
    : Equipment(name, description, value, material, maxStackSize, oneItemWeight, weight, EquipmentType::accessory, durability, maxDurability), bonusToHealth(bonusToHealth), bonusToAttack(bonusToAttack), bonusToDefense(bonusToDefense), bonusToSpeed(bonusToSpeed) {}

Accessory::Accessory() : Equipment("","",1,Material::unknown,1,1,1,EquipmentType::accessory,0,0), bonusToHealth(0), bonusToAttack(0), bonusToDefense(0), bonusToSpeed(0) {}

void Accessory::setEquipmentType(EquipmentType equipmentType) {
    if (equipmentType != EquipmentType::accessory) {
        throw std::invalid_argument("Accessory can only have EquipmentType::accessory");
    }
    Equipment::setEquipmentType(equipmentType);
}

int Accessory::getBonusToHealth() const {
    return bonusToHealth;
}   

int Accessory::getBonusToAttack() const {
    return bonusToAttack;
}

int Accessory::getBonusToDefense() const {
    return bonusToDefense;
}

int Accessory::getBonusToSpeed() const {
    return bonusToSpeed;
}

void Accessory::setBonusToHealth(int bonusToHealth) {
    this->bonusToHealth = bonusToHealth;
}

void Accessory::setBonusToAttack(int bonusToAttack) {
    this->bonusToAttack = bonusToAttack;
}

void Accessory::setBonusToDefense(int bonusToDefense) {
    this->bonusToDefense = bonusToDefense;
}

void Accessory::setBonusToSpeed(int bonusToSpeed) {
    this->bonusToSpeed = bonusToSpeed;
}

