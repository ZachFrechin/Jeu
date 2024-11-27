#ifndef GOBLIN_H
#define GOBLIN_H

#include "Enemy.h"

class Goblin : public Enemy {
public:
    Goblin(int difficulty);
    void update(float deltaTime, const Player& player, sf::RenderWindow& window) override;

private:
    void shot(float deltaTime, const Player& player);
};

#endif // GOBLIN_H
