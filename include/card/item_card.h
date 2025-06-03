#ifndef ITEM_CARD_H
#define ITEM_CARD_H
#include "card.h"
#include "../enums.h"

/**
 * @brief Represents a generic item card in the game.
 * 
 * This class inherits from Card and provides common attributes for all items,
 * such as value, material, stack size, and weight.
 */
class Item: public Card
{
    protected:
        int value;          /**< The value of the item in silver. */
        Material material;  /**< The material the item is made of. */
        int maxStackSize;   /**< The maximum number of this item that can be stacked. */
        int oneItemWeight;  /**< The weight of a single item. */
        int weight;         /**< The total weight of the item stack. */
    public:
        /**
         * @brief Constructs an Item with specified attributes.
         *
         * @param name The name of the item.
         * @param description A description of the item.
         * @param value The value of the item in silver.
         * @param material The material the item is made of.
         * @param maxStackSize The maximum number of this item that can be stacked.
         * @param oneItemWeight The weight of a single item.
         * @param weight The total weight of the item stack.
         */
        Item(const std::string& name, const std::string& description, int value, Material material, int maxStackSize, int oneItemWeight, int weight);
        /**
         * @brief Default constructor for Item.
         */
        Item();
        /**
         * @brief Gets the value of the item in silver.
         * @return The value of the item.
         */
        int getValue() const;
        /**
         * @brief Gets the material of the item.
         * @return The material of the item.
         */
        Material getMaterial() const;
        /**
         * @brief Gets the maximum stack size for the item.
         * @return The maximum stack size.
         */
        int getMaxStackSize() const;
        /**
         * @brief Gets the weight of a single item.
         * @return The weight of one item.
         */
        int getOneItemWeight() const;
        /**
         * @brief Gets the total weight of the item stack.
         * @return The total weight.
         */
        int getWeight() const;
        /**
         * @brief Sets the value of the item in silver.
         * @param value The new value for the item.
         */
        void setValue(int value);
        /**
         * @brief Sets the material of the item.
         * @param material The new material for the item.
         */
        void setMaterial(Material material);
        /**
         * @brief Sets the maximum stack size for the item.
         * @param maxStackSize The new maximum stack size.
         */
        void setMaxStackSize(int maxStackSize);
        /**
         * @brief Sets the weight of a single item.
         * @param oneItemWeight The new weight for one item.
         */
        void setOneItemWeight(int oneItemWeight);
        /**
         * @brief Sets the total weight of the item stack.
         * @param weight The new total weight.
         */
        void setWeight(int weight);

};

#endif // ITEM_CARD_H