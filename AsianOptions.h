#pragma once
#include "Options.h"
#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
#include <math.h>


class AsianOptions : public Options
{

public:

	AsianOptions();

	AsianOptions(options, double, double, double);
	int verification();
	double payoff();


};