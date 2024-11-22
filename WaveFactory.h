#ifndef WAVEFACTORY_H
#define WAVEFACTORY_H

#include <string>
#include <vector>
#include <memory>
#include "Wave.h"
#include "Enemy.h"
#include "Item.h"
#include "Bonus.h"
#include "json.hpp"


using json = nlohmann::json;

class WaveFactory {
public:

    WaveFactory(const std::string& waveFilePath, const std::string& enemyFilePath, const std::string& bonusFilePath);

    std::vector<std::unique_ptr<Wave>> generateWave(int nb);

private:
    json waveData;
    json enemyData;
    json bonusData;

    json findEnemy(const std::string& enemyName) const;
    std::vector<std::unique_ptr<Enemy>> createEnemies(const json& enemyData) const;
    std::unique_ptr<Item> createLoot(const std::string& bonusName) const;
    std::unique_ptr<Wave> createWave(const json& waveJson);
};

#endif