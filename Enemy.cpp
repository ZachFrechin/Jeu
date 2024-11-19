#include "Enemy.h"
#include "Player.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>

Enemy::Enemy(): Entity() {
}

void Enemy::update(float deltaTime, Player player) {
    if (isColliding) {
        velocity *= 0.7f; // Réduction progressive de la vitesse (friction)
    } else {
        // Calcul normal du mouvement vers le joueur
        sf::Vector2f direction = player.getPosition() - position;
        float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);

        if (length != 0) {
            direction /= length; // Normalisation
            velocity += direction * static_cast<float>(speed) * deltaTime;
        }
    }

    // Limiter la vitesse maximale
    const float maxSpeed = 200.f;
    if (std::sqrt(velocity.x * velocity.x + velocity.y * velocity.y) > maxSpeed) {
        velocity /= std::sqrt(velocity.x * velocity.x + velocity.y * velocity.y);
        velocity *= maxSpeed;
    }

    // Mise à jour de la position
    move(velocity.x * deltaTime, velocity.y * deltaTime);
}

