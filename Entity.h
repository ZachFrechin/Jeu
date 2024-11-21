#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <memory>
#include <SFML/Graphics.hpp>
#include <string>

#include "Shot.h"

class Player;

class Entity {
public:

    Entity();
    Entity(const std::string& texturePath, double health, double attack, double defense, int speed, float sizeX, float sizeY);
    virtual ~Entity() = default;

    virtual void move(float x, float y);
    virtual bool takeDamage(double amount);
    virtual void applyForce(sf::Vector2f force, float power);
    virtual void shot(float deltaTime) = 0;
    virtual void draw(sf::RenderWindow& window);

    void setScale(float x, float y);
    void setPosition(sf::Vector2f position);

    sf::Vector2f getPosition() const;

    std::vector<std::unique_ptr<Shot>>& getShots();
    sf::Sprite getSprite() const;
    double getHealth() const;
    double getAttack() const;
    double getDefense() const;

    bool checkCollision(const Entity& other) const;
    bool checkCollision(const Shot& other) const;

protected:
    std::string texturePath;
    std::vector<std::unique_ptr<Shot>> shots;

    sf::Sprite sprite;
    sf::Texture texture;
    sf::Vector2f position;
    sf::Vector2f velocity;

    double health;
    double attack;
    double defense;
    int speed;

    float timerShot;
    float lastBulletShot;



};

#endif // ENTITY_HPP
