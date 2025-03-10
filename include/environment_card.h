#ifndef ENVIRONMENT_CARD_H
#define ENVIRONMENT_CARD_H
#include "card.h"
#include "enums.h"

class EnvironmentCard : public Card
{
    private:
        Material material;
    public:
        EnvironmentCard();
        EnvironmentCard(const std::string& name, const std::string& description, Material material);
        Material getMaterial() const;
        void setMaterial(const Material& material);
};

#endif // ENVIRONMENT_CARD_H