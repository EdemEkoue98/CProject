#pragma once
#include "Options.h"
#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
#include <math.h>
using namespace std;

class EuropeanDigitalOptions : public Options
{

public:

	EuropeanDigitalOptions();

	EuropeanDigitalOptions(options, double, double, double);

	double payoff();


};
