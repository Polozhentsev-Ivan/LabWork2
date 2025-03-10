#ifndef CHARACTER_CARD_H
#define CHARACTER_CARD_H
#include "card.h"
#include "enums.h"

class CharacterCard : public Card
{
    protected:
        int health;
        int maxHealth;
        int attack;
        int defense;
        int speed;
    public:
        CharacterCard();
        CharacterCard(const std::string& name, const std::string& description, int health, int maxHealth, int attack, int defense, int speed);
        int getHealth() const;
        int getMaxHealth() const;
        int getAttack() const;
        int getDefense() const;
        int getSpeed() const;
        void setHealth(int health);
        void setMaxHealth(int maxHealth);
        void setAttack(int attack);
        void setDefense(int defense);
        void setSpeed(int speed);
};
#endif // CHARACTER_CARD_H
