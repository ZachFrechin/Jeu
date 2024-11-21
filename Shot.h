//
// Created by zachf on 19/11/2024.
//
#include <SFML/Graphics.hpp>
#ifndef SHOT_H
#define SHOT_H



class Shot {
public:
    Shot();
    Shot(int speed, sf::Vector2f direction, sf::Vector2f position, const std::string &texturePath, int attack, float sizeX, float sizeY);
    ~Shot() = default;

    void update(float deltaTime, const sf::RenderWindow& window);
    bool isMarkedForDeletion() const;

    sf::Sprite getSprite() const;
    int getAttack() const;

private:
    sf::Texture texture;
    std::string texturePath;
    sf::Sprite sprite;
    sf::Vector2f direction;
    sf::Vector2f position;

    int speed;
    int attack;
    bool isOutOfBounds = false;
};




#endif //SHOT_H
