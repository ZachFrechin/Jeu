//
// Created by zachf on 21/11/2024.
//

#ifndef BONUS_H
#define BONUS_H
#include "Item.h"


class Bonus : public Item {
public :
    Bonus();
    Bonus(const std::string& texturePath, float sizeX, float sizeY, std::vector<std::string> stats, float dropRate);

private:
    void loot(Player& player) override;
    void apply(Player& player);

    std::vector<std::string> stats;
};

#endif //BONUS_H
