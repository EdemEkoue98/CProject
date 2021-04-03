#include "RandomWalk.h"

// Constructors
RandomWalk::RandomWalk(std::vector<float> values, int nb_interval, std::string distribution = "binomial", float initial_value = 0, float param1 = 0, float param2 = 0)
{
    setN(nb_interval);
    setInitialValue(initial_value);
    setDistribution(distribution);
    setValues(values);
    initVariables(param1, param2);
}

RandomWalk::RandomWalk(const class RandomWalk& other)
{
    setN(other.n);
    setInitialValue(other.initial_value);
    setDistribution(other.distribution);
    setValues(other.values);
    initVariables(other.param1, other.param2);
}

// Getters
int RandomWalk::getN()
{
    return n;
}

std::string RandomWalk::getDistribution()
{
    return distribution;
}

float RandomWalk::getInitialValue()
{
    return initial_value;
}

float RandomWalk::getParam(int nb)
{
    if (nb == 1)
        return param1;
    else
        return param2;
}

// Setters
void RandomWalk::setN(int nb_interval)
{
    RandomWalk::n = nb_interval;
}

void RandomWalk::setDistribution(std::string distribution)
{
    RandomWalk::distribution = distribution;
}

void RandomWalk::setInitialValue(float value)
{
    RandomWalk::initial_value = value;
}

void RandomWalk::setValues(std::vector<float> walk_values)
{
    RandomWalk::values = walk_values;
}

// Overloads
float RandomWalk::operator[](int index)
{
    if (index< 0 || index > n)
    {
        try
        {
            throw "time_index_invalid_exception";
        }
        catch (const char* msg)
        {
            std::cerr << msg << std::endl;
        }
        exit(3);
    }
    else
        return values[index];
}

// Methods
float RandomWalk::computeAvg()
{
    if (average == 0)
    {
        float sum = 0;
        for (int i = 0; i <= n; i++)
        {
            sum = sum + values[i];
        }
        return sum / n;
    }
    else
        return average;
}

float RandomWalk::computeStdDev()
{
    if (standard_deviation == 0)
        return sqrt(computeVar());
    else
        return standard_deviation;
}

float RandomWalk::computeVar()
{
    if (variance == 0)
    {
        float SS = 0;
        float average = computeAvg();
        for (int i = 0; i <= n; i++)
        {
            SS = SS + pow(values[i] - average, 2);
        }
        return SS / n;
    }
    else
        return variance;
}

void RandomWalk::initVariables(float param1, float param2)
{
    RandomWalk::average = 0;
    RandomWalk::variance = 0;
    RandomWalk::standard_deviation = 0;
    RandomWalk::param1 = param1;
    RandomWalk::param2 = param2;
}