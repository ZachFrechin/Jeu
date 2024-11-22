#include "Entity.h"
#include <iostream>
#include <ctime>
#include <cmath>
#include "Player.h"

Entity::Entity() : Entity("assets/default.png", 0, 0, 0, 0, 0.f, 0.f){}
Entity::Entity(const std::string& texturePath, double health, double attack, double defense, double speed, float sizeX, float sizeY):
texturePath(texturePath), health(health), attack(attack), defense(defense), speed(speed), maxHealth(health) {
    if (!texture.loadFromFile(texturePath)) {
        std::cout << "Failed to load texture: " << texturePath << std::endl;
    }
        sprite.setTexture(texture);
        sprite.setColor(sf::Color(255, 255, 255, 255));
        lastBulletShot = 0.f;
        timerShot = 1000.f;
        setScale(sizeX, sizeY);
        setPosition(sf::Vector2f(static_cast<float>(rand() % 1700), static_cast<float>(rand() % 1000)));
}

// TODO : override function -----------------------------------------


// TODO : default inherit function (overrideable) -------------------
void Entity::move(float x, float y) {
    position.x += x;
    position.y += y;
    sprite.setPosition(position);
}

bool Entity::checkCollision(const Entity& other) const {
    if (sprite.getGlobalBounds().intersects(other.getSprite().getGlobalBounds())) {
        return true;
    }
    return false;
}

bool Entity::checkCollision(const Shot& other) const {
    if (sprite.getGlobalBounds().intersects(other.getSprite().getGlobalBounds())) {
        return true;
    }
    return false;
}

void Entity::applyForce(sf::Vector2f force, const float power) {
    if (const float length = std::sqrt(force.x * force.x + force.y * force.y); length != 0) {
        force /= length;
        force *= power;
    }
    velocity += force;
}

void Entity::draw(sf::RenderWindow& window) {
    window.draw(sprite);
    for(const auto& shot : shots) {
        window.draw(shot->getSprite());
    }
}

bool Entity::takeDamage(const double amount) {
    this->health -= amount;
    return health < 0;
}

void Entity::boostStat(double& stat, float& statTimer, double& statAmount, bool& statLogic, const float boostTime, const double amount) {
    if(statAmount != 0.0) {
        resetStat(stat, statTimer, statAmount, statLogic);
    }
    statTimer = boostTime;
    statAmount = amount;
    stat += amount;
    statLogic = true;
}

void Entity::deboostStat(double& stat, float& statTimer, double& statAmount, bool& statLogic, const float deltaTime) {
    if(statLogic) {
        if(statTimer <= 0.f) {
            stat -= statAmount;
            statTimer = 0;
            statAmount = 0;
            statLogic = false;;
        }else {
            statTimer -= deltaTime;
        }
    }
}

void Entity::resetStat(double& stat, float& statTimer, double& statAmount, bool& statLogic) {
    stat -= statAmount;
    statTimer = 0;
    statAmount = 0;
    statLogic = false;;
}



void Entity::bound(const float arenaWidth, const float arenaHeight) {
    sf::Vector2f position = sprite.getPosition();
    const sf::FloatRect bounds = sprite.getGlobalBounds();

    if (position.x - bounds.width / 2 < 0) {
        position.x = bounds.width / 2;
        velocity.x = std::abs(velocity.x);
    } else if (position.x + bounds.width / 2 > arenaWidth) {
        position.x = arenaWidth - bounds.width / 2;
        velocity.x = -std::abs(velocity.x);
    }

    if (position.y - bounds.height / 2 < 0) {
        position.y = bounds.height / 2;
        velocity.y = std::abs(velocity.y);
    } else if (position.y + bounds.height / 2 > arenaHeight) {
        position.y = arenaHeight - bounds.height / 2;
        velocity.y = -std::abs(velocity.y);
    }
    setPosition(position);
}


// TODO : getter ----------------------------------------------------
sf::Sprite Entity::getSprite() const {
    return sprite;
}

sf::Vector2f Entity::getPosition() const {
    return position;
}

std::vector<std::unique_ptr<Shot>>& Entity::getShots()  {
    return shots;
}

double Entity::getHealth() const {
    return health;
}

double Entity::getAttack() const {
    return attack;
}

double Entity::getDefense() const {
    return defense;
}


// TODO : setter ----------------------------------------------------
void Entity::setScale(const float x, const float y) {
    const sf::Vector2u textureSize = texture.getSize();
    sprite.setScale(x / textureSize.x, y / textureSize.y);
}

void Entity::setPosition(sf::Vector2f newPos) {
    position = newPos;
    sprite.setPosition(position);
}

void Entity::setHealth(const double health) {
    this->health = health;
}

void Entity::addHealth(const double health) {
    if(this->health + health >= maxHealth) {
        this->health = maxHealth;
    }else {
        this->health += health;
    }
}

// TODO : bonus function
void Entity::boostAttack(const double amount, const float boostTime) {
    boostStat(attack, attackBoostTimer, attackBoostAmount, attackBoost, boostTime, amount);
}

void Entity::debuffAttack(const float deltaTime) {
    deboostStat(attack, attackBoostTimer, attackBoostAmount, attackBoost, deltaTime);
}

void Entity::boostSpeed(const double amount, const float boostTime) {
    boostStat(speed, speedBoostTimer, speedBoostAmount, speedBoost, boostTime, amount);
}

void Entity::debuffSpeed(const float deltaTime) {
    deboostStat(speed, speedBoostTimer, speedBoostAmount, speedBoost, deltaTime);
}
























