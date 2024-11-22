//
// Created by zachf on 21/11/2024.
//

#include "Bonus.h"
#include <iostream>

#include "Player.h"

Bonus::Bonus() {}
Bonus::Bonus(const std::string& texturePath, const float sizeX, const float sizeY, const std::vector<std::string> &stats, const float dropRate, const double amount, const float boostTime) : Item(texturePath, sizeX, sizeY, dropRate), stats(stats), amount(amount), boostTime(boostTime) {}

void Bonus::loot(Player& player, const float time)
{
    std::map<std::string, int> map = getStatsMap();
    for(const auto stat : stats) {
        switch(map[stat]) {
            case 1:
                player.addHealth(amount);
            case 101:
                player.boostAttack(amount, boostTime);
                break;
            case 201 :
                player.boostSpeed(amount, boostTime);
            default:
                std::cout << "Error in stats bonus check";
        }
    }
}


std::map<std::string, int> Bonus::getStatsMap() {
    std::map<std::string, int> map;
    map["attack"] = 101;
    map["health"] = 1;
    map["speed"] = 201;
    return map;
} ;
