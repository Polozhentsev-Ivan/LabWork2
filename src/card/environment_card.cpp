/**
 * @file environment_card.cpp
 * @brief Implements the EnvironmentCard class methods.
 */

#include "../../include/card/environment_card.h"

/**
 * @brief Constructs an EnvironmentCard object with specified attributes.
 *
 * @param name The name of the environment card.
 * @param description The description of the environment card.
 * @param material The material of the environment object.
 */
EnvironmentCard::EnvironmentCard(const std::string& name, const std::string& description, Material material)
    : Card(name, description), material(material) {}

/**
 * @brief Default constructor for the EnvironmentCard class.
 *
 * Initializes with an unknown material.
 */
EnvironmentCard::EnvironmentCard() : Card(), material(Material::unknown) {}

/**
 * @brief Gets the material of the environment object.
 *
 * @return The material.
 */
Material EnvironmentCard::getMaterial() const { 
    return material;
}

/**
 * @brief Sets the material of the environment object.
 *
 * @param material The new material.
 */
void EnvironmentCard::setMaterial(const Material& material) {
    this->material = material;
}


