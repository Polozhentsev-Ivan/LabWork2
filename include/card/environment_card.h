#ifndef ENVIRONMENT_CARD_H
#define ENVIRONMENT_CARD_H
#include "card.h"
#include "../enums.h"

/**
 * @brief Represents an environment card in the game.
 * 
 * This class inherits from Card and adds attributes specific to environment elements,
 * such as the material it's made of.
 */
class EnvironmentCard : public Card
{
    private:
        Material material;  /**< The material of the environment element. */
    public:
        /**
         * @brief Default constructor for EnvironmentCard.
         */
        EnvironmentCard();
        /**
         * @brief Constructs an EnvironmentCard with specified attributes.
         *
         * @param name The name of the card.
         * @param description A description of the card.
         * @param material The material of the environment element.
         */
        EnvironmentCard(const std::string& name, const std::string& description, Material material);
        /**
         * @brief Gets the material of the environment element.
         * @return The material.
         */
        Material getMaterial() const;
        /**
         * @brief Sets the material of the environment element.
         * @param material The new material value.
         */
        void setMaterial(const Material& material);
};

#endif // ENVIRONMENT_CARD_H