//
// Created by zachf on 19/11/2024.
//

#include "Shot.h"
#include <iostream>
#include <utility>

#include "Entity.h"

Shot::Shot(const int speed, const sf::Vector2f direction, const sf::Vector2f position, const std::string &texturePath, const int attack, const float sizeX, const float sizeY)
    : texturePath(texturePath), direction(direction), position(position), speed(speed), attack(attack) {
    if (!texture.loadFromFile(texturePath)) {
        std::cout << "Failed to load texture: " << texturePath << std::endl;
    } else {
        sprite.setTexture(texture);
        sprite.setPosition(position);
        sprite.setScale(sf::Vector2f(sizeX, sizeY));
    }
}

void Shot::update(float deltaTime, const sf::RenderWindow& window) {
    position += direction * deltaTime * static_cast<float>(speed);
    sprite.setPosition(position);

    if (position.x < 0 || position.x > window.getSize().x ||
        position.y < 0 || position.y > window.getSize().y) {
        isOutOfBounds = true;
        }
}

bool Shot::isMarkedForDeletion() const {
    return isOutOfBounds;
}

// TODO : getter ------------------------------------
sf::Sprite Shot::getSprite() const {
    return sprite;
}

int Shot::getAttack() const {
    return attack;
}
