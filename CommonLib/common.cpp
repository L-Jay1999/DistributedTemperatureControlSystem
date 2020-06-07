#include "common.h"

#include <QtCore>
#include <random>

// 对 quint16 类型进行特化
quint16 getRandomInt(quint16 a, quint16 b)
{
    static std::random_device rd;
    static std::mt19937 rng(rd());
    std::uniform_int_distribution gen(a, b);
    return gen(rng);
}
