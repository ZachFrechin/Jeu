#include "GameManager.h"
#include <cstdlib>
#include <iostream>
#include <stdexcept>

GameManager::GameManager(sf::RenderWindow& window, const std::string &texturePath) : window(window) {
    if (!arena.loadFromFile(texturePath)) {
        throw std::runtime_error("Impossible de charger l'image du background !");
    }

    this->sprite.setTexture(arena);

    this->collisionManager = std::make_unique<Collision>(*this);
    this->player = std::make_unique<Player>("assets/entity.png", 50, 15, 1.2, 250, 50.f, 50.f);
    this->waveFactory = std::make_unique<WaveFactory>("assets/waves.json");

    this->waves = waveFactory->generateWave(1);
}

void GameManager::update(const float deltaTime, const float time) {
    player->update(deltaTime, time, window);
    for(auto it = inGameItems.begin(); it != inGameItems.end(); ++it) {
        (*it)->update();
    }

    if (currentWaveIndex < waves.size()) {
        Wave& currentWave = *waves[currentWaveIndex];
        collisionManager->attach(*player);
        collisionManager->attach(currentWave);
        collisionManager->handleCollision();

        currentWave.update(deltaTime, *player);

        if (currentWave.isCleared()) {
            ++currentWaveIndex;
            if (currentWaveIndex < waves.size()) {
                std::cout << "Vague suivante : " << currentWaveIndex + 1 << std::endl;
            } else {
                std::cout << "Vous avez terminé toutes les vagues !" << std::endl;
            }
        }
    }
}

void GameManager::draw() const {
    window.draw(sprite);
    player->draw(window);
    for(auto it = inGameItems.begin(); it != inGameItems.end(); ++it) {
        (*it)->draw(window);
    }
    if (currentWaveIndex < waves.size()) {
        waves[currentWaveIndex]->draw(window);
    }
}

void GameManager::addInGameItem(std::vector<std::unique_ptr<Item>> items) {
    for (auto it = items.begin(); it != items.end(); ++it) {
        inGameItems.push_back(std::move(*it));
    }
}


// TODO : getter -------------------------------------
int GameManager::getCurrentWaveIndex() const {
    return currentWaveIndex;
}

const Player& GameManager::getPlayer() const {
    return *player;
}




