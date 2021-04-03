#include "EuropeanOptions.h" 
#include "Options.h"
#include <vector>// STL vector templates
#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>// standard mathematical library
#include <math.h>
# include <algorithm>




EuropeanOptions::EuropeanOptions(options opti, double strik, double maturit, double underly) : Options(opti, strik, maturit, underly)
{
	opti = opti;
	strik = strik;
	maturit = maturit;
	underly = underly;
}

double EuropeanOptions::payoff()
{
	double resultat = 0;
	if (this->option == options::call)
	{
		std::cout << " this option is a Call option " << std::endl;
		std::cout << "the underlyinng price  is " << this->underlying_price << std::endl;
		std::cout << " the strike worth " << this->strike << std::endl;
		resultat = std::max(this->underlying_price - this->strike, 0.0);
		
	}
	if (this->option == options::put)
	{
		std::cout << " this option is a Put option " << std::endl;
		std::cout << "the underlyinng price  is " << this->underlying_price << std::endl;
		std::cout << " the strike worth " << this->strike << std::endl;
		resultat = std::max(this->strike - this->underlying_price, 0.0);

	}

	std::cout << "the payoff value is "  ;
	return resultat; 
	
}

int EuropeanOptions::verification() // to verify if an option is a call or put in order to use it in blackscholes and crr model
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