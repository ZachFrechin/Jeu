//
// Created by zachf on 21/11/2024.
//

#ifndef BONUS_H
#define BONUS_H
#include "Item.h"


class Bonus : public Item {
public :
    Bonus();
    Bonus(const std::string& texturePath, float sizeX, float sizeY, const std::vector<std::string> &stats, float dropRate, double amount, float boostTime);

private:
    void loot(Player& player, float time) override;
    void apply(Player& player);

    static std::map<std::string, int> getStatsMap();

    std::vector<std::string> stats;
    double amount;
    float boostTime;
};

#endif //BONUS_H
