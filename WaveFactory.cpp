#include "WaveFactory.h"
#include <fstream>
#include <iostream>
#include <stdexcept>

#include "EnemyFactory.h"

// Constructeur : charge les données des vagues, ennemis et bonus
WaveFactory::WaveFactory(const std::string& waveFilePath, const std::string& enemyFilePath, const std::string& bonusFilePath, int difficulty) : difficulty(difficulty) {
    std::ifstream waveFile(waveFilePath);
    if (!waveFile.is_open()) {
        throw std::runtime_error("Impossible d'ouvrir le fichier waves.json");
    }
    waveFile >> waveData;

    std::ifstream enemyFile(enemyFilePath);
    if (!enemyFile.is_open()) {
        throw std::runtime_error("Impossible d'ouvrir le fichier enemies.json");
    }
    enemyFile >> enemyData;

    std::ifstream bonusFile(bonusFilePath);
    if (!bonusFile.is_open()) {
        throw std::runtime_error("Impossible d'ouvrir le fichier bonus.json");
    }
    bonusFile >> bonusData;
}

// Méthode pour générer un nombre de vagues spécifié
std::vector<std::unique_ptr<Wave>> WaveFactory::generateWave(const int nb) {
    std::vector<std::unique_ptr<Wave>> waves;

    if (nb > waveData["waves"].size()) {
        throw std::out_of_range("Le nombre de vagues demandé dépasse les vagues disponibles dans le JSON");
    }

    waves.reserve(nb);
    for (int i = 0; i < nb; ++i) {
        waves.push_back(createWave(waveData["waves"][i]));
    }

    return waves;
}

// Trouve un ennemi par son nom dans enemyData
json WaveFactory::findEnemy(const std::string& enemyName) const {
    for (const auto& enemy : enemyData["enemies"]) {
        if (enemy["name"] == enemyName) {
            return enemy;
        }
    }
    throw std::runtime_error("Ennemi non trouvé : " + enemyName);
}

// Crée un bonus à partir de bonusData
std::unique_ptr<Item> WaveFactory::createLoot(const std::string& bonusName) const {
    for (const auto& bonusInfo : bonusData["bonuses"]) {
        if (bonusInfo["name"] == bonusName) {
            return std::make_unique<Bonus>(
                bonusInfo["texturePath"],
                bonusInfo["sizeX"],
                bonusInfo["sizeY"],
                bonusInfo["stats"],
                bonusInfo["dropRate"],
                bonusInfo["amount"],
                bonusInfo["boostTime"]
            );
        }
    }
    throw std::runtime_error("Bonus non trouvé : " + bonusName);
}

// Crée une liste d'ennemis
std::vector<std::unique_ptr<Enemy>> WaveFactory::createEnemies(const json& enemiesInfo) const {
    std::vector<std::unique_ptr<Enemy>> enemies;

    for (const auto& enemyInfo : enemiesInfo) {
        const int count = enemyInfo["count"];
        const std::string& enemyName = enemyInfo["name"];

        for (int i = 0; i < count; ++i) {
            // Utiliser EnemyFactory pour créer l'ennemi
            auto enemy = EnemyFactory::createEnemy(enemyName, difficulty);

            // Ajouter les loots à l'ennemi
            json enemyDetails = findEnemy(enemyName);
            if (enemyDetails.contains("loot")) {
                for (const auto& lootName : enemyDetails["loot"]) {
                    auto loot = createLoot(lootName);
                    enemy->addLoot(std::move(loot));
                }
            }

            enemies.push_back(std::move(enemy));
        }
    }

    return enemies;
}

// Crée une vague à partir des données JSON
std::unique_ptr<Wave> WaveFactory::createWave(const json& waveJson) {
    const auto& enemiesInfo = waveJson["enemies"];
    auto enemies = createEnemies(enemiesInfo);
    int enemyCount = static_cast<int>(enemies.size());

    return std::make_unique<Wave>(enemyCount, std::move(enemies), difficulty);
}
