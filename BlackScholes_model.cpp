#include "BlackScholes_model.h"
#include "Options.h"
#include "EuropeanOptions.h"
#include "EuropeanDigitalOptions.h"
#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
#include <math.h>
using namespace std;



BlackScholes::BlackScholes(double sigma, double interest, double str)
{
	volatility = sigma;
	interest_rate = interest;
	strike = str;
}

double BlackScholes::norm_distrib(const double& x)
{
	double k = 1.0 / (1.0 + 0.2316419 * x);
	double k_sum = k * (0.319381530 + k * (-0.356563782 + k * (1.781477937 + k * (-1.821255978 + 1.330274429 * k))));
	if (x >= 0.0)
		return (1.0 - (1.0 / (pow(2 * M_PI, 0.5))) * exp(-0.5 * x * x) * k_sum);
	else
		return 1.0 - norm_distrib(-x);
}

double BlackScholes::d1(EuropeanOptions opta)
{
	return (log(opta.underlying_price / this->strike) + (this->interest_rate + pow(this->volatility, 2) / 2) * opta.maturity) / (this->volatility * sqrt(opta.maturity));
}

double BlackScholes::d2(EuropeanOptions opta)
{
	return d1(opta) - volatility * sqrt(opta.maturity);
}

void BlackScholes::Pricing(EuropeanOptions opta)
{
	if (opta.verification() == 0)
	{
		double call_price = 0; // we will determine the price of the call
		cout << "this option is an European Call option" << endl;
		call_price = opta.underlying_price * norm_distrib(d1(opta)) - strike * exp(-this->interest_rate * opta.maturity) * norm_distrib(d2(opta));
		cout << "The price given by the black Scholes model for this  European call option is" << call_price << endl;
	}
	if (opta.verification() == 1)
	{
		double put_price = 0; // we will determine the price of the call
		cout << "this option is an European Call option" << endl;
		put_price = opta.underlying_price * norm_distrib(d1(opta)) - strike * exp(-this->interest_rate * opta.maturity) * norm_distrib(d2(opta));
		cout << "The price given by the black Scholes model for this  European call option is" << put_price << endl;
	}


}