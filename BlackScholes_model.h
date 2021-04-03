#pragma once
#include "Options.h"
#include "EuropeanOptions.h"
#include "EuropeanDigitalOptions.h"
#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
#include <math.h>
using namespace std;

class BlackScholes
{
public:

	double strike; // strike k 
	double interest_rate; // interest
	double volatility; /// Volatility 

	BlackScholes();
	BlackScholes(double,double,double);
	double d1(EuropeanOptions);
	double d2(EuropeanOptions);
	double norm_distrib(const double&);
	void Pricing(EuropeanOptions);

};