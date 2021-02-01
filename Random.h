#include <random>

class Random {
public:

    static double get_random_double();

private:
    static std::mt19937 rng;
};
