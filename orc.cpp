//
// Created by zachf on 25/11/2024.
//

#include "orc.h"

#include <cmath>

#include "Player.h"

Orc::Orc(int difficulty)
    : Enemy("assets/orc.png",
        50 * difficulty,
        10 * difficulty,
        5 * difficulty,
        75 * (difficulty / 2),
        130.f,
        130.f,
        35) {}

void Orc::update(float deltaTime, const Player& player, sf::RenderWindow& window) {
    sf::Vector2f direction = player.getPosition() - position;


    float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    const float rushDistance = 350.0f;

    if (!isRushing) {
        if (cooldownTimer <= 0.f && distance < rushDistance) {
            acceleration = 500;
            speed = 1000;
            isRushing = true;
            cooldownTimer = cooldown;
        } else {
            cooldownTimer -= deltaTime;
        }
    } else {
        if (rushTimer <= 0.f) {
            isRushing = false;
            speed = 75;
            rushTimer = rushDuration;
        } else {
            rushTimer -= deltaTime;
        }
    }

    if (!isRushing && acceleration > 0) {
        acceleration -= 150 * deltaTime;
        if (acceleration < 0) {
            acceleration = 0;
        }
    }

    if (const float length = std::sqrt(direction.x * direction.x + direction.y * direction.y); length != 0) {
        direction /= length;
        velocity += direction * (static_cast<float>(speed) + acceleration) * deltaTime;
    }

    if (float maxSpeed = speed; std::sqrt(velocity.x * velocity.x + velocity.y * velocity.y) > maxSpeed) {
        velocity /= std::sqrt(velocity.x * velocity.x + velocity.y * velocity.y);
        velocity *= maxSpeed;
    }

    move(velocity.x * deltaTime, velocity.y * deltaTime);
}


