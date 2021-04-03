#pragma once
#include "AsianOptions.h"
#include "EuropeanOptions.h"
#include "EuropeanDigitalOptions.h"
#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
#include <math.h>
#include <vector>

class MonteCarlo
{

protected:
	double volatility;
	double interest_rate; // taux sans risque
	int number_of_iteration; // for the crr model 

public: 
	MonteCarlo();
	MonteCarlo(double, double, int);
	double GaussianLaw();
	double MonteCarloPricer_exotic(AsianOptions);
	double payoff_monte_put(vector<double> , double K);
	double payoff_monte_call(vector<double>, double K);
	double Simulation_Monte(AsianOptions,int); // this function allows to simulate the montecarlo pricer n times 
	// and take the average to see if the price is more constant 
};


