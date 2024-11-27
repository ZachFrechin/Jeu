#ifndef MENU_LEVEL_H
#define MENU_LEVEL_H

#include <SFML/Graphics.hpp>
#include <functional>
#include <vector>

class MenuLevel {
public:
    explicit MenuLevel(sf::RenderWindow& window);

    void render();
    void handleEvent(const sf::Event& event);

    // Définir les actions associées aux boutons
    void setHealthCallback(const std::function<void()>& callback);
    void setAttackCallback(const std::function<void()>& callback);
    void setAttackSpeedCallback(const std::function<void()>& callback);

private:
    sf::RenderWindow& window;

    // Fond semi-transparent
    sf::RectangleShape background;

    // Boutons
    sf::RectangleShape healthButton;
    sf::RectangleShape attackButton;
    sf::RectangleShape attackSpeedButton;

    // Textes des boutons
    sf::Font font;
    sf::Text healthText;
    sf::Text attackText;
    sf::Text attackSpeedText;

    // Callbacks des boutons
    std::function<void()> healthCallback;
    std::function<void()> attackCallback;
    std::function<void()> attackSpeedCallback;

    // Initialisation des éléments graphiques
    void initializeElements();
};

#endif // MENU_LEVEL_H
