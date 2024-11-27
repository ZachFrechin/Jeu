#include "Player.h"
#include <iostream>
#include <cmath>

#include "MenuLevel.h"
#include "Shot.h"

Player::Player() : Entity() {}
Player::Player(std::string texturePath, double health, double attack, double defense, int speed, float sizeX, float sizeY)
    : Entity(texturePath, health, attack, defense, speed, sizeX, sizeY, 0) {


}
void Player::update(const float deltaTime, const float time, sf::RenderWindow &window) {
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

    bound(window.getSize().x - 75, window.getSize().y - 75);

    for (const auto& shot : shots) {
        shot->update(deltaTime, window);
    }

    if (invincibilityTimer > 0.f) {
        invincibilityTimer -= deltaTime;
    }

    debuffAttack(deltaTime);
    debuffSpeed(deltaTime);
    debuffAttackSpeed(deltaTime);

    // Vérifier si le joueur doit monter de niveau
    checkLevelUp(window);
}

void Player::shot(const float time) {
    if (time - lastBulletShot > timerShot) {
        lastBulletShot = time;
        const sf::Vector2i m = sf::Mouse::getPosition(); // Position de la souris en pixels
        const sf::Vector2f mousePosition(static_cast<float>(m.x), static_cast<float>(m.y)); // Conversion en float
        sf::Vector2f direction = mousePosition - position;

        // Calculer la direction normalisée
        if (const float length = std::sqrt(direction.x * direction.x + direction.y * direction.y); length != 0) {
            direction /= length;
        }

        // Calculer l'angle de rotation en degrés
        float angle = std::atan2(direction.y, direction.x) * 180.f / static_cast<float>(M_PI);

        // Appliquer la rotation au sprite du joueur
        sprite.setRotation(angle);

        // Créer un nouveau tir dans la direction
        shots.push_back(std::make_unique<Shot>(1000, direction, position, "assets/bullet.png", 2 * attack, 0.05f, 0.05f));
    }
}

void Player::checkLevelUp(sf::RenderWindow& window) {
    if (const int requiredScore = baseLevelScore * level; score >= requiredScore) {
        ++level;
        std::cout << "Level Up! New Level: " << level << std::endl;

        // Afficher le menu de niveau
        MenuLevel menu(window);
        bool choiceMade = false;

        menu.setHealthCallback([&]() {
            maxHealth += 50; // Augmenter les PV
            health  = maxHealth;
            choiceMade = true;
        });

        menu.setAttackCallback([&]() {
            attack += 10; // Augmenter l'attaque
            choiceMade = true;
        });

        menu.setAttackSpeedCallback([&]() {
            timerShot -= 50.0; // Augmenter la vitesse d'attaque
            choiceMade = true;
        });

        while (!choiceMade) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                    return;
                }
                menu.handleEvent(event);
            }

            window.clear();
            menu.render();
            window.display();
        }
    }
}


int Player::getLevel() const {
    return level;
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
