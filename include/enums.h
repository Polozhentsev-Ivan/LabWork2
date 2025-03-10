#ifndef ENUMS_H
#define ENUMS_H

enum class Material 
{
    wood,
    metal,
    dirt,
    stone,
    glass,
    leather,
    cloth,
    unknown,
    iron,
};

enum class Hostility
{
    hostile,
    neutral,
    friendly,
    unknown,
};

enum class Race
{
    human,
    elf,
    dwarf,
    orc,
    unknown,
};

enum class Species
{
    goblin,
    orc,
    troll,
    zombie,
    unknown,
    
};

enum class QuestType
{
    kill,
    collect,
    unknown,
};

enum class EquipmentType
{
    weapon,
    armor,
    accessory,
    unknown,
};

#endif // ENUMS_H