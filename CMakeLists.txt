cmake_minimum_required(VERSION 3.16)
project(Jeu)

set(CMAKE_CXX_STANDARD 17)

# Ajoutez le chemin vers SFML
set(SFML_DIR "C:/Users/zachf/Documents/SFML-2.6.2/lib/cmake/SFML")

# Trouvez SFML
find_package(SFML 2.5 COMPONENTS system window graphics REQUIRED)

# Ajoutez votre exécutable
add_executable(Jeu main.cpp
        GameManager.cpp
        GameManager.h
        Viewer.cpp
        Viewer.h
        Entity.cpp
        Entity.h
        Player.cpp
        Player.h
        Enemy.cpp
        Enemy.h
        Wave.cpp
        Wave.h
        Shot.cpp
        Shot.h
        Shot.cpp
        Shot.h
        Collision.cpp
        Collision.h
        WaveFactory.cpp
        WaveFactory.h
        json.hpp
        Item.cpp
        Item.h
        Bonus.cpp
        Bonus.h
        Entity.h
        Entity.h
        Goblin.cpp
        Goblin.h
        Giant.cpp
        Giant.h
        EnemyFactory.h
        orc.cpp
        orc.h
        Menu.cpp
        Menu.h
        MenuLevel.cpp
        MenuLevel.h
)

# Liez SFML à votre projet
target_link_libraries(Jeu sfml-main)

target_link_libraries(Jeu sfml-system sfml-window sfml-graphics)
