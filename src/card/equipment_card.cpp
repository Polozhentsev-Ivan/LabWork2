/**
 * @file equipment_card.cpp
 * @brief Implements the Equipment, Weapon, Armor, and Accessory class methods.
 */

#include "../../include/card/equipment_card.h"

/**
 * @brief Constructs an Equipment object with specified attributes.
 *
 * @param name The name of the equipment.
 * @param description The description of the equipment.
 * @param value The value of the equipment.
 * @param material The material of the equipment.
 * @param maxStackSize The maximum stack size of the equipment.
 * @param oneItemWeight The weight of a single item of this equipment.
 * @param weight The total weight of the equipment stack.
 * @param equipmentType The type of the equipment.
 * @param durability The current durability of the equipment.
 * @param maxDurability The maximum durability of the equipment.
 */
Equipment::Equipment(const std::string& name, const std::string& description, int value, Material material, int maxStackSize, int oneItemWeight, int weight, EquipmentType equipmentType, int durability, int maxDurability)
    : Item(name, description, value, material, maxStackSize, oneItemWeight, weight), equipmentType(equipmentType), durability(durability), maxDurability(maxDurability) {}

/**
 * @brief Default constructor for the Equipment class.
 *
 * Initializes with default item values, unknown equipment type, and zero durability.
 */
Equipment::Equipment() : Item(), equipmentType(EquipmentType::unknown), durability(0), maxDurability(0) {}

/**
 * @brief Gets the type of the equipment.
 *
 * @return The equipment type.
 */
EquipmentType Equipment::getEquipmentType() const {
    return equipmentType;
}

/**
 * @brief Gets the current durability of the equipment.
 *
 * @return The current durability.
 */
int Equipment::getDurability() const {
    return durability;
}

/**
 * @brief Gets the maximum durability of the equipment.
 *
 * @return The maximum durability.
 */
int Equipment::getMaxDurability() const {
    return maxDurability;
}

/**
 * @brief Sets the type of the equipment.
 *
 * @param equipmentType The new equipment type.
 */
void Equipment::setEquipmentType(EquipmentType equipmentType) {
    this->equipmentType = equipmentType;
}

/**
 * @brief Sets the current durability of the equipment.
 *
 * @param durability The new durability value.
 */
void Equipment::setDurability(int durability) {
    this->durability = durability;
}

/**
 * @brief Sets the maximum durability of the equipment.
 *
 * @param maxDurability The new maximum durability value.
 */
void Equipment::setMaxDurability(int maxDurability) {
    this->maxDurability = maxDurability;
}

/**
 * @brief Constructs a Weapon object with specified attributes.
 *
 * @param name The name of the weapon.
 * @param description The description of the weapon.
 * @param value The value of the weapon.
 * @param material The material of the weapon.
 * @param maxStackSize The maximum stack size of the weapon.
 * @param oneItemWeight The weight of a single item of this weapon.
 * @param weight The total weight of the weapon stack.
 * @param damage The damage dealt by the weapon.
 * @param range The range of the weapon.
 * @param durability The current durability of the weapon.
 * @param maxDurability The maximum durability of the weapon.
 */
Weapon::Weapon(const std::string& name, const std::string& description, int value, Material material, int maxStackSize, int oneItemWeight, int weight, int damage, int range, int durability, int maxDurability)
    : Equipment(name, description, value, material, maxStackSize, oneItemWeight, weight, EquipmentType::weapon, durability, maxDurability), damage(damage), range(range) {} 

/**
 * @brief Default constructor for the Weapon class.
 *
 * Initializes with default equipment values, weapon type, and zero damage/range.
 */
Weapon::Weapon() : Equipment("","",1,Material::unknown,1,1,1,EquipmentType::weapon,0,0), damage(0), range(0) {}

/**
 * @brief Sets the equipment type for the Weapon.
 *
 * Overrides the base class method to ensure the type is always `EquipmentType::weapon`.
 * @param equipmentType The equipment type to set. Must be `EquipmentType::weapon`.
 * @throws std::invalid_argument if `equipmentType` is not `EquipmentType::weapon`.
 */
void Weapon::setEquipmentType(EquipmentType equipmentType) {
    if (equipmentType != EquipmentType::weapon) {
        throw std::invalid_argument("Weapon can only have EquipmentType::weapon");
    }
    Equipment::setEquipmentType(equipmentType);
}

/**
 * @brief Gets the damage of the weapon.
 *
 * @return The damage value.
 */
int Weapon::getDamage() const {
    return damage;
}

/**
 * @brief Gets the range of the weapon.
 *
 * @return The range value.
 */
int Weapon::getRange() const {
    return range;
}

/**
 * @brief Sets the damage of the weapon.
 *
 * @param damage The new damage value.
 */
void Weapon::setDamage(int damage) {
    this->damage = damage;
}

/**
 * @brief Sets the range of the weapon.
 *
 * @param range The new range value.
 */
void Weapon::setRange(int range) {
    this->range = range;
}

/**
 * @brief Constructs an Armor object with specified attributes.
 *
 * @param name The name of the armor.
 * @param description The description of the armor.
 * @param value The value of the armor.
 * @param material The material of the armor.
 * @param maxStackSize The maximum stack size of the armor.
 * @param oneItemWeight The weight of a single item of this armor.
 * @param weight The total weight of the armor stack.
 * @param defense The defense provided by the armor.
 * @param durability The current durability of the armor.
 * @param maxDurability The maximum durability of the armor.
 */
