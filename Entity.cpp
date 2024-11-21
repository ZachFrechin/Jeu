#include "Entity.h"
#include <iostream>
#include <ctime>
#include <cmath>
#include "Player.h"

Entity::Entity() : Entity("assets/default.png", 0, 0, 0, 0, 0.f, 0.f){}
Entity::Entity(const std::string& texturePath, double health, double attack, double defense, int speed, float sizeX, float sizeY):
texturePath(texturePath), health(health), attack(attack), defense(defense), speed(speed) {
    if (!texture.loadFromFile(texturePath)) {
        std::cout << "Failed to load texture: " << texturePath << std::endl;
    }
        sprite.setTexture(texture);
        sprite.setColor(sf::Color(255, 255, 255, 255));
        lastBulletShot = 0.f;
        timerShot = 1000.f;
        setScale(sizeX, sizeY);
        setPosition(sf::Vector2f(static_cast<float>(rand() % 1700), static_cast<float>(rand() % 1000)));
}

// TODO : override function -----------------------------------------


// TODO : default inherit function (overrideable) -------------------
void Entity::move(float x, float y) {
    position.x += x;
    position.y += y;
    sprite.setPosition(position);
}

bool Entity::checkCollision(const Entity& other) const {
    if (sprite.getGlobalBounds().intersects(other.getSprite().getGlobalBounds())) {
        return true;
    }
    return false;
}

bool Entity::checkCollision(const Shot& other) const {
    if (sprite.getGlobalBounds().intersects(other.getSprite().getGlobalBounds())) {
        return true;
    }
    return false;
}

void Entity::applyForce(sf::Vector2f force, const float power) {
    if (const float length = std::sqrt(force.x * force.x + force.y * force.y); length != 0) {
        force /= length;
        force *= power;
    }
    velocity += force;
}

void Entity::draw(sf::RenderWindow& window) {
    window.draw(sprite);
    for(const auto& shot : shots) {
        window.draw(shot->getSprite());
    }
}

bool Entity::takeDamage(const double amount) {
    this->health -= amount;
    return health < 0;
}

// TODO : getter ----------------------------------------------------
sf::Sprite Entity::getSprite() const {
    return sprite;
}

sf::Vector2f Entity::getPosition() const {
    return position;
}

std::vector<std::unique_ptr<Shot>>& Entity::getShots()  {
    return shots;
}

double Entity::getHealth() const {
    return health;
}

double Entity::getAttack() const {
    return attack;
}

double Entity::getDefense() const {
    return defense;
}


// TODO : setter ----------------------------------------------------
void Entity::setScale(float x, float y) {
    const sf::Vector2u textureSize = texture.getSize();
    sprite.setScale(x / textureSize.x, y / textureSize.y);
}

void Entity::setPosition(sf::Vector2f newPos) {
    position = newPos;
    sprite.setPosition(position);
}

























