#pragma once
#include "Options.h"
#include "EuropeanOptions.h"
#include"AmericanOptions.h"
#include "EuropeanDigitalOptions.h"
#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
#include <math.h>
using namespace std;

class CRR
{

	double volatility;
	double interest_rate; // taux sans risque
	int number_of_iteration; // for the crr model 

public:

	// constructor 
	CRR();
	CRR(double, double, int);
	// méthodes to compute crr model 
	double pricing_crr_European(EuropeanOptions, double, double);
	double pricing_crr_American(AmericanOptions, double, double);
	double closedform_European(EuropeanOptions, double, double);
	double factorielle(double);
	double approximation_blackscholes_Binomial_tree_European(EuropeanOptions);
	double approximation_Blackscholes_Closed_form_European(EuropeanOptions);
	double payoff();
};