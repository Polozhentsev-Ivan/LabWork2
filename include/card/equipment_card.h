#ifndef EQUIPMENT_CARD_H
#define EQUIPMENT_CARD_H
#include "item_card.h"
#include "../enums.h"

class Equipment: public Item
{
    protected:
        EquipmentType equipmentType;
        int durability;
        int maxDurability;
    public:
        Equipment(const std::string& name, const std::string& description, int value, Material material, int maxStackSize, int oneItemWeight, int weight, EquipmentType equipmentType, int durability, int maxDurability);
        Equipment();
        EquipmentType getEquipmentType() const;
        int getDurability() const;
        int getMaxDurability() const;
        void setEquipmentType(EquipmentType equipmentType);
        void setDurability(int durability);
        void setMaxDurability(int maxDurability);
};
class Weapon: public Equipment
{
    private:
        int damage;
        int range;
    public:
        Weapon(const std::string& name, const std::string& description, int value, Material material, int maxStackSize, int oneItemWeight, int weight, int damage, int range, int durability, int maxDurability);
        Weapon();
        int getDamage() const;
        int getRange() const;
        void setDamage(int damage);
        void setRange(int range);
        void setEquipmentType(EquipmentType equipmentType);
};

class Armor: public Equipment
{
    private:
        int defense;
    public:
        Armor(const std::string& name, const std::string& description, int value, Material material, int maxStackSize, int oneItemWeight, int weight, int defense, int durability, int maxDurability);
        Armor();
        int getDefense() const;
        void setDefense(int defense);
        void setEquipmentType(EquipmentType equipmentType);
};
class Accessory: public Equipment
{
    private:
        int bonusToHealth;
        int bonusToAttack;
        int bonusToDefense;
        int bonusToSpeed;
    public:
        Accessory(const std::string& name, const std::string& description, int value, Material material, int maxStackSize, int oneItemWeight, int weight, int bonusToHealth, int bonusToAttack, int bonusToDefense, int bonusToSpeed, int durability, int maxDurability);
        Accessory();
        int getBonusToHealth() const;   
        int getBonusToAttack() const;
        int getBonusToDefense() const;
        int getBonusToSpeed() const;
        void setBonusToHealth(int bonusToHealth);
        void setBonusToAttack(int bonusToAttack);
        void setBonusToDefense(int bonusToDefense);
        void setBonusToSpeed(int bonusToSpeed); 
        void setEquipmentType(EquipmentType equipmentType);
};

#endif // EQUIPMENT_CARD_H
