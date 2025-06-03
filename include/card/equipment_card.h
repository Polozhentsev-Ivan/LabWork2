#ifndef EQUIPMENT_CARD_H
#define EQUIPMENT_CARD_H
#include "item_card.h"
#include "../enums.h"

/**
 * @brief Represents a generic equipment item in the game.
 * 
 * This class inherits from Item and serves as a base for specific equipment types
 * like weapons, armor, and accessories. It includes common equipment attributes
 * such as equipment type and durability.
 */
class Equipment: public Item
{
    protected:
        EquipmentType equipmentType; /**< The type of the equipment (e.g., Weapon, Armor). */
        int durability;              /**< The current durability of the equipment. */
        int maxDurability;           /**< The maximum durability of the equipment. */
    public:
        /**
         * @brief Constructs an Equipment item with specified attributes.
         *
         * @param name The name of the equipment.
         * @param description A description of the equipment.
         * @param value The value of the equipment in silver.
         * @param material The material the equipment is made of.
         * @param maxStackSize The maximum number of this item that can be stacked.
         * @param oneItemWeight The weight of a single item.
         * @param weight The total weight of the item stack.
         * @param equipmentType The type of the equipment.
         * @param durability The current durability of the equipment.
         * @param maxDurability The maximum durability of the equipment.
         */
        Equipment(const std::string& name, const std::string& description, int value, Material material, int maxStackSize, int oneItemWeight, int weight, EquipmentType equipmentType, int durability, int maxDurability);
        /**
         * @brief Default constructor for Equipment.
         */
        Equipment();
        /**
         * @brief Gets the type of the equipment.
         * @return The equipment type.
         */
        EquipmentType getEquipmentType() const;
        /**
         * @brief Gets the current durability of the equipment.
         * @return The current durability.
         */
        int getDurability() const;
        /**
         * @brief Gets the maximum durability of the equipment.
         * @return The maximum durability.
         */
        int getMaxDurability() const;
        /**
         * @brief Sets the type of the equipment.
         * @param equipmentType The new equipment type.
         */
        void setEquipmentType(EquipmentType equipmentType);
        /**
         * @brief Sets the current durability of the equipment.
         * @param durability The new durability value.
         */
        void setDurability(int durability);
        /**
         * @brief Sets the maximum durability of the equipment.
         * @param maxDurability The new maximum durability value.
         */
        void setMaxDurability(int maxDurability);
};
/**
 * @brief Represents a weapon in the game.
 * 
 * This class inherits from Equipment and adds attributes specific to weapons,
 * such as damage and range.
 */
class Weapon: public Equipment
{
    private:
        int damage; /**< The damage dealt by the weapon. */
        int range;  /**< The attack range of the weapon. */
    public:
        /**
         * @brief Constructs a Weapon with specified attributes.
         *
         * @param name The name of the weapon.
         * @param description A description of the weapon.
         * @param value The value of the weapon in silver.
         * @param material The material the weapon is made of.
         * @param maxStackSize The maximum number of this weapon that can be stacked.
         * @param oneItemWeight The weight of a single weapon.
         * @param weight The total weight of the weapon stack.
         * @param damage The damage dealt by the weapon.
         * @param range The attack range of the weapon.
         * @param durability The current durability of the weapon.
         * @param maxDurability The maximum durability of the weapon.
         */
        Weapon(const std::string& name, const std::string& description, int value, Material material, int maxStackSize, int oneItemWeight, int weight, int damage, int range, int durability, int maxDurability);
        /**
         * @brief Default constructor for Weapon.
         */
        Weapon();
        /**
         * @brief Gets the damage dealt by the weapon.
         * @return The damage value.
         */
        int getDamage() const;
        /**
         * @brief Gets the attack range of the weapon.
         * @return The range value.
         */
        int getRange() const;
        /**
         * @brief Sets the damage dealt by the weapon.
         * @param damage The new damage value.
         */
        void setDamage(int damage);
        /**
         * @brief Sets the attack range of the weapon.
         * @param range The new range value.
         */
        void setRange(int range);
        /**
         * @brief Sets the type of the equipment.
         * @param equipmentType The new equipment type.
         */
        void setEquipmentType(EquipmentType equipmentType);
};

/**
 * @brief Represents an armor item in the game.
 * 
 * This class inherits from Equipment and adds attributes specific to armor,
 * such as defense power.
 */
