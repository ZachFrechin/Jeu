#include "GameManager.h"
#include <cstdlib>
#include <iostream>
#include <stdexcept>

// Constructeur
GameManager::GameManager(sf::RenderWindow& window, std::string texturePath) : window(window) {
    if (!arena.loadFromFile(texturePath)) {
        throw std::runtime_error("Impossible de charger l'image du background !");
    }
    sprite.setTexture(arena);

    // Initialisation du joueur.
    player = Player("assets/entity.png", 100, 10, 2, 500, 50.f, 50.f);

    // Ajout de plusieurs vagues.
    waves.emplace_back(5, "assets/entity.png", 50, 5, 1, 200, 35.f, 35.f); // 1ère vague : 5 ennemis.
    waves.emplace_back(10, "assets/entity.png", 70, 7, 2, 150, 40.f, 40.f); // 2ème vague : 10 ennemis.
    waves.emplace_back(15, "assets/entity.png", 100, 10, 3, 100, 50.f, 50.f); // 3ème vague : 15 ennemis.
}

// Mise à jour de la vague actuelle et des entités.
void GameManager::update(float deltaTime) {
    player.update(deltaTime, player);
    if (currentWaveIndex < waves.size()) {
        Wave& currentWave = waves[currentWaveIndex];
        currentWave.update(deltaTime, player);
    }
}

// Dessiner l'arène, le joueur et la vague actuelle.
void GameManager::draw() {
    window.draw(sprite);
    window.draw(player.getSprite());

    if (currentWaveIndex < waves.size()) {
        waves[currentWaveIndex].draw(window);
    }
}
