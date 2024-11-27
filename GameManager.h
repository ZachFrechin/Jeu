#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <SFML/Graphics.hpp>
#include <vector>

#include "Collision.h"
#include "Entity.h"
#include "Player.h"
#include "Wave.h"
#include "WaveFactory.h"

class GameManager {
public:
    GameManager(sf::RenderWindow& window, const std::string &texturePath);

    void update(float deltaTime, float time);
    void draw() const;

    int getCurrentWaveIndex() const;
    const Player& getPlayer() const;
    std::vector<std::unique_ptr<Item>>& getInGameItems();

    void addInGameItem(std::vector<std::unique_ptr<Item>> items);

private:
    sf::RenderWindow& window;
    sf::Texture arena;
    sf::Sprite sprite;

    std::unique_ptr<Player> player;
    std::unique_ptr<Collision> collisionManager;
    std::vector<std::unique_ptr<Wave>> waves;
    std::unique_ptr<WaveFactory> waveFactory;
    std::vector<std::unique_ptr<Item>> inGameItems;

    int currentWaveIndex = 0;
    int difficulty = 2;
};

#endif
