#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Entity.h"
#include "Shot.h"

class Player final : public Entity {
public:
    Player();
    Player(std::string texturePath, double health, double attack, double defense, int speed, float sizeX, float sizeY);

    void update(float deltaTime, float time, sf::RenderWindow &window);

    void shot(float time) override;
    bool takeDamage(double amount) override;

    bool isInvincible() const;

    int getLevel() const;
    void checkLevelUp(sf::RenderWindow &window);

private:
    float invincibilityTimer = 0.f;
    const float maxInvincibilityTime = 1.f;

    int level = 1;             // Niveau actuel du joueur
    const int baseLevelScore = 200; // Score requis pour passer du niveau 1 au niveau 2
};

#endif
