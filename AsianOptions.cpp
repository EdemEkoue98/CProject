#include "AsianOptions.h" 
#include "Options.h"
#include <vector>// STL vector templates
#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>// standard mathematical library
#include <math.h>
# include <algorithm>




AsianOptions::AsianOptions(options opti, double strik, double maturit, double underly) : Options(opti, strik, maturit, underly)
{
	opti = opti;
	strik = strik;
	maturit = maturit;
	underly = underly;
}

double AsianOptions::payoff()
{
	

	// the payoff is compute in the montecarlo class 
	return 1;

}

int AsianOptions::verification() // to verify if an option is a call or put in order to use it in blackscholes and crr model
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