#ifndef VIEWER_H
#define VIEWER_H

#include <SFML/Graphics.hpp>
#include "GameManager.h"

class Viewer {
public:
    Viewer(sf::RenderWindow& window, GameManager& gameManager);

    void render();

private:
    sf::RenderWindow& window;
    GameManager& gameManager;
};

#endif // VIEWER_H
