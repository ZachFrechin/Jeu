#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>
#include <functional>

class Menu {
public:
    explicit Menu(sf::RenderWindow& window);

    // Méthodes principales
    void handleEvent(const sf::Event& event);
    void render();

    // Définir une action à exécuter lorsque le bouton est cliqué
    void setPlayButtonCallback(const std::function<void()>& callback);

private:
    sf::RenderWindow& window;          // Référence à la fenêtre SFML
    sf::Font font;                     // Police pour le texte
    sf::Text titleText;                // Titre du menu
    sf::RectangleShape playButton;     // Bouton "Jouer"
    sf::Text playButtonText;           // Texte sur le bouton

    std::function<void()> playCallback; // Action pour le bouton "Jouer"
};

#endif // MENU_H
