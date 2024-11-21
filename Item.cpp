//
// Created by zachf on 21/11/2024.
//

#include "Item.h"

#include <iostream>

Item::Item(): TTL(0), dropRate(0.f) {}
Item::Item(const std::string& texturePath, float sizeX, float sizeY, float dropRate) : Entity(texturePath,0,0,0,0, sizeX, sizeY),
    TTL(0), dropRate(dropRate) {}

void Item::loot(Player& player) {
    std::cout << "Item::loot" << std::endl;
}

void Item::shot(float deltaTime) {
    // Implémentation vide ou comportement par défaut
}

void Item::update() const {
    if(dropped) {
        std::cout << "Item::update" << std::endl;
    }
}

void Item::draw(sf::RenderWindow& window) {
    if(dropped) {
        std::cout << "Item::draw" << std::endl;
        window.draw(sprite);
    }
}

