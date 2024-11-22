#include "Enemy.h"
#include "Player.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>

Enemy::Enemy(): Entity() {}
Enemy::Enemy(std::string texturePath, double health, double attack, double defense, int speed, float sizeX, float sizeY)
    : Entity(texturePath, health, attack, defense, speed, sizeX, sizeY) {
}

void Enemy::update(const float deltaTime, const Player& player) {
    sf::Vector2f direction = player.getPosition() - position;

    if (const float length = std::sqrt(direction.x * direction.x + direction.y * direction.y); length != 0) {
            direction /= length; // Normalisation
            velocity += direction * static_cast<float>(speed * 1.5) * deltaTime;
        }

    if ( float maxSpeed = speed; std::sqrt(velocity.x * velocity.x + velocity.y * velocity.y) > maxSpeed) {
        velocity /= std::sqrt(velocity.x * velocity.x + velocity.y * velocity.y);
        velocity *= maxSpeed;
    }
    move(velocity.x * deltaTime, velocity.y * deltaTime);
}

void Enemy::shot(float deltaTime) {
    std::cout << "shot" << std::endl;
}

void Enemy::addLoot(std::unique_ptr<Item> item) {
    loot.push_back(std::move(item));
}

std::vector<std::unique_ptr<Item>> Enemy::drop() {
    std::vector<std::unique_ptr<Item>> droppedItems;
    for(auto it = loot.begin(); it != loot.end(); ++it) {
        if(const float r = rand() % 101; r <= (*it)->getDropRate() * 100) {
            (*it)->setDropped(true);
            (*it)->setPosition(position);
            droppedItems.push_back(std::move(*it));
        }
    }
    return droppedItems;
}


