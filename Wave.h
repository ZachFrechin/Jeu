#ifndef WAVE_HPP
#define WAVE_HPP

#include <memory>
#include <vector>
#include "Enemy.h"

class Wave {
public:
    Wave(int enemyCount, std::vector<std::unique_ptr<Enemy>> enemies, int difficulty);
    void update(float deltaTime, const Player& player, sf::RenderWindow& window);
    void draw(sf::RenderWindow& window) const;
    std::vector<std::unique_ptr<Enemy>>& getEnemies();
    [[nodiscard]] bool isCleared() const;

private:
    std::vector<std::unique_ptr<Enemy>> enemies;
    std::vector<std::unique_ptr<Enemy>> spawnedEnemiesList;
    int enemiesToSpawn{};
    int enemyCount;
    int spawnedEnemies = 0;
    float spawnTimer = 0.0f;
    const float spawnInterval = 1.0f;
    int difficulty = 0;
};


#endif // WAVE_HPP
