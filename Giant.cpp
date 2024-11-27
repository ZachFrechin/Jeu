#include "Giant.h"

Giant::Giant(const int difficulty)
    : Enemy("assets/giant.png",
        200 * difficulty,
        30 * difficulty,
        20 * difficulty,
        150 * (difficulty / 2),
        150.f,
        100.f,
        20){}
