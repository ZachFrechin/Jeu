#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "Entity.h"
#include "Player.h"
#include "Wave.h"

class GameManager {
public:
    GameManager(sf::RenderWindow& window, std::string texturePath);

    void update(float deltaTime);
    void draw();

private:
    sf::RenderWindow& window;
    sf::Texture arena;
    sf::Sprite sprite; // Représente l'arène.

    Player player;
    std::vector<Wave> waves;
    int currentWaveIndex = 0; // Index de la vague actuelle.
};

#endif // GAMEMANAGER_H
