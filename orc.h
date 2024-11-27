//
// Created by zachf on 25/11/2024.
//

#ifndef ORC_H
#define ORC_H
#include "Enemy.h"


class Orc : public Enemy{
public:
    Orc(int difficulty);
    void update(float deltaTime, const Player& player, sf::RenderWindow& window) override;
private:
private:
    bool isRushing = false;       // Indique si l'Orc est en train de ruer
    float rushDuration =1.f;   // Durée de la ruée en secondes
    float rushTimer = 1.f;         // Timer pour gérer la durée de la ruée
    float cooldown = 5.0f;       // Cooldown entre deux ruées
    float cooldownTimer = 0;     // Timer pour gérer le cooldown
    float acceleration;


};



#endif //ORC_H
