# pragma once
#define _USE_MATH_DEFINES
# include<list>
#include <cmath>
#include <iostream>


class Options
{

	
public:

	enum class options { call, put};

	double strike; // strike k 
	double maturity; /// maturity
	double underlying_price; // prix sous jacent
	options option;

	
	virtual double payoff()=0 ;

	/*void display()
	{
		if (this->option == options::call)
		{
			cout << "this option is a call " << endl;
		}

		if (this->option == options::put)
		{
			cout << "this option is a put " << endl;
		}

	};*/
	Options();
	Options(options op, double s, double m, double under)
	{
		option = op;
		strike = s;
		maturity = m;
		underlying_price = under;
	}
	
	
	
};
