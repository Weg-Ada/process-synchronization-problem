#include <random>
#include "utils.h"

int utils::generateRandomInt(int begin, int end) {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist(begin, end);

    return (int)dist(mt);
}
