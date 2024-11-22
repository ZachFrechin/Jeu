//
// Created by zachf on 20/11/2024.
//

#ifndef COLLISION_H
#define COLLISION_H
#include <memory>
#include <vector>

#include "Wave.h"
class GameManager;

class Collision {
public:
    explicit Collision(GameManager& gameManager);
    ~Collision() = default;
    void attach(Player& player);
    void attach(Wave& wave);
    void detachPlayer();
    void detachWave();
    void handleCollision(float time) const;




private:
    void handlePlayerCollision(Enemy *enemy) const;
    static void handleOtherEnemyCollision(Enemy* enemy, const Enemy* otherEnemy);
    static void handleEnemyShotCollision(Enemy *enemy, const Shot *shot, bool &imDeleted, bool &shotDeleted);
    void handleItemPlayerCollision(Item* item, float time, bool& itemDeleted) const;

    Wave* wave = nullptr;
    Player *player = nullptr;
    GameManager& gameManager;
};



#endif //COLLISION_H
