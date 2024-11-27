#include "MenuLevel.h"
#include <stdexcept>

MenuLevel::MenuLevel(sf::RenderWindow& window) : window(window) {
    // Charger la police
    if (!font.loadFromFile("assets/arial.ttf")) {
        throw std::runtime_error("Impossible de charger la police !");
    }

    // Initialiser les éléments graphiques
    initializeElements();
}

void MenuLevel::initializeElements() {
    // Fond semi-transparent
    background.setSize(sf::Vector2f(window.getSize().x, window.getSize().y));
    background.setFillColor(sf::Color(0, 0, 0, 150));

    // Boutons
    const float buttonWidth = 200.f;
    const float buttonHeight = 50.f;
    const float buttonSpacing = 20.f;
    const float centerX = window.getSize().x / 2.f;
    const float centerY = window.getSize().y / 2.f;

    healthButton.setSize({buttonWidth, buttonHeight});
    healthButton.setFillColor(sf::Color::Blue);
    healthButton.setPosition(centerX - buttonWidth / 2.f, centerY - buttonHeight - buttonSpacing);

    attackButton.setSize({buttonWidth, buttonHeight});
    attackButton.setFillColor(sf::Color::Red);
    attackButton.setPosition(centerX - buttonWidth / 2.f, centerY);

    attackSpeedButton.setSize({buttonWidth, buttonHeight});
    attackSpeedButton.setFillColor(sf::Color::Green);
    attackSpeedButton.setPosition(centerX - buttonWidth / 2.f, centerY + buttonHeight + buttonSpacing);

    // Textes des boutons
    healthText.setFont(font);
    healthText.setString("Increase Health");
    healthText.setCharacterSize(20);
    healthText.setFillColor(sf::Color::White);
    healthText.setPosition(
        healthButton.getPosition().x + (buttonWidth - healthText.getGlobalBounds().width) / 2.f,
        healthButton.getPosition().y + (buttonHeight - healthText.getGlobalBounds().height) / 2.f
    );

    attackText.setFont(font);
    attackText.setString("Increase Attack");
    attackText.setCharacterSize(20);
    attackText.setFillColor(sf::Color::White);
    attackText.setPosition(
        attackButton.getPosition().x + (buttonWidth - attackText.getGlobalBounds().width) / 2.f,
        attackButton.getPosition().y + (buttonHeight - attackText.getGlobalBounds().height) / 2.f
    );

    attackSpeedText.setFont(font);
    attackSpeedText.setString("Increase Attack Speed");
    attackSpeedText.setCharacterSize(20);
    attackSpeedText.setFillColor(sf::Color::White);
    attackSpeedText.setPosition(
        attackSpeedButton.getPosition().x + (buttonWidth - attackSpeedText.getGlobalBounds().width) / 2.f,
        attackSpeedButton.getPosition().y + (buttonHeight - attackSpeedText.getGlobalBounds().height) / 2.f
    );
}

void MenuLevel::render() {
    window.draw(background);
    window.draw(healthButton);
    window.draw(attackButton);
    window.draw(attackSpeedButton);
    window.draw(healthText);
    window.draw(attackText);
    window.draw(attackSpeedText);
}

void MenuLevel::handleEvent(const sf::Event& event) {
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);

        if (healthButton.getGlobalBounds().contains(mousePos)) {
            if (healthCallback) healthCallback();
        } else if (attackButton.getGlobalBounds().contains(mousePos)) {
            if (attackCallback) attackCallback();
        } else if (attackSpeedButton.getGlobalBounds().contains(mousePos)) {
            if (attackSpeedCallback) attackSpeedCallback();
        }
    }
}

void MenuLevel::setHealthCallback(const std::function<void()>& callback) {
    healthCallback = callback;
}

void MenuLevel::setAttackCallback(const std::function<void()>& callback) {
    attackCallback = callback;
}

void MenuLevel::setAttackSpeedCallback(const std::function<void()>& callback) {
    attackSpeedCallback = callback;
}
