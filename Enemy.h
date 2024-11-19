#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/Graphics.hpp>
#include <string>
#include <utility>

#include "Entity.h"

class Enemy : public Entity {
public:
    Enemy();
    Enemy(std::string texturePath, double health, double attack, double defense, int speed, float sizeX, float sizeY) : Entity(texturePath, health, attack, defense, speed, sizeX, sizeY) {};
    void update(float deltaTime, Player player) override;

};
#endif
