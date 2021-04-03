#include <iostream>
#include <math.h> 
#include <random>

class RandomGenerator
{
public:
    static RandomGenerator& getInstance();
    static std::mt19937 gen;
private:
    // Constructor
    RandomGenerator();
};