#ifndef WAVEFACTORY_H
#define WAVEFACTORY_H

#include <string>
#include <vector>
#include <memory>
#include "Wave.h"
#include "Enemy.h"
#include "json.hpp"

// Alias pour simplifier
using json = nlohmann::json;

class WaveFactory {
public:

    explicit WaveFactory(const std::string& jsonFilePath);
    std::vector<std::unique_ptr<Wave>> generateWave(int nb);

private:
    json waveData;
    std::vector<std::unique_ptr<Enemy>> createEnemies(const json& enemyData) const;
    std::unique_ptr<Wave> createWave(const json& waveJson);
    std::unique_ptr<Item>createLoot(const json& lootJson) const;
};

#endif // WAVEFACTORY_H
