#include "RandomWalkGenerator.h"
#include "RandomGenerator.cpp"


// Constructor
RandomWalkGenerator::RandomWalkGenerator()
{
    std::cout << "Random-Walk generator created" << std::endl;
}

// Methods
RandomWalkGenerator& RandomWalkGenerator::getInstance()
{
    static RandomWalkGenerator instance;
    return instance;
}

RandomWalk RandomWalkGenerator::generate(int nb_interval, std::string distribution = "binomial", float initial_value = 0, float param1 = 0, float param2 = 0)
{
    // Generates the vector containing the variables for each step of the walk
    std::vector<float> innovation_process = generateInnovationProcess(nb_interval, distribution, param1, param2);

    // Creates a vector containing the values for each step of the walk
    std::vector<float> walk_values(nb_interval + 1);

    // Fill the vector
    walk_values[0] = initial_value;
    for (int i = 1; i <= nb_interval; i++)
    {
        walk_values[i] = walk_values[i - 1] + innovation_process[i];
    }

    // Creating the random walk object
    RandomWalk walk(walk_values, nb_interval, distribution, initial_value, param1, param2);

    return walk;
}


// Methods
std::vector<float> RandomWalkGenerator::generateInnovationProcess(int n, std::string distribution, float param1, float param2)
{
    // Using a singleton to generator a random generator
    RandomGenerator rdGen = RandomGenerator::getInstance();

    std::binomial_distribution<int> distrib_bin(param1, param2);
    std::uniform_real_distribution<float> distrib_uni(param1, param2);
    std::normal_distribution<float> distrib_norm(param1, param2);

    if (param1 == 0 && param2 == 0)
    {
        distrib_bin = std::binomial_distribution<int>(1, 0.5);
        distrib_uni = std::uniform_real_distribution<float>(-1, 1);
        distrib_norm = std::normal_distribution<float>(0, 1);
    }

    // Creates a vector containing the changes for each step of the walk
    std::vector<float> process(n + 1);

    for (int i = 0; i <= n; i++)
    {
        switch (convertDistribution(distribution))
        {
        case 0:            // Binomial
            process[i] = distrib_bin(rdGen.gen);
            if (process[i] == 0)
                process[i] = -1;
            break;
        case 1:            // Uniform
            process[i] = distrib_uni(rdGen.gen);
            break;
        case 2:            // Normal
            process[i] = distrib_norm(rdGen.gen);
            break;
        default:            // Other (null)
            process[i] = 0;
        }
    }
    return process;
}

int RandomWalkGenerator::convertDistribution(std::string walk_distribution)
{
    int distribution;
    if (walk_distribution == "binomial")
        distribution = 0;
    else if (walk_distribution == "uniform")
        distribution = 1;
    else if (walk_distribution == "normal")
        distribution = 2;
    else
    {
        try
        {
            throw "distribution_invalid_exception";
        }
        catch (const char* msg)
        {
            std::cerr << msg << std::endl;
            exit(3);
        }
    }
    return distribution;
}