#include "Entity.h"

#include <iostream>
#include <ctime>
#include <math.h>

#include "Player.h"

Entity::Entity() {

}
Entity::Entity(std::string texturePath, double health, double attack, double defense, int speed, float sizeX, float sizeY):
texturePath(texturePath), health(health), attack(attack), defense(defense), speed(speed) {
    if (!texture.loadFromFile(texturePath)) {
        std::cerr << "Failed to load texture: " << texturePath << std::endl;
    }else {
        sprite.setTexture(texture);
        setScale(sizeX, sizeY);
        setPosition(sf::Vector2f(400.f, 300.f));
    }
}

void Entity::update(float deltaTime, Player player) {

}


const sf::Sprite& Entity::getSprite() const {
    return sprite;
}

void Entity::setScale(float x, float y) {
    sf::Vector2u textureSize = texture.getSize();
    sprite.setScale(x / textureSize.x, y / textureSize.y);
}

void Entity::setPosition(sf::Vector2f newPos) {
    position = newPos;
    sprite.setPosition(position);
}
void Entity::move(float x, float y) {
        position.x += x;
        position.y += y;
        sprite.setPosition(position);
}

sf::Vector2f Entity::getPosition() {
    return position;
}

bool Entity::checkCollision(const Entity& other) const {
    if (sprite.getGlobalBounds().intersects(other.getSprite().getGlobalBounds())) {
        std::cout << "Collision detected!" << std::endl;
        return true;
    }
    return false;
}

void Entity::setColliding(bool colliding) {
    isColliding = colliding;
}

void Entity::applyForce(sf::Vector2f force) {
    velocity += force;
}


bool Entity::getColliding() const {
    return isColliding;
}

