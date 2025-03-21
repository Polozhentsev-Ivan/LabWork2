#ifndef ITEM_CARD_H
#define ITEM_CARD_H
#include "card.h"
#include "../enums.h"

class Item: public Card
{
    protected:
        int value;
        Material material;
        int maxStackSize;
        int oneItemWeight;
        int weight;
    public:
        Item(const std::string& name, const std::string& description, int value, Material material, int maxStackSize, int oneItemWeight, int weight);
        Item();
        int getValue() const;
        Material getMaterial() const;
        int getMaxStackSize() const;
        int getOneItemWeight() const;
        int getWeight() const;
        void setValue(int value);
        void setMaterial(Material material);
        void setMaxStackSize(int maxStackSize);
        void setOneItemWeight(int oneItemWeight);
        void setWeight(int weight);

};

#endif // ITEM_CARD_H   