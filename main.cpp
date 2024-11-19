#include <SFML/Graphics.hpp>
#include "GameManager.h"
#include "Viewer.h"

int main() {
    sf::VideoMode fullscreenMode = sf::VideoMode::getDesktopMode();
    sf::RenderWindow window(fullscreenMode, "Fullscreen Window", sf::Style::Fullscreen);
    GameManager gameManager(window, "assets/arena.png");
    Viewer viewer(window, gameManager);

    sf::Clock clock;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        float deltaTime = clock.restart().asSeconds();
        gameManager.update(deltaTime);
        viewer.render();
    }

    return 0;
}
