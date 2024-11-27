#include "Goblin.h"

#include <cmath>
#include <iostream>

#include "Player.h"

Goblin::Goblin(int difficulty)
    : Enemy("assets/goblin.png",
        50 * difficulty,
        10 * difficulty,
        5 * difficulty,
        300 * (difficulty / 2),
        100.f,
        100.f,
        10) {
    timerShot = 3.f / difficulty;
}

void Goblin::update(const float deltaTime, const Player& player, sf::RenderWindow& window) {
    sf::Vector2f direction = player.getPosition() - position;
    const float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);

    if (constexpr float stopDistance = 250.0f; distance > stopDistance) {
        if (distance != 0) {
            direction /= distance;
            velocity += direction * static_cast<float>(speed * 1.5) * deltaTime;
        }
        if (const float maxSpeed = speed; std::sqrt(velocity.x * velocity.x + velocity.y * velocity.y) > maxSpeed) {
            velocity /= std::sqrt(velocity.x * velocity.x + velocity.y * velocity.y);
            velocity *= maxSpeed;
        }
        move(velocity.x * deltaTime, velocity.y * deltaTime);


    } else {
        velocity = sf::Vector2f(0.f, 0.f);
    }
    float angle = std::atan2(direction.y, direction.x) * 180.f / static_cast<float>(M_PI);
    sprite.setRotation(angle);
    shot(deltaTime, player);
    for (const auto& shot : shots) {
        shot->update(deltaTime, window);
    }
}

void Goblin::shot(const float deltaTime, const Player& player) {
    if (timerShot <= 0.f ) {
        const sf::Vector2f playerPosition = player.getPosition();
        sf::Vector2f direction = playerPosition - position;

        if (const float length = std::sqrt(direction.x * direction.x + direction.y * direction.y); length != 0) {
            direction /= length;
        }
        shots.push_back(std::make_unique<Shot>(500, direction, position, "assets/bullet.png", 2 * attack, 0.05f, 0.05f));
        timerShot = 3.f;
    }else {
        timerShot -= deltaTime;
    }
}