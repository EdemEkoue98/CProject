#include <iostream>
#include "RandomWalk.cpp"

class RandomWalkGenerator
{
public:
    // Methods
    static RandomWalkGenerator& getInstance();
    static RandomWalk generate(int, std::string, float, float, float);
private:
    // Constructor
    RandomWalkGenerator();
    // Methods
    static std::vector<float> generateInnovationProcess(int, std::string, float, float);
    static int convertDistribution(std::string);
};