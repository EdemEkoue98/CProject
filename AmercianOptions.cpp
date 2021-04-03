#include "AmericanOptions.h" 
#include "Options.h"
#include <vector>// STL vector templates
#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>// standard mathematical library
#include <math.h>
# include <algorithm>
using namespace std;



AmericanOptions::AmericanOptions(options opti, double strik, double maturit, double underly) : Options(opti, strik, maturit, underly)
{
	opti = opti;
	strik = strik;
	maturit = maturit;
	underly = underly;
}

double AmericanOptions::payoff()
{
	double resultat = 0;
	if (this->option == options::call)
	{
		cout << " this option is a Call option " << endl;
		cout << "the underlyinng price  is " << this->underlying_price << endl;
		cout << " the strike worth " << this->strike << endl;
		resultat = max(this->underlying_price - this->strike, 0.0);

	}
	if (this->option == options::put)
	{
		cout << " this option is a Put option " << endl;
		cout << "the underlyinng price  is " << this->underlying_price << endl;
		cout << " the strike worth " << this->strike << endl;
		resultat = max(this->strike - this->underlying_price, 0.0);

	}

	cout << "the payoff value is ";
	return resultat;

}

int AmericanOptions::verificationA() // to verify if an option is a call or put in order to use it in blackscholes and crr model
{
	if (this->option == options::call)
	{
		return 0;
	}
	if (this->option == options::put)
	{
		return 1;
	}

}