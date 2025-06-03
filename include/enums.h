#ifndef ENUMS_H
#define ENUMS_H

/**
 * @brief Defines different types of materials for items or objects.
 */
enum class Material 
{
    wood,       /**< Wood material. */
    metal,      /**< Metal material. */
    dirt,       /**< Dirt material. */
    stone,      /**< Stone material. */
    glass,      /**< Glass material. */
    leather,    /**< Leather material. */
    cloth,      /**< Cloth material. */
    unknown,    /**< Unknown or unspecified material. */
    iron,       /**< Iron material. */
};

/**
 * @brief Defines the hostility levels of NPCs or creatures.
 */
enum class Hostility
{
    hostile,    /**< The entity is hostile and will attack. */
    neutral,    /**< The entity is neutral and will not attack unless provoked. */
    friendly,   /**< The entity is friendly. */
    unknown,    /**< Unknown or unspecified hostility. */
};

/**
 * @brief Defines different races for characters.
 */
enum class Race
{
    human,      /**< Human race. */
    elf,        /**< Elf race. */
    dwarf,      /**< Dwarf race. */
    orc,        /**< Orc race. */
    unknown,    /**< Unknown or unspecified race. */
};

/**
 * @brief Defines different species, typically for monsters or creatures.
 */
enum class Species
{
    goblin,     /**< Goblin species. */
    orc,        /**< Orc species (can be different from Race::orc). */
    troll,      /**< Troll species. */
    zombie,     /**< Zombie species. */
    unknown,    /**< Unknown or unspecified species. */
    
};

/**
 * @brief Defines different types of quests.
 */
enum class QuestType
{
    kill,       /**< A quest that requires killing specific targets. */
    collect,    /**< A quest that requires collecting specific items. */
    unknown,    /**< Unknown or unspecified quest type. */
};

/**
 * @brief Defines different types of equipment.
 */
enum class EquipmentType
{
    weapon,     /**< Weapon type equipment. */
    armor,      /**< Armor type equipment. */
    accessory,  /**< Accessory type equipment. */
    unknown,    /**< Unknown or unspecified equipment type. */
};

#endif // ENUMS_H