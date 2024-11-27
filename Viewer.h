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

    sf::Font font; // Police pour le texte.
    sf::Text waveText; // Texte pour afficher la vague.
    sf::Text playerHealthText; // Texte pour afficher la santé du joueur.
    sf::Text score;

    sf::RectangleShape waveBackground; // Fond pour le texte de la vague
    sf::RectangleShape playerHealthBackground; // Fond pour le texte de la santé
    sf::RectangleShape scoreBackground;

    sf::RectangleShape xpBarBackground;
    sf::RectangleShape xpBarFill;

    void updateXPBar();

    void updateUI(); // Mettre à jour les textes affichés.
};

#endif // VIEWER_H
