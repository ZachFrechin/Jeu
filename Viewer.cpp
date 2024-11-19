#include "Viewer.h"

// Constructor
Viewer::Viewer(sf::RenderWindow& window, GameManager& gameManager)
    : window(window), gameManager(gameManager) {}

// Render the game
void Viewer::render() {
    window.clear();
    gameManager.draw();
    window.display();
}
