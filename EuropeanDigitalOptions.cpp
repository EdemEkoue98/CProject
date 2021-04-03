#include "EuropeanDigitalOptions.h" 
#include "Options.h"
#include <vector>// STL vector templates
#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>// standard mathematical library
#include <math.h>
# include <algorithm>
using namespace std;


EuropeanDigitalOptions::EuropeanDigitalOptions(options opti, double strik, double maturit, double underly) : Options(opti, strik, maturit, underly)
{
	opti = opti;
	strik = strik;
	maturit = maturit;
	underly = underly;
}

double EuropeanDigitalOptions::payoff()
{
	double resultat = 0;
	if (this->option == options::call)
	{
		cout << " this option is a European Digital Call option " << endl;
		cout << "the underlyinng price  is " << this->underlying_price << endl;
		cout << " the strike worth " << this->strike << endl;

		if (this->underlying_price >= this->strike)
		{
			resultat = 1; 
		}
		else
		{
			resultat = 0;
		}
	}
	if (this->option == options::put)
	{
		cout << " this option is a European Digital Put option " << endl;
		cout << "the underlyinng price  is " << this->underlying_price << endl;
		cout << " the strike worth " << this->strike << endl;

		if (this->underlying_price <= this->strike)
		{
			resultat = 1;
		}
		else
		{
			resultat = 0;
		}
	}

	cout << "the payoff value is ";
	return resultat;

}