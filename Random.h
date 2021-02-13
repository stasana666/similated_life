#include <random>

class Random {
public:

    static double get_random_double();

    static int get_random_index(int n);

private:

    static std::mt19937 rng;
};
