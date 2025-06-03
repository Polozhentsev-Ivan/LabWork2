#ifndef CARD_H
#define CARD_H
#include <string>
#include <stdexcept>
/**
 * @brief Represents a generic card in the game.
 * 
 * This is a base class for all types of cards in the game, providing common attributes
 * like name and description.
 */
class Card
{
    protected:
        std::string name;           /**< The name of the card. */
        std::string description;    /**< A description of the card. */
    public:
        /**
         * @brief Default constructor for Card.
         */
        Card();
        /**
         * @brief Constructs a Card with a specified name and description.
         *
         * @param name The name of the card.
         * @param description A description of the card.
         */
        Card(const std::string& name, const std::string& description);
        /**
         * @brief Gets the name of the card.
         * @return The name of the card.
         */
        std::string getName() const;
        /**
         * @brief Gets the description of the card.
         * @return The description of the card.
         */
        std::string getDescription() const;
        /**
         * @brief Sets the name of the card.
         * @param name The new name for the card.
         */
        void setName(const std::string& name);
        /**
         * @brief Sets the description of the card.
         * @param description The new description for the card.
         */
        void setDescription(const std::string& description);
};
#endif // CARD_H