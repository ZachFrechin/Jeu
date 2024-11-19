#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <SFML/Graphics.hpp>

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
    void handleInput();

    const sf::Sprite& getSprite() const;

    bool checkCollision(const Entity& other) const;
    void setColliding(bool colliding);

protected:
    std::string texturePath;
    sf::Sprite sprite;
    sf::Texture texture;
    double health{};
    double attack{};
    double defense{};
    int speed{};
    sf::Vector2f position;

    bool isColliding = false;
};
#endif
