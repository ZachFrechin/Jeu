#include "WaveFactory.h"
#include <fstream>
#include <stdexcept>

#include "Bonus.h"

// Constructeur : charge les données JSON depuis un fichier
#include "WaveFactory.h"
#include <fstream>
#include <stdexcept>

// Constructeur : charge les données des vagues et des ennemis
WaveFactory::WaveFactory(const std::string& waveFilePath, const std::string& enemyFilePath, const std::string& bonusFilePath) {
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
std::vector<std::unique_ptr<Wave>> WaveFactory::generateWave(int nb) {
    std::vector<std::unique_ptr<Wave>> waves;

    // Vérifier que le nombre demandé ne dépasse pas les vagues disponibles
    if (nb > waveData["waves"].size()) {
        throw std::out_of_range("Le nombre de vagues demandé dépasse les vagues disponibles dans le JSON");
    }

    // Créer chaque vague
    waves.reserve(nb);
    for (int i = 0; i < nb; ++i) {;
        waves.push_back(createWave(waveData["waves"][i]));
    }

    return waves;
}

std::vector<std::unique_ptr<Enemy>> WaveFactory::createEnemies(const json& enemyData) const {
    std::vector<std::unique_ptr<Enemy>> enemies;

    for (const auto& enemyInfo : enemyData) {
        // Trouver les détails de l'ennemi par son nom
        auto enemyDetails = findEnemy(enemyInfo["name"]);

        const int count = enemyInfo["count"];
        for (int i = 0; i < count; ++i) {
            // Créer l'ennemi
            auto enemy = std::make_unique<Enemy>(
                enemyDetails["texturePath"],
                enemyDetails["health"],
                enemyDetails["attack"],
                enemyDetails["defense"],
                enemyDetails["speed"],
                enemyDetails["sizeX"],
                enemyDetails["sizeY"]
            );

            // Ajouter les loots à l'ennemi
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

json WaveFactory::findEnemy(const std::string& enemyName) const {
    for (const auto& enemy : enemyData["enemies"]) {
        if (enemy["name"] == enemyName) {
            return enemy;
        }
    }
    throw std::runtime_error("Ennemi non trouvé : " + enemyName);
}





// Méthode pour créer une vague à partir des données JSON
std::unique_ptr<Wave> WaveFactory::createWave(const json& waveJson) {
    const auto& enemyData = waveJson["enemies"];
    auto enemies = createEnemies(enemyData);
    int enemyCount = static_cast<int>(enemies.size());

    // Créer une vague avec le nombre d'ennemis et la liste d'ennemis
    return std::make_unique<Wave>(enemyCount, std::move(enemies));
}

std::unique_ptr<Item> WaveFactory::createLoot(const std::string& bonusName) const {
    // Trouver le bonus correspondant dans bonusData
    for (const auto& bonusInfo : bonusData["bonuses"]) {
        if (bonusInfo["name"] == bonusName) {
            // Créer un Bonus à partir des informations
            return std::make_unique<Bonus>(
                bonusInfo["texturePath"],
                bonusInfo["sizeX"],
                bonusInfo["sizeY"],
                bonusInfo["stats"].get<std::vector<std::string>>(),
                bonusInfo["dropRate"],
                bonusInfo["amount"],
                bonusInfo["boostTime"]
            );
        }
    }

    // Si le bonus n'est pas trouvé
    throw std::runtime_error("Bonus non trouvé : " + bonusName);
}
