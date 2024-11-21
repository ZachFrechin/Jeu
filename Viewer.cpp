#include "Viewer.h"

// Constructor
#include "Viewer.h"

// Constructeur
Viewer::Viewer(sf::RenderWindow& window, GameManager& gameManager)
    : window(window), gameManager(gameManager) {
    // Charger la police
    if (!font.loadFromFile("assets/arial.ttf")) {
        throw std::runtime_error("Impossible de charger la police !");
    }

    // Initialisation des textes
    waveText.setFont(font);
    waveText.setCharacterSize(24);
    waveText.setFillColor(sf::Color::White);
    waveText.setPosition(10.f, 10.f);

    playerHealthText.setFont(font);
    playerHealthText.setCharacterSize(24);
    playerHealthText.setFillColor(sf::Color::White);
    playerHealthText.setPosition(10.f, 40.f);

    // Initialisation des rectangles de fond
    waveBackground.setFillColor(sf::Color(0, 0, 0, 150)); // Fond noir semi-transparent
    waveBackground.setSize(sf::Vector2f(150.f, 30.f)); // Taille arbitraire
    waveBackground.setPosition(10.f, 10.f);

    playerHealthBackground.setFillColor(sf::Color(0, 0, 0, 150)); // Fond noir semi-transparent
    playerHealthBackground.setSize(sf::Vector2f(150.f, 30.f)); // Taille arbitraire
    playerHealthBackground.setPosition(10.f, 40.f);
}


void Viewer::updateUI() {
    // Mettre à jour le texte de la vague
    int waveNumber = gameManager.getCurrentWaveIndex() + 1;
    waveText.setString("Wave: " + std::to_string(waveNumber));

    // Mettre à jour le texte de la santé du joueur
    int playerHealth = gameManager.getPlayer().getHealth();
    playerHealthText.setString("Health: " + std::to_string(playerHealth));

    // Adapter la taille des rectangles au texte
    sf::FloatRect waveBounds = waveText.getGlobalBounds();
    waveBackground.setSize(sf::Vector2f(waveBounds.width + 10.f, waveBounds.height + 10.f));

    sf::FloatRect healthBounds = playerHealthText.getGlobalBounds();
    playerHealthBackground.setSize(sf::Vector2f(healthBounds.width + 10.f, healthBounds.height + 10.f));
}


void Viewer::render() {
    window.clear();

    // Dessiner le jeu
    gameManager.draw();

    // Mettre à jour et dessiner l'interface utilisateur
    updateUI();

    // Dessiner les fonds
    window.draw(waveBackground);
    window.draw(playerHealthBackground);

    // Dessiner les textes
    window.draw(waveText);
    window.draw(playerHealthText);

    window.display();
}
