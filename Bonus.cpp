//
// Created by zachf on 21/11/2024.
//

#include "Bonus.h"
#include <iostream>

Bonus::Bonus() {}
Bonus::Bonus(const std::string& texturePath, float sizeX, float sizeY, std::vector<std::string> stats, float dropRate) : Item(texturePath, sizeX, sizeY, dropRate), stats(stats) {}

void Bonus::loot(Player& player) {
    std::cout << "Bonus::loot" << std::endl;
}
