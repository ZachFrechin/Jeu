#include "Enemy.h"
#include "Player.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>

Enemy::Enemy(): Entity() {
}

void Enemy::update(float deltaTime, Player player) {
    sf::Vector2f direction = player.getPosition() - position;
    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);

    if (length != 0) {
        direction /= length; // Normalisation
        move(direction.x * static_cast<float>(speed) * deltaTime, direction.y * static_cast<float>(speed) * deltaTime);
    }

}

