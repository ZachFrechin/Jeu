#ifndef WAVE_HPP
#define WAVE_HPP

#include <vector>
#include "Enemy.h"

class Wave {
public:
    Wave(int enemyCount, std::string enemyTexturePath, double health, double attack, double defense, int speed, float sizeX, float sizeY);
    void update(float deltaTime, Player& player);
    void draw(sf::RenderWindow& window);
    const std::vector<Enemy>& getEnemies() const; // Version constante
    std::vector<Enemy>& getEnemies();

    bool isCleared() const; // Vérifie si tous les ennemis sont éliminés.

private:
    std::vector<Enemy> enemies;
};

#endif // WAVE_HPP
