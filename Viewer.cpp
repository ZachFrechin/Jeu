#include "Viewer.h"

// Constructor
#include "Viewer.h"

#include <iostream>

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

    score.setFont(font);
    score.setCharacterSize(24);
    score.setFillColor(sf::Color::White);
    score.setPosition(10.f, 80.f);

    xpBarBackground.setFillColor(sf::Color(0, 0, 0, 150)); // Fond noir semi-transparent
    xpBarBackground.setSize(sf::Vector2f(200.f, 20.f)); // Taille de la barre
    xpBarBackground.setPosition(10.f, 120.f);

    xpBarFill.setFillColor(sf::Color(0, 255, 0, 200)); // Remplissage vert
    xpBarFill.setSize(sf::Vector2f(0.f, 20.f)); // Taille initiale (0% rempli)
    xpBarFill.setPosition(10.f, 120.f);

    // Initialisation des rectangles de fond
    waveBackground.setFillColor(sf::Color(0, 0, 0, 150)); // Fond noir semi-transparent
    waveBackground.setSize(sf::Vector2f(150.f, 30.f)); // Taille arbitraire
    waveBackground.setPosition(10.f, 10.f);

    playerHealthBackground.setFillColor(sf::Color(0, 0, 0, 150)); // Fond noir semi-transparent
    playerHealthBackground.setSize(sf::Vector2f(150.f, 30.f)); // Taille arbitraire
    playerHealthBackground.setPosition(10.f, 40.f);

    scoreBackground.setFillColor(sf::Color(0, 0, 0, 150));
    scoreBackground.setSize(sf::Vector2f(150.f, 30.f));
    scoreBackground.setPosition(10.f, 80.f);
}


void Viewer::updateUI() {
    // Mettre à jour le texte de la vague
    int waveNumber = gameManager.getCurrentWaveIndex() + 1;
    waveText.setString("Wave: " + std::to_string(waveNumber));

    // Mettre à jour le texte de la santé du joueur
    int playerHealth = gameManager.getPlayer().getHealth();
    playerHealthText.setString("Health: " + std::to_string(playerHealth));

    // Mettre à jour le texte du score
    int playerScore = gameManager.getPlayer().getScore();
    score.setString("Score: " + std::to_string(playerScore));

    // Mettre à jour la barre d'XP
    updateXPBar();

    // Adapter la taille des rectangles au texte
    sf::FloatRect waveBounds = waveText.getGlobalBounds();
    waveBackground.setSize(sf::Vector2f(waveBounds.width + 10.f, waveBounds.height + 10.f));

    sf::FloatRect healthBounds = playerHealthText.getGlobalBounds();
    playerHealthBackground.setSize(sf::Vector2f(healthBounds.width + 10.f, healthBounds.height + 10.f));

    sf::FloatRect scoreBounds = score.getGlobalBounds();
    scoreBackground.setSize(sf::Vector2f(scoreBounds.width + 10.f, scoreBounds.height + 10.f));
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
    window.draw(scoreBackground);

    // Dessiner la barre d'XP
    window.draw(xpBarBackground);
    window.draw(xpBarFill);

    // Dessiner les textes
    window.draw(waveText);
    window.draw(playerHealthText);
    window.draw(score);

    window.display();
}


void Viewer::updateXPBar() {
    const Player& player = gameManager.getPlayer();

    // Calculer le score requis pour le niveau suivant
    int currentLevel = player.getLevel();
    int baseLevelScore = 200; // Le score de base pour atteindre le niveau 2
    int requiredScore = baseLevelScore * currentLevel;
    int previousLevelScore = baseLevelScore * (currentLevel - 1);

    // Calculer la progression de l'XP (entre 0 et 1)
    int currentScore = player.getScore();
    float xpProgress = static_cast<float>(currentScore - previousLevelScore) /
                       static_cast<float>(requiredScore - previousLevelScore);

    // Assurez-vous que la progression est entre 0 et 1
    xpProgress = std::clamp(xpProgress, 0.f, 1.f);

    // Mettre à jour la taille de la barre d'XP
    xpBarFill.setSize(sf::Vector2f(200.f * xpProgress, 20.f));
}

