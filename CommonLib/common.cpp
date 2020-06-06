#include "common.h"

#include <random>

int getRandomInt(int low_bound, int up_bound)
{
    static std::random_device rd;
    static std::mt19937 rng(rd());
    std::uniform_int_distribution gen(low_bound, up_bound);
    return gen(rng);
}
