#include <iostream>
#include <exception>
#include <stdlib.h>
#include <math.h> 
#include <random>

class RandomWalk
{
public:
    // Construcors
    RandomWalk(std::vector<float>, int, std::string, float, float, float);
    RandomWalk(const RandomWalk&);

    // Getters
    int getN();
    std::string getDistribution();
    float getInitialValue();
    float getParam(int);

    // Methods
    float computeAvg();
    float computeVar();
    float computeStdDev();

    // Return the value of the random walk for any index
    float operator[](int);

private:
    // Variables
    float average;
    float variance;
    float standard_deviation;

    // Attributes
    int n;
    int initial_value;
    float param1;                 // 1=nb int, 2=lowest value, 3=average
    float param2;                // 1=probability, 2=highest value, 3=variance
    std::string distribution;   // 1=binomial / 2=uniform / 3=normal

    // Vectors containing walk values
    std::vector<float> values;

    // Method
    void initVariables(float, float);

    // Setters
    void setN(int);
    void setInitialValue(float);
    void setDistribution(std::string);
    void setValues(std::vector<float>);
};