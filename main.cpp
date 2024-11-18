#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

int main()
{
    // Taille de la fenêtre
    const int windowWidth = 800;
    const int windowHeight = 600;

    // Création de la fenêtre
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Arena Game", sf::Style::Close);
    window.setFramerateLimit(60);

    // Chargement de l'image d'arène
    sf::Texture arenaTexture;
    if (!arenaTexture.loadFromFile("arena.png")) // Remplacez "arena.png" par le chemin de votre image
    {
        return -1; // Erreur si l'image ne se charge pas
    }
    sf::Sprite arenaSprite(arenaTexture);

    // Création du joueur
    sf::RectangleShape player(sf::Vector2f(50.f, 50.f));
    player.setFillColor(sf::Color::Red);
    player.setPosition(windowWidth / 2.f, windowHeight / 2.f); // Position initiale au centre

    // Vitesse de déplacement
    const float playerSpeed = 5.0f;

    // Boucle principale
    while (window.isOpen())
    {
        // Gestion des événements
        sf::Event event{};
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Gestion du clavier pour déplacer le joueur
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            player.move(0, -playerSpeed);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            player.move(0, playerSpeed);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            player.move(-playerSpeed, 0);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            player.move(playerSpeed, 0);

        // Nettoyage de l'écran
        window.clear();

        // Dessin des éléments
        window.draw(arenaSprite); // Dessin de l'arène
        window.draw(player);      // Dessin du joueur

        // Affichage
        window.display();
    }

    return 0;
}
