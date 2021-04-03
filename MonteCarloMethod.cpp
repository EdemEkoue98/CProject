# include"MonteCarloMethod.h"
#include <vector>// STL vector templates
#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>// standard mathematical library
#include <math.h>
#include <random>
# include <algorithm>
#include "EuropeanOptions.h"

MonteCarlo::MonteCarlo(double sigma, double interest, int p)
{
	volatility = sigma;
	interest_rate = interest;
	number_of_iteration = p;
}

double MonteCarlo::GaussianLaw()
{
	std::random_device rd;
	std::mt19937 gen(rd());

	int i;
	double sample;
	std::normal_distribution<double> d(0, 1);
	sample = d(gen);
	return sample;
}

double MonteCarlo::MonteCarloPricer_exotic(AsianOptions opta)
{
	int n = this->number_of_iteration;
	double K = opta.strike;
	double T = opta.maturity;
	double S = opta.underlying_price;
	double sigma = this->volatility;
	double r = this->interest_rate;
	vector<vector<double>> Stocks(n,vector<double>(n));
	
	vector<double> t(n);
	vector<double> Payoffss(n);
	for (int k = 0; k < n; k++)
	{
		if (k == 0)
		{
			t[0] = (double)(T / (double)n);
		}
		else
		{
			t[k] = (double)(((k+1) * T) / (double)n);
		}

		
	}
	//for (int j = 0; j < n; j++)
	//{
	//	std::cout << t[j] << std::endl; // a look on the t[k]
	//}
	for (int k = 0; k < n; k++)
	{
		for (int j = 0; j < n; j++)
		{
			if (k == 0)
			{

				Stocks[0][j] = S * (double)(exp((r - (pow(sigma, 2) / 2)) * t[0] + sigma * pow(t[0], 0.5) * GaussianLaw()));
			}
			else
			{
				Stocks[k][j] = Stocks[k-1][j] * (double)(exp((r - (pow(sigma, 2) / 2)) * (t[k]-t[k-1]) + sigma * pow((t[k]-t[k-1]), 0.5) * GaussianLaw()));
			}

		}
	}
	
	/*for (int i = 0; i < n; i++)
	{
		for (int j = 0; j <n; j++)
		{
			std::cout << Stocks[i][j] << "|";
		}
		std::cout << " " << std::endl;
	}*/

	// payoffs calculation 

	// for monte carlo method we understand the St[k]^(i) 
	// like the ith component of the St[k] Vector 
	// so we will calculate the Matrix STocks transpose 


	vector<vector<double>> Stocks_transpose (n, vector<double>(n));
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			Stocks_transpose[i][j] = Stocks[j][i];
		}
		
	}

	/*for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			std::cout << Stocks_transpose[i][j] << "|";
		}
		std::cout << " " << std::endl;
	}*/

	// so now we will calculate the payoff according to monte carlon methods 
	double sum = 0;
	if (opta.verification() == 0) // a disjonction of case is treated here Call/Put 
	{
		for (int k = 0; k < n; k++)
		{
			sum += payoff_monte_call(Stocks_transpose[k], K);

		}
		/*std::cout << sum << std::endl;*/
	}
	if (opta.verification() == 1)
	{
		for (int k = 0; k < n; k++)
		{
			sum += payoff_monte_put(Stocks_transpose[k], K);

		}
		/*std::cout << sum << std::endl;*/
	}

	double H_o = 0;
	H_o = (exp(-r * T) / n) * sum;

	return H_o; // for each simulation i obtain the price given by the montecarlo method but these numbers are too
	            // different so i will do this simulation N = 100000 times and take the average of the price obtained at each time
}

double MonteCarlo::payoff_monte_call(vector<double> Vect,double K )
{
	
	double sum = 0;
	double p = Vect.size();
	for (int k = 0; k < p;k++)
	{
		sum += Vect[k];
	}
	/*std::cout << sum << std::endl;*/
	double expectation =   sum/ p ;
	/*std::cout << expectation << std::endl;*/
	
	double resultat = max((expectation - K), 0.0); 

	return resultat; 
}


double MonteCarlo::payoff_monte_put(vector<double> Vect, double K)
{

	double sum = 0;
	double p = Vect.size();
	for (int k = 0; k < p; k++)
	{
		sum += Vect[k];
	}
	/*std::cout << sum << std::endl;*/
	double expectation = sum / p;
	/*std::cout << expectation << std::endl;*/

	double resultat = max((-expectation + K), 0.0);

	return resultat;
}
double MonteCarlo::Simulation_Monte(AsianOptions opta,int steps)
{   
	double price = 0;
	double sum = 0;
	for (int k = 0; k < steps; k++)
	{
		price = MonteCarloPricer_exotic(opta);
		sum += price;
	}
	return sum / steps;
}