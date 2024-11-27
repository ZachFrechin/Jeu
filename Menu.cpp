#include "Menu.h"

Menu::Menu(sf::RenderWindow& window) : window(window) {
    // Charger une police
    if (!font.loadFromFile("assets/arial.ttf")) {
        throw std::runtime_error("Impossible de charger la police");
    }

    // Configurer le titre
    titleText.setFont(font);
    titleText.setString("Menu Principal");
    titleText.setCharacterSize(50);
    titleText.setFillColor(sf::Color::White);
    titleText.setStyle(sf::Text::Bold);
    titleText.setPosition(window.getSize().x / 2.f - titleText.getGlobalBounds().width / 2.f, 50.f);

    // Configurer le bouton "Jouer"
    playButton.setSize({200.f, 50.f});
    playButton.setFillColor(sf::Color::Blue);
    playButton.setPosition(window.getSize().x / 2.f - playButton.getSize().x / 2.f, 200.f);

    // Configurer le texte du bouton
    playButtonText.setFont(font);
    playButtonText.setString("Jouer");
    playButtonText.setCharacterSize(30);
    playButtonText.setFillColor(sf::Color::White);
    playButtonText.setPosition(
        playButton.getPosition().x + playButton.getSize().x / 2.f - playButtonText.getGlobalBounds().width / 2.f,
        playButton.getPosition().y + playButton.getSize().y / 2.f - playButtonText.getGlobalBounds().height / 2.f
    );
}

void Menu::handleEvent(const sf::Event& event) {
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);

        // Vérifier si le bouton "Jouer" est cliqué
        if (playButton.getGlobalBounds().contains(mousePos)) {
            if (playCallback) {
                playCallback(); // Exécuter l'action associée au bouton
            }
        }
    }
}

void Menu::render() {
    // Dessiner les éléments du menu
    window.draw(titleText);
    window.draw(playButton);
    window.draw(playButtonText);
}

void Menu::setPlayButtonCallback(const std::function<void()>& callback) {
    playCallback = callback;
}
