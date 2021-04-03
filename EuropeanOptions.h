#pragma once
#include "Options.h"
#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
#include <math.h>


class EuropeanOptions : public Options
{

public: 

	EuropeanOptions();
	
	EuropeanOptions(options,double, double, double);
	int verification();
	double payoff(); 

 
};