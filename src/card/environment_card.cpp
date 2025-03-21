#include "../../include/card/environment_card.h"

EnvironmentCard::EnvironmentCard(const std::string& name, const std::string& description, Material material)
    : Card(name, description), material(material) {}

EnvironmentCard::EnvironmentCard() : Card(), material(Material::unknown) {}

Material EnvironmentCard::getMaterial() const { 
    return material;
}

void EnvironmentCard::setMaterial(const Material& material) {
    this->material = material;
}


