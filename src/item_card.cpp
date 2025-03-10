#include "../include/item_card.h"


Item::Item(const std::string& name, const std::string& description, int value, Material material, int maxStackSize, int oneItemWeight, int weight)
    : Card(name, description), value(value), material(material), maxStackSize(maxStackSize), 
      oneItemWeight(oneItemWeight), weight(weight) {}
Item::Item() : Card(), value(0), material(Material::unknown), maxStackSize(0), oneItemWeight(0), weight(0) {}

int Item::getValue() const {
    return value;
}

Material Item::getMaterial() const {
    return material;
}

int Item::getMaxStackSize() const {
    return maxStackSize;
}

int Item::getOneItemWeight() const {
    return oneItemWeight;
}

int Item::getWeight() const {
    return weight;
}


void Item::setValue(int value) {
    this->value = value;
}

void Item::setMaterial(Material material) {
    this->material = material;
}

void Item::setMaxStackSize(int maxStackSize) {
    this->maxStackSize = maxStackSize;
}

void Item::setOneItemWeight(int oneItemWeight) {
    this->oneItemWeight = oneItemWeight;
}

void Item::setWeight(int weight) {
    this->weight = weight;
}