class Armor: public Equipment
{
    private:
        int defense; /**< The defense power provided by the armor. */
    public:
        /**
         * @brief Constructs an Armor item with specified attributes.
         *
         * @param name The name of the armor.
         * @param description A description of the armor.
         * @param value The value of the armor in silver.
         * @param material The material the armor is made of.
         * @param maxStackSize The maximum number of this armor that can be stacked.
         * @param oneItemWeight The weight of a single armor piece.
         * @param weight The total weight of the armor stack.
         * @param defense The defense power provided by the armor.
         * @param durability The current durability of the armor.
         * @param maxDurability The maximum durability of the armor.
         */
        Armor(const std::string& name, const std::string& description, int value, Material material, int maxStackSize, int oneItemWeight, int weight, int defense, int durability, int maxDurability);
        /**
         * @brief Default constructor for Armor.
         */
        Armor();
        /**
         * @brief Gets the defense power provided by the armor.
         * @return The defense value.
         */
        int getDefense() const;
        /**
         * @brief Sets the defense power provided by the armor.
         * @param defense The new defense value.
         */
        void setDefense(int defense);
        /**
         * @brief Sets the type of the equipment.
         * @param equipmentType The new equipment type.
         */
        void setEquipmentType(EquipmentType equipmentType);
};
/**
 * @brief Represents an accessory item in the game.
 * 
 * This class inherits from Equipment and adds attributes specific to accessories,
 * such as bonuses to health, attack, defense, and speed.
 */
class Accessory: public Equipment
{
    private:
        int bonusToHealth;  /**< Bonus to health provided by the accessory. */
        int bonusToAttack;  /**< Bonus to attack provided by the accessory. */
        int bonusToDefense; /**< Bonus to defense provided by the accessory. */
        int bonusToSpeed;   /**< Bonus to speed provided by the accessory. */
    public:
        /**
         * @brief Constructs an Accessory with specified attributes.
         *
         * @param name The name of the accessory.
         * @param description A description of the accessory.
         * @param value The value of the accessory in silver.
         * @param material The material the accessory is made of.
         * @param maxStackSize The maximum number of this accessory that can be stacked.
         * @param oneItemWeight The weight of a single accessory.
         * @param weight The total weight of the accessory stack.
         * @param bonusToHealth Bonus to health.
         * @param bonusToAttack Bonus to attack.
         * @param bonusToDefense Bonus to defense.
         * @param bonusToSpeed Bonus to speed.
         * @param durability The current durability of the accessory.
         * @param maxDurability The maximum durability of the accessory.
         */
        Accessory(const std::string& name, const std::string& description, int value, Material material, int maxStackSize, int oneItemWeight, int weight, int bonusToHealth, int bonusToAttack, int bonusToDefense, int bonusToSpeed, int durability, int maxDurability);
        /**
         * @brief Default constructor for Accessory.
         */
        Accessory();
        /**
         * @brief Gets the bonus to health provided by the accessory.
         * @return The health bonus.
         */
        int getBonusToHealth() const;   
        /**
         * @brief Gets the bonus to attack provided by the accessory.
         * @return The attack bonus.
         */
        int getBonusToAttack() const;
        /**
         * @brief Gets the bonus to defense provided by the accessory.
         * @return The defense bonus.
         */
        int getBonusToDefense() const;
        /**
         * @brief Gets the bonus to speed provided by the accessory.
         * @return The speed bonus.
         */
        int getBonusToSpeed() const;
        /**
         * @brief Sets the bonus to health provided by the accessory.
         * @param bonusToHealth The new health bonus value.
         */
        void setBonusToHealth(int bonusToHealth);
        /**
         * @brief Sets the bonus to attack provided by the accessory.
         * @param bonusToAttack The new attack bonus value.
         */
        void setBonusToAttack(int bonusToAttack);
        /**
         * @brief Sets the bonus to defense provided by the accessory.
         * @param bonusToDefense The new defense bonus value.
         */
        void setBonusToDefense(int bonusToDefense);
        /**
         * @brief Sets the bonus to speed provided by the accessory.
         * @param bonusToSpeed The new speed bonus value.
         */
        void setBonusToSpeed(int bonusToSpeed); 
        /**
         * @brief Sets the type of the equipment.
         * @param equipmentType The new equipment type.
         */
        void setEquipmentType(EquipmentType equipmentType);
};

#endif // EQUIPMENT_CARD_H
