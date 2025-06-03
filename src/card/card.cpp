/**
 * @file card.cpp
 * @brief Implements the Card class methods.
 */

#include "../../include/card/card.h"

/**
 * @brief Constructs a Card object with a specified name and description.
 *
 * @param name The name of the card.
 * @param description The description of the card.
 */
Card::Card(const std::string& name, const std::string& description)
    : name(name), description(description) {}

/**
 * @brief Default constructor for the Card class.
 *
 * Initializes the card with empty name and description.
 */
Card::Card() : name(""), description("") {}

/**
 * @brief Gets the name of the card.
 *
 * @return The name of the card.
 */
std::string Card::getName() const {
    return name;
}

/**
 * @brief Gets the description of the card.
 *
 * @return The description of the card.
 */
std::string Card::getDescription() const {
    return description;
}

/**
 * @brief Sets the name of the card.
 *
 * @param name The new name for the card.
 */
void Card::setName(const std::string& name) {
    this->name = name;
}

/**
 * @brief Sets the description of the card.
 *
 * @param description The new description for the card.
 */
void Card::setDescription(const std::string& description) {
    this->description = description;
}