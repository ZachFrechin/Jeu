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
)

# Liez SFML à votre projet
target_link_libraries(Jeu sfml-main)

target_link_libraries(Jeu sfml-system sfml-window sfml-graphics)
