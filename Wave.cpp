#include "Wave.h"

#include <iostream>

#include "Enemy.h"
#include "Player.h"
#include "math.h"

Wave::Wave(int enemyCount, std::string enemyTexturePath, double health, double attack, double defense, int speed, float sizeX, float sizeY) {
    for (int i = 0; i < enemyCount; ++i) {
        // Initialiser chaque ennemi à une position aléatoire dans l'arène.
        Enemy enemy(enemyTexturePath, health, attack, defense, speed, sizeX, sizeY);
        enemy.setPosition(sf::Vector2f(rand() % 800, rand() % 600)); // Position aléatoire.
        enemies.push_back(enemy);
    }
}

void Wave::update(float deltaTime, Player& player) {
    // Réinitialiser l'état de collision pour tous les ennemis
    for (Enemy& enemy : enemies) {
        enemy.setColliding(false);
    }

    // Gérer les collisions entre le joueur et les ennemis
    for (Enemy& enemy : enemies) {
        if (enemy.checkCollision(player)) {
            enemy.setColliding(true);

            // Appliquer une force de répulsion
            sf::Vector2f repelForce = enemy.getPosition() - player.getPosition();
            float length = std::sqrt(repelForce.x * repelForce.x + repelForce.y * repelForce.y);
            if (length != 0) {
                repelForce /= length; // Normaliser
                repelForce *= 20.f; // Intensité de la force de répulsion
                enemy.applyForce(repelForce);
            }
            std::cout << "Collision detected between player and enemy!" << std::endl;
        }
    }

    // Gérer les collisions entre ennemis
    for (size_t i = 0; i < enemies.size(); ++i) {
        for (size_t j = i + 1; j < enemies.size(); ++j) {
            if (enemies[i].checkCollision(enemies[j])) {
                enemies[i].setColliding(true);
                enemies[j].setColliding(true);

                // Appliquer une force de répulsion entre ennemis
                sf::Vector2f repelForce = enemies[i].getPosition() - enemies[j].getPosition();
                float length = std::sqrt(repelForce.x * repelForce.x + repelForce.y * repelForce.y);
                if (length != 0) {
                    repelForce /= length; // Normaliser
                    repelForce *= 10.f; // Intensité de la force
                    enemies[i].applyForce(repelForce);
                    enemies[j].applyForce(-repelForce); // Force opposée
                }
                std::cout << "Collision detected between enemies!" << std::endl;
            }
        }
    }

    // Mettre à jour la position de chaque ennemi
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


