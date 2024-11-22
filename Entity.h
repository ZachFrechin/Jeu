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
    Entity(const std::string& texturePath, double health, double attack, double defense, double speed, float sizeX, float sizeY);
    virtual ~Entity() = default;

    virtual void move(float x, float y);
    virtual bool takeDamage(double amount);
    virtual void applyForce(sf::Vector2f force, float power);
    virtual void shot(float deltaTime) = 0;
    virtual void draw(sf::RenderWindow& window);
    virtual void boostStat(double& stat, float& statTimer, double& statAmount, bool& statLogic, float boostTime, double amount);
    virtual void deboostStat(double &stat, float &statTimer, double &statAmount, bool &statLogic, float deltaTime);
    virtual void resetStat(double& stat, float& statTimer, double& statAmount, bool& statLogic);
    void bound(float arenaWidth, float arenaHeight);
    void addHealth(const double health);

    void setScale(float x, float y);
    void setPosition(sf::Vector2f position);
    void setHealth(double health);

    sf::Vector2f getPosition() const;
    std::vector<std::unique_ptr<Shot>>& getShots();
    sf::Sprite getSprite() const;
    double getHealth() const;
    double getAttack() const;
    double getDefense() const;

    bool checkCollision(const Entity& other) const;
    bool checkCollision(const Shot& other) const;

    // Bonus function
    void boostAttack(double amount, float boostTime);
    void debuffAttack(float deltaTime);
    void boostSpeed(double amount, float boostTime);
    void debuffSpeed(float deltaTime);

protected:
    std::string texturePath;
    std::vector<std::unique_ptr<Shot>> shots;

    sf::Sprite sprite;
    sf::Texture texture;
    sf::Vector2f position;
    sf::Vector2f velocity;

    double health;
    double maxHealth;
    double attack;
    double defense;
    double speed;

    float timerShot;
    float lastBulletShot;

    // ATTACK
    float attackBoostTimer = 0.f;
    double attackBoostAmount = 0.0;
    bool attackBoost = false;

    //SPEED
    float speedBoostTimer = 0.f;
    double speedBoostAmount = 0.0;
    bool speedBoost = false;


};

#endif // ENTITY_HPP
