#include "Player.h"
#include <iostream>
#include <cmath>
#include "Shot.h"

Player::Player() : Entity() {}
Player::Player(std::string texturePath, double health, double attack, double defense, int speed, float sizeX, float sizeY)
    : Entity(texturePath, health, attack, defense, speed, sizeX, sizeY) {}

void Player::update(const float deltaTime, const float time, const sf::RenderWindow& window) {
    sf::Vector2f direction(0.f, 0.f);

    // KEYBOARD EVENT
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
        direction.y -= 1.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        direction.y += 1.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
        direction.x -= 1.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        direction.x += 1.f;
    // MOUSE EVENT
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        shot(time);
    }

    if (const float length = std::sqrt(direction.x * direction.x + direction.y * direction.y); length != 0) {
        direction /= length;
        position += direction * static_cast<float>(speed) * deltaTime;
        sprite.setPosition(position);
    }

    for (const auto& shot : shots) {
        shot->update(deltaTime, window);
    }

    if (invincibilityTimer > 0.f) {
        invincibilityTimer -= deltaTime;
    }
}

void Player::shot(const float time) {
    if (time - lastBulletShot > timerShot) {
        lastBulletShot = time;
        const sf::Vector2i m = sf::Mouse::getPosition();
        const sf::Vector2f mousePosition(m);
        sf::Vector2f direction = mousePosition - position;

        if (const float length = std::sqrt(direction.x * direction.x + direction.y * direction.y); length != 0) {
            direction /= length;
        }

        shots.push_back(std::make_unique<Shot>(1000, direction, position, "assets/bullet.png", 2 * attack, 0.05f, 0.05f));
    }
}

bool Player::takeDamage(const double amount) {
    if (invincibilityTimer <= 0.f) {
        health -= amount;
        invincibilityTimer = maxInvincibilityTime;
    }
    return health < 0;
}

bool Player::isInvincible() const {
    return invincibilityTimer > 0.f;
}
