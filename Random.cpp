#include "Random.h"

std::mt19937 Random::rng;

double Random::get_random_double() {
    return static_cast<double>(rng() - std::mt19937::min())
         / static_cast<double>(std::mt19937::max() - std::mt19937::min());
}
