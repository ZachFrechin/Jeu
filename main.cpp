#include <SFML/Graphics.hpp>
#include "GameManager.h"
#include "Viewer.h"
#include "Menu.h"

int main() {
    // Créer la fenêtre en mode plein écran
    sf::VideoMode fullscreenMode = sf::VideoMode::getDesktopMode();
    sf::RenderWindow window(fullscreenMode, "Fullscreen Window", sf::Style::Fullscreen);

    // Créer une instance du menu
    Menu menu(window);
    bool isGameRunning = false; // Indique si le jeu est en cours

    // Définir l'action du bouton "Jouer"
    menu.setPlayButtonCallback([&]() {
        isGameRunning = true; // Passer en mode jeu
    });

    // Initialiser les composants pour le jeu
    std::unique_ptr<GameManager> gameManager;
    std::unique_ptr<Viewer> viewer;

    sf::Clock deltaClock;
    sf::Clock clock;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            // Si le jeu n'est pas en cours, gérer les événements du menu
            if (!isGameRunning) {
                menu.handleEvent(event);
            }
        }

        // Si le jeu est en cours
        if (isGameRunning) {
            // Initialiser GameManager et Viewer lors de la première boucle
            if (!gameManager || !viewer) {
                gameManager = std::make_unique<GameManager>(window, "assets/arena.png");
                viewer = std::make_unique<Viewer>(window, *gameManager);
            }

            float deltaTime = deltaClock.restart().asSeconds();
            gameManager->update(deltaTime, clock.getElapsedTime().asMilliseconds());
            viewer->render();
        } else {
            // Sinon, afficher le menu
            window.clear();
            menu.render();
            window.display();
        }
    }

    return 0;
}
