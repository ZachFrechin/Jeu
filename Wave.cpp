#include "Wave.h"

#include <iostream>

#include "Enemy.h"
#include "Player.h"

Wave::Wave(int enemyCount, std::string enemyTexturePath, double health, double attack, double defense, int speed, float sizeX, float sizeY) {
    for (int i = 0; i < enemyCount; ++i) {
        // Initialiser chaque ennemi à une position aléatoire dans l'arène.
        Enemy enemy(enemyTexturePath, health, attack, defense, speed, sizeX, sizeY);
        enemy.setPosition(sf::Vector2f(rand() % 800, rand() % 600)); // Position aléatoire.
        enemies.push_back(enemy);
    }
}

void Wave::update(float deltaTime, Player& player) {
    for (Enemy& enemy : enemies) {
        enemy.update(deltaTime, player);

    }

}

void Wave::draw(sf::RenderWindow& window) {
    for (const Enemy& enemy : enemies) {
        window.draw(enemy.getSprite());
    }
}

const std::vector<Enemy>& Wave::getEnemies() const {
    return enemies;
}

std::vector<Enemy>& Wave::getEnemies() {
    return enemies;
}


