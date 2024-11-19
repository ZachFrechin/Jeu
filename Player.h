#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Entity.h"

class Player : public Entity {
    public:
    Player();
    Player(std::string texturePath, double health, double attack, double defense, int speed, float sizeX, float sizeY) : Entity(texturePath, health, attack, defense, speed, sizeX, sizeY) {};
    void update(float deltaTime, Player player) override;

};
#endif
