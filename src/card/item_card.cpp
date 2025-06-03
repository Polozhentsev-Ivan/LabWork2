/**
 * @file item_card.cpp
 * @brief Implements the Item class methods.
 */

#include "../../include/card/item_card.h"


/**
 * @brief Constructs an Item object with specified attributes.
 *
 * @param name The name of the item.
 * @param description The description of the item.
 * @param value The value of the item.
 * @param material The material of the item.
 * @param maxStackSize The maximum stack size of the item.
 * @param oneItemWeight The weight of a single unit of this item.
 * @param weight The total weight of the item stack.
 */
Item::Item(const std::string& name, const std::string& description, int value, Material material, int maxStackSize, int oneItemWeight, int weight)
    : Card(name, description), value(value), material(material), maxStackSize(maxStackSize), 
      oneItemWeight(oneItemWeight), weight(weight) {}
/**
 * @brief Default constructor for the Item class.
 *
 * Initializes with default card values, zero value, unknown material, and zero stack/weight attributes.
 */
Item::Item() : Card(), value(0), material(Material::unknown), maxStackSize(0), oneItemWeight(0), weight(0) {}

/**
 * @brief Gets the value of the item.
 *
 * @return The item's value.
 */
int Item::getValue() const {
    return value;
}

/**
 * @brief Gets the material of the item.
 *
 * @return The item's material.
 */
Material Item::getMaterial() const {
    return material;
}

/**
 * @brief Gets the maximum stack size for this item.
 *
 * @return The maximum stack size.
 */
int Item::getMaxStackSize() const {
    return maxStackSize;
}

/**
 * @brief Gets the weight of a single unit of this item.
 *
 * @return The weight of one item.
 */
int Item::getOneItemWeight() const {
    return oneItemWeight;
}

/**
 * @brief Gets the total weight of the current stack of this item.
 *
 * @return The total weight.
 */
int Item::getWeight() const {
    return weight;
}


/**
 * @brief Sets the value of the item.
 *
 * @param value The new value for the item.
 */
void Item::setValue(int value) {
    this->value = value;
}

/**
 * @brief Sets the material of the item.
 *
 * @param material The new material for the item.
 */
void Item::setMaterial(Material material) {
    this->material = material;
}

/**
 * @brief Sets the maximum stack size for this item.
 *
 * @param maxStackSize The new maximum stack size.
 */
void Item::setMaxStackSize(int maxStackSize) {
    this->maxStackSize = maxStackSize;
}

/**
 * @brief Sets the weight of a single unit of this item.
 *
 * @param oneItemWeight The new weight for one item.
 */
void Item::setOneItemWeight(int oneItemWeight) {
    this->oneItemWeight = oneItemWeight;
}

/**
 * @brief Sets the total weight of the current stack of this item.
 *
 * @param weight The new total weight.
 */
void Item::setWeight(int weight) {
    this->weight = weight;
}
