//
// Created by zachf on 20/11/2024.
//

#include "Collision.h"

#include <cmath>
#include <iostream>

#include "Player.h"

#include "GameManager.h"

Collision::Collision(GameManager& gameManager) : gameManager(gameManager) {}

void Collision::attach(Player& player) {
    this->player = &player;
}

void Collision::detachPlayer() {
    this->player = nullptr;
}

void Collision::attach(Wave& wave) {
    this->wave = &wave;
}

void Collision::detachWave() {
    this->wave = nullptr;
}

void Collision::handlePlayerCollision(Enemy *enemy) const {
    if (enemy->checkCollision(*this->player)) {
        this->player->takeDamage(enemy->getAttack());
        enemy->applyForce(enemy->getPosition() - this->player->getPosition(), 20.0f);
    }
}

void Collision::handleOtherEnemyCollision(Enemy *enemy, Enemy *otherEnemy) {
    if (enemy->checkCollision((*otherEnemy))) {
        enemy->applyForce(enemy->getPosition() - otherEnemy->getPosition(), 1.0f);
    }
}

void Collision::handleEnemyShotCollision(Enemy *enemy, const Shot *shot, bool& imDeleted, bool& shotDeleted) {
    if(enemy->checkCollision(*shot)) {
        std::cout << "collision par balle" << std::endl;
        shotDeleted = true;
        if(enemy->takeDamage(shot->getAttack())) {
            std::cout << "damage par balle" << std::endl;
            imDeleted = true;
        }
    }
}

void Collision::handleCollision() const {
    auto& enemies = this->wave->getEnemies();
    for (auto enemy = enemies.begin(); enemy!= enemies.end();) {
        bool imDeleted = false;
        // HANDLE PLAYER COLLISION
        handlePlayerCollision(enemy->get());

        // HANDLE ENEMY COLLISION
        for(auto & otherEnemy : enemies) {
            handleOtherEnemyCollision(enemy->get(), otherEnemy.get());
        }

        // HANDLE SHOT COLLISION
        auto& shots = this->player->getShots();
        for(auto shot = shots.begin(); shot != shots.end(); ) {
            bool shotDeleted = false;
            handleEnemyShotCollision(enemy->get(), shot->get(), imDeleted, shotDeleted);
            if(shotDeleted) {
                shots.erase(shot);
                break;
            }
            ++shot;
        }
         if(imDeleted) {
             gameManager.addInGameItem((*enemy)->drop());
             enemy = this->wave->getEnemies().erase(enemy);
         }else {
             ++enemy;
        }
    }
}


