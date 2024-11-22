//
// Created by zachf on 21/11/2024.
//

#ifndef ITEM_H
#define ITEM_H
#include "Entity.h"


class Item : public Entity {
public:
    Item();
    Item(const std::string& texturePath, float sizeX, float sizeY, float dropRate);

    virtual void loot(Player &player, float time);
    void shot(float deltaTime) override;
    void update() const;
    void draw(sf::RenderWindow &window) override;

    float getDropRate() const { return dropRate; }

    void setDropped(const bool dropped) { this->dropped = dropped; }

private:
    float TTL;
    float dropRate;
    bool dropped = false;

};



#endif //ITEM_H
