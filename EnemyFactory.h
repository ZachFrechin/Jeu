#ifndef ENEMY_FACTORY_H
#define ENEMY_FACTORY_H

#include <memory>
#include <stdexcept>
#include "Enemy.h"
#include "Goblin.h"
#include "Giant.h"
#include "orc.h"

class EnemyFactory {
public:
    // Méthode statique pour créer un ennemi en fonction de son type
    static std::unique_ptr<Enemy> createEnemy(const std::string& type, int difficulty) {
        if (type == "goblin") {
            return std::make_unique<Goblin>(difficulty);
        } else if (type == "giant") {
            return std::make_unique<Giant>(difficulty);
        } else if (type == "orc") {
            return std::make_unique<Orc>(difficulty);
        }else {
            throw std::runtime_error("Type d'ennemi inconnu : " + type);
        }
    }
};

#endif // ENEMY_FACTORY_H
