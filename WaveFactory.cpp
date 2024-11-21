#include "WaveFactory.h"
#include <fstream>
#include <stdexcept>

#include "Bonus.h"

// Constructeur : charge les données JSON depuis un fichier
WaveFactory::WaveFactory(const std::string& jsonFilePath) {
    // Charger le JSON depuis un fichier
    std::ifstream file(jsonFilePath);
    if (!file.is_open()) {
        throw std::runtime_error("Impossible d'ouvrir le fichier JSON");
    }
    file >> waveData; // Charger les données JSON dans l'objet `waveData`
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
        const int count = enemyInfo["count"];
        for (int i = 0; i < count; ++i) {
            // Créer l'ennemi
            auto enemy = std::make_unique<Enemy>(
                enemyInfo["texturePath"],
                enemyInfo["health"],
                enemyInfo["attack"],
                enemyInfo["defense"],
                enemyInfo["speed"],
                enemyInfo["sizeX"],
                enemyInfo["sizeY"]
            );

            // Ajouter les loots à l'ennemi
            if (enemyInfo.contains("loot")) {
                for (const auto& lootInfo : enemyInfo["loot"]) {
                    auto loot = createLoot(lootInfo);
                    enemy->addLoot(std::move(loot));
                }
            }
            enemies.push_back(std::move(enemy));
        }
    }
    return enemies;
}


// Méthode pour créer une vague à partir des données JSON
std::unique_ptr<Wave> WaveFactory::createWave(const json& waveJson) {
    const auto& enemyData = waveJson["enemies"];
    auto enemies = createEnemies(enemyData);
    int enemyCount = static_cast<int>(enemies.size());

    // Créer une vague avec le nombre d'ennemis et la liste d'ennemis
    return std::make_unique<Wave>(enemyCount, std::move(enemies));
}

std::unique_ptr<Item> WaveFactory::createLoot(const json& lootJson) const {
    if (lootJson["type"] == "bonus") {
        return std::move(std::make_unique<Bonus>(
            lootJson["texturePath"],
            lootJson["sizeX"],
            lootJson["sizeY"],
            lootJson["stats"].get<std::vector<std::string>>(),
            lootJson["dropRate"]
        ));
    }

    // Si d'autres types d'items sont ajoutés, gérer ici.
    throw std::runtime_error("Type de loot non supporté : " + lootJson["type"].get<std::string>());
}

