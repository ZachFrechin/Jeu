#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <SFML/Graphics.hpp>
#include <string>

class Player;

class Entity {
public:
    Entity();
    Entity(std::string texturePath, double health, double attack, double defense, int speed, float sizeX, float sizeY);
    virtual ~Entity() = default;

    virtual void update(float deltaTime, Player player);
    void setScale(float x, float y);
    void setPosition(sf::Vector2f position);
    sf::Vector2f getPosition();
    void move(float x, float y);

    const sf::Sprite& getSprite() const;

    // Gestion des collisions
    bool checkCollision(const Entity& other) const;
    void setColliding(bool colliding);
    bool getColliding() const;
    void applyForce(sf::Vector2f force); // Appliquer une force pour le "bump"

protected:
    std::string texturePath;
    sf::Sprite sprite;
    sf::Texture texture;
    double health;
    double attack;
    double defense;
    int speed;
    sf::Vector2f position;

    sf::Vector2f velocity; // Vitesse actuelle de l'entité
    bool isColliding = false;
};

#endif // ENTITY_HPP