Armor::Armor(const std::string& name, const std::string& description, int value, Material material, int maxStackSize, int oneItemWeight, int weight, int defense, int durability, int maxDurability)
    : Equipment(name, description, value, material, maxStackSize, oneItemWeight, weight, EquipmentType::armor, durability, maxDurability), defense(defense) {}

/**
 * @brief Default constructor for the Armor class.
 *
 * Initializes with default equipment values, armor type, and zero defense.
 */
Armor::Armor() : Equipment("","",1,Material::unknown,1,1,1,EquipmentType::armor,0,0), defense(0) {}

/**
 * @brief Sets the equipment type for the Armor.
 *
 * Overrides the base class method to ensure the type is always `EquipmentType::armor`.
 * @param equipmentType The equipment type to set. Must be `EquipmentType::armor`.
 * @throws std::invalid_argument if `equipmentType` is not `EquipmentType::armor`.
 */
void Armor::setEquipmentType(EquipmentType equipmentType) {
    if (equipmentType != EquipmentType::armor) {
        throw std::invalid_argument("Armor can only have EquipmentType::armor");
    }
    Equipment::setEquipmentType(equipmentType);
}

/**
 * @brief Gets the defense value of the armor.
 *
 * @return The defense value.
 */
int Armor::getDefense() const {
    return defense;
}   

/**
 * @brief Sets the defense value of the armor.
 *
 * @param defense The new defense value.
 */
void Armor::setDefense(int defense) {
    this->defense = defense;
}   

/**
 * @brief Constructs an Accessory object with specified attributes.
 *
 * @param name The name of the accessory.
 * @param description The description of the accessory.
 * @param value The value of the accessory.
 * @param material The material of the accessory.
 * @param maxStackSize The maximum stack size of the accessory.
 * @param oneItemWeight The weight of a single item of this accessory.
 * @param weight The total weight of the accessory stack.
 * @param bonusToHealth Bonus to health provided by the accessory.
 * @param bonusToAttack Bonus to attack provided by the accessory.
 * @param bonusToDefense Bonus to defense provided by the accessory.
 * @param bonusToSpeed Bonus to speed provided by the accessory.
 * @param durability The current durability of the accessory.
 * @param maxDurability The maximum durability of the accessory.
 */
Accessory::Accessory(const std::string& name, const std::string& description, int value, Material material, int maxStackSize, int oneItemWeight, int weight, int bonusToHealth, int bonusToAttack, int bonusToDefense, int bonusToSpeed, int durability, int maxDurability)
    : Equipment(name, description, value, material, maxStackSize, oneItemWeight, weight, EquipmentType::accessory, durability, maxDurability), bonusToHealth(bonusToHealth), bonusToAttack(bonusToAttack), bonusToDefense(bonusToDefense), bonusToSpeed(bonusToSpeed) {}

/**
 * @brief Default constructor for the Accessory class.
 *
 * Initializes with default equipment values, accessory type, and zero bonuses.
 */
Accessory::Accessory() : Equipment("","",1,Material::unknown,1,1,1,EquipmentType::accessory,0,0), bonusToHealth(0), bonusToAttack(0), bonusToDefense(0), bonusToSpeed(0) {}

/**
 * @brief Sets the equipment type for the Accessory.
 *
 * Overrides the base class method to ensure the type is always `EquipmentType::accessory`.
 * @param equipmentType The equipment type to set. Must be `EquipmentType::accessory`.
 * @throws std::invalid_argument if `equipmentType` is not `EquipmentType::accessory`.
 */
void Accessory::setEquipmentType(EquipmentType equipmentType) {
    if (equipmentType != EquipmentType::accessory) {
        throw std::invalid_argument("Accessory can only have EquipmentType::accessory");
    }
    Equipment::setEquipmentType(equipmentType);
}

/**
 * @brief Gets the bonus to health provided by the accessory.
 *
 * @return The health bonus.
 */
int Accessory::getBonusToHealth() const {
    return bonusToHealth;
}   

/**
 * @brief Gets the bonus to attack provided by the accessory.
 *
 * @return The attack bonus.
 */
int Accessory::getBonusToAttack() const {
    return bonusToAttack;
}

/**
 * @brief Gets the bonus to defense provided by the accessory.
 *
 * @return The defense bonus.
 */
int Accessory::getBonusToDefense() const {
    return bonusToDefense;
}

/**
 * @brief Gets the bonus to speed provided by the accessory.
 *
 * @return The speed bonus.
 */
int Accessory::getBonusToSpeed() const {
    return bonusToSpeed;
}

/**
 * @brief Sets the bonus to health provided by the accessory.
 *
 * @param bonusToHealth The new health bonus.
 */
void Accessory::setBonusToHealth(int bonusToHealth) {
    this->bonusToHealth = bonusToHealth;
}

/**
 * @brief Sets the bonus to attack provided by the accessory.
 *
 * @param bonusToAttack The new attack bonus.
 */
void Accessory::setBonusToAttack(int bonusToAttack) {
    this->bonusToAttack = bonusToAttack;
}

/**
 * @brief Sets the bonus to defense provided by the accessory.
 *
 * @param bonusToDefense The new defense bonus.
 */
void Accessory::setBonusToDefense(int bonusToDefense) {
    this->bonusToDefense = bonusToDefense;
}

/**
 * @brief Sets the bonus to speed provided by the accessory.
 *
 * @param bonusToSpeed The new speed bonus.
 */
void Accessory::setBonusToSpeed(int bonusToSpeed) {
    this->bonusToSpeed = bonusToSpeed;
}

