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

void Collision::handleOtherEnemyCollision(Enemy *enemy, const Enemy *otherEnemy) {
    if (enemy->checkCollision((*otherEnemy))) {
        enemy->applyForce(enemy->getPosition() - otherEnemy->getPosition(), 0.5f);
    }
}

void Collision::handleEnemyShotCollision(Enemy *enemy, const Shot *shot, bool& imDeleted, bool& shotDeleted) {
    if(enemy->checkCollision(*shot)) {
        shotDeleted = true;
        if(enemy->takeDamage(shot->getAttack())) {
            imDeleted = true;
        }
    }
}

void Collision::handleCollision(float time) const {
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

    auto& items = gameManager.getInGameItems();
    for (auto item = items.begin(); item != items.end();) {
        bool itemDeleted = false;
        handleItemPlayerCollision(item->get(), time, itemDeleted);
        if(itemDeleted) {
            gameManager.getInGameItems().erase(item);
        }else {
            ++item;
        }
    }
}



void Collision::handleItemPlayerCollision(Item* item, float time, bool& itemDeleted) const {
    if(item->checkCollision(*this->player)) {
        item->loot(*player, time);
        itemDeleted = true;
    }
}



