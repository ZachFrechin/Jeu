#include "Player.h"
#include <math.h>

Player::Player(): Entity() {
}

void Player::update(float deltaTime, Player player) {
    sf::Vector2f direction(0.f, 0.f);
    // Example movement logic: move toward the player
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        direction.y -= 1.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        direction.y += 1.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        direction.x -= 1.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        direction.x += 1.f;

    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    if (length != 0) {
        direction /= length; // Normalize direction
        position += direction *  static_cast<float>(speed) * deltaTime;
        sprite.setPosition(position);
    }
}
