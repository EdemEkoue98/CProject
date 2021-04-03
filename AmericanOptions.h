
#pragma once
#include "Options.h"
#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
#include <math.h>
using namespace std;

class AmericanOptions : public Options
{

public:

	AmericanOptions();

	AmericanOptions(options, double, double, double);
	int verificationA();
	double payoff();


};