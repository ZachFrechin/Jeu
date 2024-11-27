#include "Wave.h"

#include <iostream>
#include <utility>
#include "Enemy.h"
#include "Player.h"

Wave::Wave(const int enemyCount, std::vector<std::unique_ptr<Enemy>> enemies, const int difficulty) : difficulty(difficulty) {
    this->enemies = std::move(enemies);
    this->enemyCount = enemyCount;
    this->enemiesToSpawn = enemyCount;
    std::cout << "vague créer : " << enemiesToSpawn << std::endl;
}

void Wave::update(const float deltaTime, const Player& player, sf::RenderWindow& window) {
    spawnTimer += deltaTime;
    if (spawnTimer >= (3.0f / difficulty) && enemiesToSpawn > 0) {
        spawnTimer = 0.f;
        spawnedEnemiesList.push_back(std::move(enemies[enemyCount - enemiesToSpawn]));
        --enemiesToSpawn;
    }
    for (const auto& enemy : spawnedEnemiesList) {
        enemy->update(deltaTime, player, window);
    }
}

void Wave::draw(sf::RenderWindow& window) const {
    for (const auto& enemy : spawnedEnemiesList) {
        enemy->draw(window);
    }
}

std::vector<std::unique_ptr<Enemy>>& Wave::getEnemies() {
    return spawnedEnemiesList;
}

bool Wave::isCleared() const {
    return enemiesToSpawn == 0 && spawnedEnemiesList.empty();
}



