#include "../../include/card/card.h"

Card::Card(const std::string& name, const std::string& description)
    : name(name), description(description) {}

Card::Card() : name(""), description("") {}

std::string Card::getName() const {
    return name;
}

std::string Card::getDescription() const {
    return description;
}

void Card::setName(const std::string& name) {
    this->name = name;
}

void Card::setDescription(const std::string& description) {
    this->description = description;
} 