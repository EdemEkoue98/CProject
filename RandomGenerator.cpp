#include "RandomGenerator.h"

std::random_device rd;
std::mt19937 RandomGenerator::gen(rd());

// Constructor
RandomGenerator::RandomGenerator()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::cout << "Generator created" << std::endl;
}

// Method
RandomGenerator& RandomGenerator::getInstance()
{
    static RandomGenerator instance;
    return instance;
}
