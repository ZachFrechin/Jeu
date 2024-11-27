#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/Graphics.hpp>
#include <string>
#include <utility>

#include "Entity.h"
#include "Item.h"

class Enemy : public Entity {
public:
    Enemy();
    Enemy(std::string texturePath, double health, double attack, double defense, int speed, float sizeX, float sizeY, int score);

    virtual void update(float deltaTime, const Player& player, sf::RenderWindow& window);
    void shot(float deltaTime) override;

    void addLoot(std::unique_ptr<Item> item);

    std::vector<std::unique_ptr<Item>> drop();

private:
    std::vector<std::unique_ptr<Item>> loot;
};

#endif
